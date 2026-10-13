// Specter.Internal — teleport feature (implementation).
//
// See tp.h. The persistence file is /tmp (mapped as Z:\ under wine), the same
// place the log fallback and the Lua CLI channel live: never inside the game
// directory or the wine prefix.

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "features/lua_console.h"
#include "features/tp.h"
#include "log.h"

namespace specter::features {
namespace tp {
namespace {

constexpr int kMaxSlots = 64;
constexpr std::size_t kNameCap = 32;
const wchar_t* kFile = L"Z:\\tmp\\specter-tp.json";
const wchar_t* kFileTmp = L"Z:\\tmp\\specter-tp.json.tmp";

// Lerp tuning bounds (defaults match the values validated live).
constexpr float kLerpStepDef = 2.0f;
constexpr float kLerpStepMin = 0.25f;
constexpr float kLerpStepMax = 20.0f;
constexpr float kLerpSpeedDef = 60.0f;
constexpr float kLerpSpeedMin = 5.0f;
constexpr float kLerpSpeedMax = 120.0f;
constexpr int kLerpMaxSteps = 20000;

float clampf(float v, float lo, float hi)
{
    return v < lo ? lo : (v > hi ? hi : v);
}

struct Slot
{
    char name[kNameCap] = {};
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    int space = 1;
};

// Render-thread only.
std::vector<Slot> g_slots;
float g_cur[3] = {};
int g_cur_space = 1;
bool g_cur_valid = false;
float g_lerp_step = kLerpStepDef;
float g_lerp_speed = kLerpSpeedDef;

void write_slots()
{
    std::string out;
    out.reserve(g_slots.size() * 48 + 32);
    char cfg[64];
    std::snprintf(cfg, sizeof(cfg), "@lerp %.4f %.4f\n",
                  static_cast<double>(g_lerp_step),
                  static_cast<double>(g_lerp_speed));
    out += cfg;
    for (const Slot& s : g_slots) {
        char line[96];
        std::snprintf(line, sizeof(line), "%s %.6f %.6f %.6f %d\n", s.name,
                      static_cast<double>(s.x), static_cast<double>(s.y),
                      static_cast<double>(s.z), s.space);
        out += line;
    }
    HANDLE h = ::CreateFileW(kFileTmp, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
                             FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) {
        log::error("tp: can't write %ls", kFileTmp);
        return;
    }
    DWORD wrote = 0;
    ::WriteFile(h, out.data(), static_cast<DWORD>(out.size()), &wrote, nullptr);
    ::CloseHandle(h);
    ::MoveFileExW(kFileTmp, kFile, MOVEFILE_REPLACE_EXISTING);
}

// Slot names travel through a whitespace-separated file, so keep them to a
// safe charset (everything else becomes '_').
void sanitize_name(char* out, std::size_t cap, const char* src)
{
    std::size_t n = 0;
    if (!src) {
        src = "";
    }
    for (; src[n] && n + 1 < cap; ++n) {
        char c = src[n];
        const bool ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                        (c >= '0' && c <= '9') || c == '_' || c == '-';
        out[n] = ok ? c : '_';
    }
    out[n] = '\0';
}

// Parse "x y z [space]" (optionally prefixed by a "P " tag from kPosProbe).
// Returns false when fewer than three numbers are present.
bool parse_position(const char* text, float* x, float* y, float* z, int* space)
{
    const char* p = text;
    while (*p == ' ' || *p == '\t') {
        ++p;
    }
    if (*p == 'P' && (p[1] == ' ' || p[1] == '\t')) {
        ++p;
    }
    char* end = nullptr;
    const float vx = std::strtof(p, &end);
    if (end == p) {
        return false;
    }
    p = end;
    const float vy = std::strtof(p, &end);
    if (end == p) {
        return false;
    }
    p = end;
    const float vz = std::strtof(p, &end);
    if (end == p) {
        return false;
    }
    p = end;
    int sp = 1;
    char* se = nullptr;
    const long v = std::strtol(p, &se, 10);
    if (se != p) {
        sp = static_cast<int>(v);
    }
    *x = vx;
    *y = vy;
    *z = vz;
    *space = sp;
    return true;
}

// --- Lua chunks (run on the Lua thread via the dedicated TP channel) --------

// Prints "P <x> <y> <z> <space>" when a player entity exists.
constexpr char kPosProbe[] =
    "local e=pg.me\n"
    "if not e then for _k,_v in pairs(pg.global.actorMgr.uid2Ent) do e=_v break end end\n"
    "if not e then return end\n"
    "local p=e:getPosition()\n"
    "if p then print(string.format('P %.2f %.2f %.2f %d', p[1],p[2],p[3],"
    "p[4] or 0)) end\n";

// Teleport by lerping. A single big setPosition is rejected by the
// server-authoritative movement and rubber-bands the player back; instead we
// walk the player toward the target in small per-tick steps. The step size and
// rate come from the user-tunable settings (g_lerp_step / g_lerp_speed). The
// step loop lives in the game's own timer and self-disables, and any previous
// move is cancelled before a new one starts, so nothing keeps re-asserting an
// old position.
bool send_setpos(float x, float y, float z)
{
    const double step = clampf(g_lerp_step, kLerpStepMin, kLerpStepMax);
    const double interval = 1.0 / clampf(g_lerp_speed, kLerpSpeedMin, kLerpSpeedMax);
    char code[2048];
    const int n = std::snprintf(
        code, sizeof(code),
        "local e=pg.me\n"
        "if not e then for _k,_v in pairs(pg.global.actorMgr.uid2Ent) do e=_v break end end\n"
        "if not e or not e.getPosition then return end\n"
        "local V=Vector3\n"
        "local TM=require('Core.Timer.TimerManager')\n"
        "local prev=e.__specter_tp\n"
        "if prev and prev.tid then pcall(function() TM.removeTimer(prev.tid) end) end\n"
        "if prev then prev.active=false end\n"
        "local p=e:getPosition()\n"
        "if not p then return end\n"
        "local st={active=true,i=0,s=%.4f,"
        "x0=p[1],y0=p[2],z0=p[3],x1=%.4f,y1=%.4f,z1=%.4f}\n"
        "e.__specter_tp=st\n"
        "local dx,dy,dz=st.x1-st.x0,st.y1-st.y0,st.z1-st.z0\n"
        "local dist=(dx*dx+dy*dy+dz*dz)^0.5\n"
        "local n=math.ceil(dist/st.s)\n"
        "if n<1 then n=1 end\n"
        "if n>%d then n=%d end\n"
        "st.n=n\n"
        "local s=st\n"
        "local tid\n"
        "tid=TM.addRepeatTimer(%.5f,function()\n"
        "  if not s.active then return end\n"
        "  s.i=s.i+1\n"
        "  local a=s.i/s.n\n"
        "  if a>1 then a=1 end\n"
        "  local v=V.ForceNew(s.x0+(s.x1-s.x0)*a,s.y0+(s.y1-s.y0)*a,"
        "s.z0+(s.z1-s.z0)*a)\n"
        "  if e.forceSetPos then e:forceSetPos(v,true) else e:setPosition(v) end\n"
        "  if s.i>=s.n then s.active=false "
        "pcall(function() TM.removeTimer(tid) end) end\n"
        "end)\n"
        "st.tid=tid\n",
        step, static_cast<double>(x), static_cast<double>(y),
        static_cast<double>(z), kLerpMaxSteps, kLerpMaxSteps, interval);
    if (n <= 0 || n >= static_cast<int>(sizeof(code))) {
        return false;
    }
    return features::lua::tp_submit(code, n);
}

}  // namespace

void init()
{
    g_slots.clear();
    HANDLE h = ::CreateFileW(kFile, GENERIC_READ,
                             FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                             OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h != INVALID_HANDLE_VALUE) {
        static char buf[8192];
        DWORD got = 0;
        DWORD total = 0;
        while (total < sizeof(buf) - 1 &&
               ::ReadFile(h, buf + total,
                          static_cast<DWORD>(sizeof(buf) - 1 - total), &got,
                          nullptr) &&
               got != 0) {
            total += got;
        }
        ::CloseHandle(h);
        buf[total] = '\0';
        const char* p = buf;
        while (p && *p) {
            // One line: a "@lerp <step> <speed>" tuning header, or a slot
            // "<name> <x> <y> <z> [space]".
            while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') {
                ++p;
            }
            if (*p == '@') {
                float st = 0.0f;
                float sp = 0.0f;
                if (std::sscanf(p, "@lerp %f %f", &st, &sp) == 2) {
                    g_lerp_step = clampf(st, kLerpStepMin, kLerpStepMax);
                    g_lerp_speed = clampf(sp, kLerpSpeedMin, kLerpSpeedMax);
                }
                const char* eol = std::strchr(p, '\n');
                p = eol ? eol + 1 : p + std::strlen(p);
                continue;
            }
            char name[kNameCap] = {};
            std::size_t nl = 0;
            while (p[nl] && p[nl] != ' ' && p[nl] != '\t' && p[nl] != '\r' &&
                   p[nl] != '\n' && nl + 1 < sizeof(name)) {
                name[nl] = p[nl];
                ++nl;
            }
            p += nl;
            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
            int sp = 1;
            if (name[0] &&
                parse_position(p, &x, &y, &z, &sp) &&
                g_slots.size() < kMaxSlots) {
                Slot s;
                std::snprintf(s.name, sizeof(s.name), "%s", name);
                s.x = x;
                s.y = y;
                s.z = z;
                s.space = sp;
                g_slots.push_back(s);
            }
            const char* eol = std::strchr(p, '\n');
            p = eol ? eol + 1 : p + std::strlen(p);
        }
    }
    log::info("tp: %d saved slot(s) loaded from /tmp/specter-tp.json "
              "(lerp step %.2f u, speed %.0f/s)",
              static_cast<int>(g_slots.size()),
              static_cast<double>(g_lerp_step),
              static_cast<double>(g_lerp_speed));
}

void request_position()
{
    features::lua::tp_submit(kPosProbe, static_cast<int>(sizeof(kPosProbe) - 1));
}

bool have_position()
{
    return g_cur_valid;
}

void position(float* x, float* y, float* z, int* space)
{
    if (x) {
        *x = g_cur[0];
    }
    if (y) {
        *y = g_cur[1];
    }
    if (z) {
        *z = g_cur[2];
    }
    if (space) {
        *space = g_cur_space;
    }
}

void handle_result(const char* text)
{
    if (!text || !*text) {
        return;
    }
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    int sp = 1;
    if (parse_position(text, &x, &y, &z, &sp)) {
        g_cur[0] = x;
        g_cur[1] = y;
        g_cur[2] = z;
        g_cur_space = sp;
        g_cur_valid = true;
    }
}

bool save_current(const char* name)
{
    if (!g_cur_valid) {
        return false;
    }
    char clean[kNameCap];
    sanitize_name(clean, sizeof(clean), name);
    if (!clean[0]) {
        return false;
    }
    for (Slot& s : g_slots) {
        if (std::strcmp(s.name, clean) == 0) {
            s.x = g_cur[0];
            s.y = g_cur[1];
            s.z = g_cur[2];
            s.space = g_cur_space;
            write_slots();
            return true;
        }
    }
    if (static_cast<int>(g_slots.size()) >= kMaxSlots) {
        return false;
    }
    Slot s;
    std::snprintf(s.name, sizeof(s.name), "%s", clean);
    s.x = g_cur[0];
    s.y = g_cur[1];
    s.z = g_cur[2];
    s.space = g_cur_space;
    g_slots.push_back(s);
    write_slots();
    log::info("tp: saved '%s' at (%.2f, %.2f, %.2f) space %d", s.name,
              static_cast<double>(s.x), static_cast<double>(s.y),
              static_cast<double>(s.z), s.space);
    return true;
}

bool teleport_to(int idx)
{
    if (idx < 0 || idx >= static_cast<int>(g_slots.size())) {
        return false;
    }
    const Slot& s = g_slots[idx];
    if (!send_setpos(s.x, s.y, s.z)) {
        return false;
    }
    log::info("tp: teleport to '%s' (%.2f, %.2f, %.2f)", s.name,
              static_cast<double>(s.x), static_cast<double>(s.y),
              static_cast<double>(s.z));
    return true;
}

bool remove_at(int idx)
{
    if (idx < 0 || idx >= static_cast<int>(g_slots.size())) {
        return false;
    }
    g_slots.erase(g_slots.begin() + idx);
    write_slots();
    return true;
}

int count()
{
    return static_cast<int>(g_slots.size());
}

void get_slot(int idx, char* name, int cap, float* x, float* y, float* z)
{
    if (idx < 0 || idx >= static_cast<int>(g_slots.size())) {
        if (name && cap > 0) {
            name[0] = '\0';
        }
        return;
    }
    const Slot& s = g_slots[idx];
    if (name && cap > 0) {
        std::snprintf(name, static_cast<std::size_t>(cap), "%s", s.name);
    }
    if (x) {
        *x = s.x;
    }
    if (y) {
        *y = s.y;
    }
    if (z) {
        *z = s.z;
    }
}

float lerp_step()
{
    return g_lerp_step;
}

void set_lerp_step(float units)
{
    g_lerp_step = clampf(units, kLerpStepMin, kLerpStepMax);
}

float lerp_speed()
{
    return g_lerp_speed;
}

void set_lerp_speed(float steps_per_second)
{
    g_lerp_speed = clampf(steps_per_second, kLerpSpeedMin, kLerpSpeedMax);
}

void persist()
{
    write_slots();
}

}  // namespace tp
}  // namespace specter::features
