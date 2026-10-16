// Specter.Internal — the Lua console (implementation).
//
// See console.h for what this is and, more importantly, what it is not: the
// only caller of submit() is the Execute button, so nothing here runs Lua
// unless a person asked for it.
//
// The heavy lifting is in lua/pump.h (the detour, the state, the chunk runner)
// and lua/mailbox.h (the cross-thread transport). This file wires the two
// together for one queue and one result buffer.

#include "pch-il2cpp.h"

#include "features/console/console.h"

#include <atomic>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <string>

#include "imgui.h"

#include "lua/mailbox.h"
#include "lua/pump.h"
#include "platform/log.h"

namespace specter::features {
namespace console {
namespace {

// Meme valeur que lua/pump.cpp : le tampon de la boite et celui du chunk
// sont le meme objet. tools/embed-lua.sh lit CETTE ligne pour verifier la
// taille des scripts -- une recopie serait un second endroit a maintenir.
constexpr int kMaxCode = 64 * 1024;
constexpr int kMaxOut = 48 * 1024;

// POD payloads, stored inline by the mailbox. Kept in lockstep with the caps
// above so a chunk can never be truncated silently between submit and drain.
struct Chunk {
    char code[kMaxCode];
    int len;
};

struct Output {
    char text[kMaxOut];
    int len;
    bool ok;
};

// Replace, single slot per channel: these are all "what did I just ask for"
// lanes. A backlog of superseded chunks would only make the result harder to
// read, and for the teleport channel it would let an old position probe clobber
// a move that has not run yet.
lua::Mailbox<Chunk, Output, 1, lua::Replace> g_channels[kChannelCount];

unsigned long long g_out_seq = 0;  // bumped per result, Lua thread only

// UI state, owned here rather than by the overlay: the tab is this feature's,
// so its buffers are too.
//
// g_src MUST be kMaxCode, pas un nombre choisi a part.
//
// Il l'etait a 16384, et voila ce que ca donne. Un collage de
// scripts/chest-open.lua (18 198 octets) se fait tronquer a 16 Ko SANS UN MOT :
// ImGui InputTextMultiline ecrase ce qui deborde, la coupure tombe au milieu
// d'une ligne -- ici au milieu de `tpStop()  -- annule un éventuel dép` --, et
// le seul symptome est une erreur de compilation qui ne parle pas du script :
//
//     specter\client\LuaScripts\Core\Timer\SpecterManager.lua:492:
//         unexpected symbol near ')'
//
// Ce nom de fichier, c'est kChunkName. Il ne dit RIEN du script de l'utilisateur
// : il fait croire a un probleme de pont Lua, alors que le pont va tres bien et
// que le texte a ete coupe en route. Deux heures a comparer des lignes de
// source alors que la cause etait un tampon de 16 Ko.
//
// La regle : la boite ou on colle et le tampon qui recoit le chunk sont le
// MÊME objet. Au-dela, il n'y a plus de troncature -- il y a un refus.
char g_src[kMaxCode] = "print('hello from the game Lua')";
std::string g_log;

// Mirror the captured output to the host log pipe, line by line, so the console
// is readable in the terminal and in specter.log next to everything else.
void log_result(bool ok, const char* text, int n)
{
    if (!text || n <= 0) {
        log::info("lua: (no output)");
        return;
    }
    const char* p = text;
    const char* end = text + n;
    int lines = 0;
    while (p < end) {
        if (lines >= 200) {
            log::info("lua| ... (output truncated in the pipe)");
            break;
        }
        ++lines;
        const char* nl = static_cast<const char*>(
            std::memchr(p, '\n', static_cast<std::size_t>(end - p)));
        int len = static_cast<int>(nl ? nl - p : end - p);
        char line[1500];
        int c = len < static_cast<int>(sizeof(line)) - 1
                    ? len
                    : static_cast<int>(sizeof(line)) - 1;
        std::memcpy(line, p, static_cast<std::size_t>(c));
        line[c] = '\0';
        if (ok) {
            log::info("lua| %s", line);
        } else {
            log::error("lua| %s", line);
        }
        p = nl ? nl + 1 : end;
    }
}

// ---- the armed shell -------------------------------------------------------
//
// Guest-side paths. /tmp on the host is Z:\tmp to the game, which is what the
// shell scripts write to. Nothing here exists unless the checkbox was ticked:
// the files only ever appear inside an armed window.
constexpr const char* kCliDir = "Z:\\tmp\\specter-cli";
constexpr const char* kCliReq = "Z:\\tmp\\specter-cli\\req.lua";
constexpr const char* kCliRes = "Z:\\tmp\\specter-cli\\res.txt";

// How long the checkbox opens the window, in Lua-thread ticks.
//
// DISARMED: it no longer expires. It was a 10 s window so that a forgotten
// checkbox was not a standing door, but that is friction without a boundary —
// re-ticking every ten seconds trains you to tick it without reading it, which
// is worse than either extreme. The checkbox is now the whole control: open
// once, stays open for the session, closes when you close it.
constexpr unsigned long long kCliWindowTicks = 0;  // 0 = no expiry

// When the channel was opened. Zero = closed.
//
// OPEN AT LOAD, and that is a deliberate reversal of the earlier decision.
// The channel was shipped closed, opened by a checkbox, so that nothing could
// run Lua without a person having asked. Asked twice, it is now open from the
// first tick: this is a development channel on the operator's own machine, the
// operator injects the module by hand, and a checkbox you re-arm every session
// is a checkbox nobody reads. The checkbox stays, to CLOSE it.
//
// What that costs, stated plainly: anything on this machine that can write
// /tmp/specter-cli/req.lua can run Lua in the game while the module is mapped.
// No injection, no UI, no intent required. That is true of the checkbox too —
// it just needed ten seconds of not-touching.
//
// Every execution is still mirrored to the host log. That is the guard that
// survives this decision: not "nobody can use it", but "nothing goes unrecorded".
std::atomic<unsigned long long> g_cli_armed_at = 1;

// One-shot: says once, the first time the shell actually serves something, that
// the channel was open before anyone touched the checkbox. An integer atomic
// with a constant initialiser, like every other global here — nothing runs at
// load time.
std::atomic<unsigned long long> g_cli_first_use = 0;

// The chunk taken from the shell, owned by the Lua thread.
char g_cli_code[kMaxCode];
int g_cli_len = 0;
// TRUE when the request filled the buffer: the chunk we received is a prefix of
// the file the shell sent. See read_file.
bool g_cli_truncated = false;

// Read a whole file, or fail. Returns false if it is absent or unreadable —
// Read a whole file, or fail. Returns false if it is absent or unreadable —
// which is the normal case, every frame, for the whole time the window is shut.
//
// A file that does not fit is NOT read partially. ReadFile fills `cap - 1`
// bytes and reports success, and the caller would then run a prefix of the
// chunk: the parse dies somewhere in the middle, on a line the user never
// wrote, under a chunk name that is ours and theirs. That happened twice in
// one session — `unfinished string near 'TP_ONLY '`, then a state that looked
// like a live run but was the previous run's leftovers.
//
// So `out_truncated` (optional) says "this did not fit" and the caller refuses.
bool read_file(const char* path, char* out, int cap, int* out_len,
               bool* out_truncated = nullptr)
{
    if (out_truncated) {
        *out_truncated = false;
    }
    HANDLE h = ::CreateFileA(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
                             nullptr, OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) {
        return false;
    }
    DWORD want = static_cast<DWORD>(cap - 1);
    DWORD got = 0;
    const BOOL ok = ::ReadFile(h, out, want, &got, nullptr);
    ::CloseHandle(h);
    if (!ok) {
        return false;
    }
    if (got == want) {
        // Full buffer. Either the file is exactly cap-1 bytes, or it is longer.
        // One byte more settles it, and it is cheaper than being wrong.
        HANDLE h2 = ::CreateFileA(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                  nullptr, OPEN_EXISTING,
                                  FILE_ATTRIBUTE_NORMAL, nullptr);
        if (h2 != INVALID_HANDLE_VALUE) {
            char probe;
            DWORD extra = 0;
            ::SetFilePointer(h2, static_cast<LONG>(want), nullptr, FILE_BEGIN);
            if (::ReadFile(h2, &probe, 1, &extra, nullptr) && extra > 0 && out_truncated) {
                *out_truncated = true;
            }
            ::CloseHandle(h2);
        }
    }
    out[got] = '\0';
    *out_len = static_cast<int>(got);
    return true;
}

void write_file(const char* path, const char* text, int len)
{
    HANDLE h = ::CreateFileA(path, GENERIC_WRITE, FILE_SHARE_READ,
                             nullptr, CREATE_ALWAYS,
                             FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) {
        return;
    }
    DWORD put = 0;
    ::WriteFile(h, text, static_cast<DWORD>(len), &put, nullptr);
    ::CloseHandle(h);
}

// The pump's result sink. Runs on the Lua thread, inside pump::run.
// One sink per channel. The pump takes a plain function pointer, so it cannot be
// told "which channel" any other way.
Channel g_sink_channel = kChannelConsole;

// Where the shell reads its answer. Written only for kChannelCli, and only
// because the window is open — otherwise the file is never touched.
void publish_cli_result(bool ok, const char* text, int n)
{
    char buf[kMaxOut + 64];
    const int len = std::snprintf(buf, sizeof(buf), "#ok=%d\n%s",
                                  ok ? 1 : 0, text ? text : "");
    write_file(kCliRes, buf, len);
    log::info("cli: requete traitee (ok=%d, %d o de sortie)", ok ? 1 : 0, n);
}

void sink(bool ok, const char* text, int n)
{
    if (n < 0) {
        n = text ? static_cast<int>(std::strlen(text)) : 0;
    }
    if (n > kMaxOut - 1) {
        n = kMaxOut - 1;
    }
    Output out;
    if (n > 0 && text) {
        std::memcpy(out.text, text, static_cast<std::size_t>(n));
    }
    out.text[n] = '\0';
    out.len = n;
    out.ok = ok;
    g_channels[g_sink_channel].publish(out);
    ++g_out_seq;

    // Which channels' output is a human reading it, and which is a machine.
    //
    // The teleport channel produces no output worth reading: it runs a chunk
    // that calls straight into C++. When it DID print "P x y z" and
    // "F <zone>..." for a parser, mirroring them to the log wrote one line
    // every 0.75 s for as long as the Teleport tab was open -- a wall of
    // "(no output)", with the real question underneath it invisible in the
    // noise.
    //
    // Errors are logged whatever the channel: a chunk that failed is worth
    // seeing even if its output was meant for a parser.
    const bool pourHumain = (g_sink_channel == kChannelConsole ||
                             g_sink_channel == kChannelCli ||
                             g_sink_channel == kChannelInit);
    if (pourHumain || !ok) {
        log_result(ok, text, n);
    }
    if (g_sink_channel == kChannelCli) {
        publish_cli_result(ok, text, n);
    }
}

// Claim the request: rename it away so the same chunk cannot run twice. If the
// shell is still writing, the rename fails and we leave it for the next tick.
bool claim_request()
{
    char claimed[64];
    std::snprintf(claimed, sizeof(claimed), "%s\\claimed.lua", kCliDir);
    if (!::MoveFileA(kCliReq, claimed)) {
        return false;
    }
    int n = 0;
    bool tropGrand = false;
    const bool ok = read_file(claimed, g_cli_code, kMaxCode, &n, &tropGrand);
    ::DeleteFileA(claimed);
    if (!ok) {
        return false;
    }
    if (tropGrand) {
        // On refuse, et on le DIT. Le refus est publish_cli_result(false, ...)
        // pour que la commande responde au lieu de timeout.
        const char* msg =
            "ERREUR: le script depasse kMaxCode (32767 octets).\n"
            "       Recu tel quel : il serait coupe en plein milieu d'une chaine,\n"
            "       et l'erreur de compilation nommerait un fichier qui n'est pas\n"
            "       le votre. Coupez-le, ou lancez le en plusieurs morceaux.";
        log::error("cli: requete trop grande (%d octets et plus), refusee", n);
        publish_cli_result(false, msg, static_cast<int>(std::strlen(msg)));
        return false;
    }
    g_cli_len = n;
    return true;
}

// Take one shell request, if the channel is open. Returns false when the
// checkbox is off, or when there is nothing to take.
bool take_cli_request()
{
    if (g_cli_armed_at.load(std::memory_order_relaxed) == 0) {
        return false;
    }
    // The expiry stays in the code as the one-line way to get it back, so the
    // trade-off is visible rather than forgotten.
    if (kCliWindowTicks != 0 &&
        lua::pump::ticks() - g_cli_armed_at.load(std::memory_order_relaxed) >
            kCliWindowTicks) {
        g_cli_armed_at.store(0, std::memory_order_relaxed);
        log::info("cli: fenetre expiree, le shell est de nouveau muet");
        return false;
    }
    if (!claim_request()) {
        return false;
    }
    // Once, and only when something actually came through. exchange() returns
    // the PREVIOUS value: testing it the other way round logs on every call
    // from the second onwards, which is every frame.
    if (g_cli_first_use.exchange(1, std::memory_order_relaxed) == 0) {
        log::info("cli: premiere requete servie (canal ouvert par defaut, "
                  "la case 'Autoriser le shell' permet de le fermer)");
    }
    return true;
}

// The console's tick hook. Runs on the Lua thread once per CommonUpdate; it
// drains whatever Execute queued, and the shell's requests while a window is
// open. Nothing else.
void on_lua_tick(void* L)
{
    // Static, not a local: this runs every frame, and a 32 KB automatic object
    // would be pushed on the game's Lua-thread stack sixty times a second for
    // the privilege of usually going unused. Only the Lua thread reaches it.
    static Chunk c;
    for (int i = 0; i < kChannelCount; ++i) {
        if (!g_channels[i].take_pending(c)) {
            continue;
        }
        g_sink_channel = static_cast<Channel>(i);
        // The one boundary where IL2CPP's void* becomes the real lua_State*.
        // pump.h now takes the typed pointer because the DLL has ONE
        // declaration of that type (capi.h) instead of a hand-written
        // `using lua_State = void` in one file and the header's in another.
        lua::pump::run(static_cast<lua_State*>(L), c.code, c.len, &sink);
    }
    if (take_cli_request()) {
        g_sink_channel = kChannelCli;
        lua::pump::run(static_cast<lua_State*>(L), g_cli_code, g_cli_len, &sink);
    }
}

}  // namespace

// ---- public API ------------------------------------------------------------

bool install()
{
    return lua::pump::add_tick_hook(&on_lua_tick);
}

bool ready()
{
    return lua::pump::ready();
}

bool submit_call(Channel ch, const char* name, int ndoubles, ...)
{
    if (!name || !*name) {
        return false;
    }
    // 128 for the name, 32 per argument: "%.17g" of a double never exceeds 24
    // characters plus a sign, a decimal point and an exponent.
    char code[128 + 32 * (ndoubles > 0 ? ndoubles : 0)];
    int n = std::snprintf(code, sizeof(code), "%s(", name);
    if (n <= 0 || n >= static_cast<int>(sizeof(code))) {
        return false;
    }
    va_list ap;
    va_start(ap, ndoubles);
    for (int i = 0; i < ndoubles; ++i) {
        const double v = va_arg(ap, double);
        const int w = std::snprintf(code + n, sizeof(code) - static_cast<std::size_t>(n),
                                    i ? ", %.17g" : "%.17g", v);
        if (w <= 0 || n + w >= static_cast<int>(sizeof(code))) {
            va_end(ap);
            return false;
        }
        n += w;
    }
    va_end(ap);
    const int tail = std::snprintf(code + n, sizeof(code) - static_cast<std::size_t>(n), ")");
    if (tail != 1) {
        return false;
    }
    n += tail;
    return submit(ch, code, n);
}

bool submit(Channel ch, const char* code, int len)
{
    if (ch < 0 || ch >= kChannelCount) {
        return false;
    }
    if (!lua::pump::ready()) {
        return false;
    }
    if (!code || len <= 0) {
        return false;
    }
    if (len > kMaxCode) {
        len = kMaxCode;
    }
    Chunk c;
    std::memcpy(c.code, code, static_cast<std::size_t>(len));
    c.code[len] = '\0';
    c.len = len;
    return g_channels[ch].submit(c);
}

bool take_result(Channel ch, char* out, int cap, bool* out_ok)
{
    if (ch < 0 || ch >= kChannelCount || !out || cap <= 0) {
        return false;
    }
    Output o;
    if (!g_channels[ch].take_result(o)) {
        return false;
    }
    int n = o.len;
    if (n > cap - 1) {
        n = cap - 1;
    }
    std::memcpy(out, o.text, static_cast<std::size_t>(n));
    out[n] = '\0';
    if (out_ok) {
        *out_ok = o.ok;
    }
    return true;
}

const char* status()
{
    return lua::pump::status();
}

// Open the shell channel. Called from the checkbox, on the render thread; the
// state itself is read on the Lua thread, so this only ever writes one atomic.
void arm_cli()
{
    g_cli_armed_at.store(1, std::memory_order_relaxed);
    log::info("cli: canal ouvert -- tools/lua.sh peut parler jusqu'a fermeture");
}

// Drain whatever the Lua thread produced since the last frame. Called from
// draw_ui, because that is the only place the result is shown.
void drain_result()
{
    char buf[8192];
    bool ok = false;
    if (!take_result(kChannelConsole, buf, sizeof(buf), &ok)) {
        return;
    }
    g_log += ok ? "> " : "! ";
    g_log += buf;
    g_log += '\n';
    constexpr std::size_t kKeep = 60000;
    if (g_log.size() > kKeep) {
        g_log.erase(0, g_log.size() - kKeep / 2);
    }
}

void note(const char* text)
{
    if (!text) {
        return;
    }
    g_log += text;
    constexpr std::size_t kKeep = 60000;
    if (g_log.size() > kKeep) {
        g_log.erase(0, g_log.size() - kKeep / 2);
    }
}

void draw_ui()
{
    drain_result();

    ImGui::Text("bridge: %s", status());
    ImGui::InputTextMultiline("##lua_src", g_src, sizeof(g_src),
                              ImVec2(-1.0f, 180.0f));

    // Le tampon est plein => le prochain caractere est perdu. Ça se voit ici,
    // en clair, AVANT que Lua ne rende une erreur qui accuse le pont.
    const int srcLen = static_cast<int>(std::strlen(g_src));
    if (srcLen >= static_cast<int>(sizeof(g_src)) - 1) {
        ImGui::TextColored(ImVec4(1.0f, 0.35f, 0.30f, 1.0f),
                           "TAMPON PLEIN (%d / %d octets) : le texte est coupe, "
                           "l'execution echouera.", srcLen,
                           static_cast<int>(sizeof(g_src)) - 1);
    }
    if (ImGui::Button("Execute")) {
        const int n = srcLen;
        if (!submit(kChannelConsole, g_src, n)) {
            g_log += "! bridge not ready\n";
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Clear output")) {
        g_log.clear();
    }
    ImGui::SameLine();
    ImGui::TextDisabled("(an infinite loop freezes the game)");

    // The shell window. Ticking this is the only thing that lets anything run
    // Lua without the Execute button, which is the whole point: the precondition
    // stays a human action, and it lapses on its own.
    ImGui::Separator();
    bool open = g_cli_armed_at.load(std::memory_order_relaxed) != 0;
    if (ImGui::Checkbox("Autoriser le shell", &open)) {
        if (open) {
            arm_cli();
        } else {
            g_cli_armed_at.store(0, std::memory_order_relaxed);
            log::info("cli: canal ferme");
        }
    }
    ImGui::SameLine();
    if (open) {
        ImGui::Text("ouvert (par defaut) -- decocher pour fermer");
    } else {
        ImGui::TextDisabled("ferme");
    }

    ImGui::BeginChild("##lua_out", ImVec2(-1.0f, -1.0f), true);
    ImGui::TextUnformatted(g_log.c_str());
    ImGui::EndChild();
}

}  // namespace console
}  // namespace specter::features