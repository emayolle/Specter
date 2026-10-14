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
#include <cstring>
#include <string>

#include "imgui.h"

#include "lua/mailbox.h"
#include "lua/pump.h"
#include "platform/log.h"

namespace specter::features {
namespace console {
namespace {

constexpr int kMaxCode = 32 * 1024;
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
char g_src[16384] = "print('hello from the game Lua')";
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

// The pump's result sink. Runs on the Lua thread, inside pump::run.
// One sink per channel. The pump takes a plain function pointer, so it cannot be
// told "which channel" any other way.
Channel g_sink_channel = kChannelConsole;

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
    log_result(ok, text, n);
}

// The console's tick hook. Runs on the Lua thread once per CommonUpdate; it
// drains whatever Execute queued and nothing else.
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
        lua::pump::run(L, c.code, c.len, &sink);
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
    if (ImGui::Button("Execute")) {
        const int n = static_cast<int>(std::strlen(g_src));
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

    ImGui::BeginChild("##lua_out", ImVec2(-1.0f, -1.0f), true);
    ImGui::TextUnformatted(g_log.c_str());
    ImGui::EndChild();
}

}  // namespace console
}  // namespace specter::features