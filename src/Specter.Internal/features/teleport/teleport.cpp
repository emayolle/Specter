#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "features/console/console.h"
#include "features/teleport/teleport.h"
#include "platform/log.h"

namespace specter::features {
namespace teleport {
namespace {

constexpr int kMaxSlots = 64;
constexpr std::size_t kNameCap = 32;
const wchar_t* kFile = L"Z:\\tmp\\specter-tp.json";
const wchar_t* kFileTmp = L"Z:\\tmp\\specter-tp.json.tmp";

// Floraisons (Leyline Flowers) live in their own file so a bad/hand-edited
// entry can never corrupt the saved teleport slots.
const wchar_t* kFloraFile = L"Z:\\tmp\\specter-floraisons.json";
const wchar_t* kFloraFileTmp = L"Z:\\tmp\\specter-floraisons.json.tmp";
constexpr int kMaxFlora = 256;

// Open-world scenes searched for both Leyline Flower marks and Teleportation
// Array crystals. Every scene's mark data is queried from Lua on request;
// keeping the list short makes the scan effectively instant (a wrong scene id
// is simply skipped).
constexpr int kWorldScenes[] = {3000, 3003};

// Waypoints (the "Teleportation Array" crystals) also live in their own file.
const wchar_t* kWpFile = L"Z:\\tmp\\specter-waypoints.json";
const wchar_t* kWpFileTmp = L"Z:\\tmp\\specter-waypoints.json.tmp";
constexpr int kMaxWp = 512;
constexpr int kMaxWpName = 64;
// markConfigId of a crystal (infoImage $UI_Img_Map_Preview_TeleportationArray.png,
// POIIcon $UI_Icon_POI_Explore_Transmit.png). Unlike the Floraisons these are
// not a distinct markType: they share markType 0 with other map marks, so the
// scan filters on the config id instead.
constexpr int kWpMarkConfig = 10406;

// Lerp tuning bounds (defaults are the fastest values found to hold live:
// step 5.5 u at 120 steps/s ~= 660 u/s).
constexpr float kLerpStepDef = 5.5f;
constexpr float kLerpStepMin = 0.25f;
constexpr float kLerpStepMax = 20.0f;
constexpr float kLerpSpeedDef = 120.0f;
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

// One Leyline Flower: the zone ("large area") it belongs to and its position.
struct Floraison
{
    int zone = 0;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

std::vector<Floraison> g_flora;
// Accumulates "F ..." lines of the result currently being parsed; committed to
// g_flora when the terminating marker arrives.
std::vector<Floraison> g_flora_tmp;

// One "Teleportation Array" crystal: the zone it reveals plus its localized
// name. Several crystals can share a zone.
struct Waypoint
{
    int zone = 0;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    char name[kMaxWpName] = {};
};

std::vector<Waypoint> g_wp;
// Accumulates "W ..." lines of the result currently being parsed; committed to
// g_wp when the terminating marker arrives.
std::vector<Waypoint> g_wp_tmp;

// One scan produces both lists (the TP channel keeps a single result buffer),
// so a single "busy" flag drives the UI spinner.
bool g_marks_pending = false;

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

// Floraisons are written as one "<zone> <x> <y> <z>" line per entry. Order is
// by zone so the on-disk list (and the panel) stays stable.
void sort_flora(std::vector<Floraison>& v)
{
    for (std::size_t i = 1; i < v.size(); ++i) {
        Floraison k = v[i];
        std::size_t j = i;
        while (j > 0 && v[j - 1].zone > k.zone) {
            v[j] = v[j - 1];
            --j;
        }
        v[j] = k;
    }
    // Drop duplicate zones (a scene may describe the same flower twice).
    std::vector<Floraison> out;
    for (const Floraison& f : v) {
        if (!out.empty() && out.back().zone == f.zone) {
            continue;
        }
        out.push_back(f);
    }
    v.swap(out);
}

void write_floraisons()
{
    std::string out;
    out.reserve(g_flora.size() * 40 + 16);
    for (const Floraison& f : g_flora) {
        char line[80];
        std::snprintf(line, sizeof(line), "%d %.6f %.6f %.6f\n", f.zone,
                      static_cast<double>(f.x), static_cast<double>(f.y),
                      static_cast<double>(f.z));
        out += line;
    }
    HANDLE h = ::CreateFileW(kFloraFileTmp, GENERIC_WRITE, 0, nullptr,
                             CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) {
        log::error("tp: can't write %ls", kFloraFileTmp);
        return;
    }
    DWORD wrote = 0;
    ::WriteFile(h, out.data(), static_cast<DWORD>(out.size()), &wrote, nullptr);
    ::CloseHandle(h);
    ::MoveFileExW(kFloraFileTmp, kFloraFile, MOVEFILE_REPLACE_EXISTING);
}

void load_floraisons()
{
    g_flora.clear();
    HANDLE h = ::CreateFileW(kFloraFile, GENERIC_READ,
                             FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                             OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) {
        return;
    }
    static char buf[32768];
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
        while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') {
            ++p;
        }
        if (!*p) {
            break;
        }
        if (*p == '@' || *p == '#') {  // comment line
            const char* eol = std::strchr(p, '\n');
            p = eol ? eol + 1 : p + std::strlen(p);
            continue;
        }
        float x = 0.0f, y = 0.0f, z = 0.0f;
        int zone = 0;
        if (std::sscanf(p, "%d %f %f %f", &zone, &x, &y, &z) == 4 &&
            g_flora.size() < kMaxFlora) {
            Floraison f;
            f.zone = zone;
            f.x = x;
            f.y = y;
            f.z = z;
            g_flora.push_back(f);
        }
        const char* eol = std::strchr(p, '\n');
        p = eol ? eol + 1 : p + std::strlen(p);
    }
    sort_flora(g_flora);
}

// Waypoints are written as "<zone> <x> <y> <z> <name>"; the name is always last
// because it may contain spaces. Sorted by zone then x for a stable list.
void sort_waypoints(std::vector<Waypoint>& v)
{
    for (std::size_t i = 1; i < v.size(); ++i) {
        Waypoint k = v[i];
        std::size_t j = i;
        while (j > 0 && (v[j - 1].zone > k.zone ||
                         (v[j - 1].zone == k.zone && v[j - 1].x > k.x))) {
            v[j] = v[j - 1];
            --j;
        }
        v[j] = k;
    }
    std::vector<Waypoint> out;
    for (const Waypoint& w : v) {
        bool dup = false;
        for (const Waypoint& o : out) {
            if (o.zone == w.zone && o.x == w.x && o.y == w.y && o.z == w.z) {
                dup = true;
                break;
            }
        }
        if (!dup) {
            out.push_back(w);
        }
    }
    v.swap(out);
}

void write_waypoints()
{
    std::string out;
    out.reserve(g_wp.size() * 96 + 16);
    for (const Waypoint& w : g_wp) {
        char line[256];
        std::snprintf(line, sizeof(line), "%d %.6f %.6f %.6f %s\n", w.zone,
                      static_cast<double>(w.x), static_cast<double>(w.y),
                      static_cast<double>(w.z), w.name);
        out += line;
    }
    HANDLE h = ::CreateFileW(kWpFileTmp, GENERIC_WRITE, 0, nullptr,
                             CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) {
        log::error("tp: can't write %ls", kWpFileTmp);
        return;
    }
    DWORD wrote = 0;
    ::WriteFile(h, out.data(), static_cast<DWORD>(out.size()), &wrote, nullptr);
    ::CloseHandle(h);
    ::MoveFileExW(kWpFileTmp, kWpFile, MOVEFILE_REPLACE_EXISTING);
}

void load_waypoints()
{
    g_wp.clear();
    HANDLE h = ::CreateFileW(kWpFile, GENERIC_READ,
                             FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                             OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) {
        return;
    }
    static char buf[65536];
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
        while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') {
            ++p;
        }
        if (!*p) {
            break;
        }
        if (*p == '@' || *p == '#') {  // comment line
            const char* eol = std::strchr(p, '\n');
            p = eol ? eol + 1 : p + std::strlen(p);
            continue;
        }
        int zone = 0;
        int off = 0;
        float x = 0.0f, y = 0.0f, z = 0.0f;
        if (std::sscanf(p, "%d %f %f %f %n", &zone, &x, &y, &z, &off) == 4 &&
            g_wp.size() < kMaxWp) {
            Waypoint w;
            w.zone = zone;
            w.x = x;
            w.y = y;
            w.z = z;
            const char* nm = p + off;
            std::size_t nl = 0;
            while (nm[nl] && nm[nl] != '\r' && nm[nl] != '\n' &&
                   nl + 1 < sizeof(w.name)) {
                w.name[nl] = nm[nl];
                ++nl;
            }
            w.name[nl] = '\0';
            g_wp.push_back(w);
        }
        const char* eol = std::strchr(p, '\n');
        p = eol ? eol + 1 : p + std::strlen(p);
    }
    sort_waypoints(g_wp);
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
    return features::console::submit(features::console::kChannelTeleport, code, n);
}

// Builds and queues one scan for both fast-travel lists. It walks the
// open-world scenes once, printing a "F <zone> <x> <y> <z>" line per Leyline
// Flower (markType 26) and a "W <zone> <x> <y> <z> <name>" line per
// Teleportation Array crystal (markConfigId 10406), then "MARKS_DONE".
// handle_result() parses it. Doing both in one chunk matters: the TP channel
// keeps a single result buffer, so two queued probes would clobber each other.
// The scan is bounded to a handful of scenes, so it returns within a frame.
bool send_marks_probe()
{
    std::string code;
    code.reserve(1800);
    code +=
        "local SU=require('Common.Utils.SceneUtils')\n"
        "local CTU=require('Utils.ClientTextUtils')\n"
        "local e=pg.me\n"
        "local set={}\n"
        "local function add(s) if s and s>100 then set[s]=true end end\n"
        "if e and e.sceneId then add(e.sceneId) end\n"
        "local m=pg.game and pg.game.map\n"
        "if m then add(m.sceneId) add(m.mainSceneId) end\n";
    for (int sid : kWorldScenes) {
        code += "add(";
        code += std::to_string(sid);
        code += ")\n";
    }
    code +=
        "local seen={}\n"
        "for sid in pairs(set) do\n"
        "  local ok,pts=pcall(SU.getSceneMarkPointData,sid)\n"
        "  if ok and type(pts)=='table' then\n"
        "    for id,p in pairs(pts) do\n"
        "      if seen[id] then\n"
        "      elseif p.markType==26 then\n"
        "        seen[id]=true\n"
        "        local mp=p.markPosition\n"
        "        if mp then print(string.format('F %d %.2f %.2f %.2f',"
        "p.largeAreaId or 0,mp[1],mp[2],mp[3])) end\n"
        "      elseif p.markConfigId==";
    code += std::to_string(kWpMarkConfig);
    code +=
        " then\n"
        "        seen[id]=true\n"
        "        local mp=p.markPosition\n"
        "        if mp then\n"
        "          local nm=''\n"
        "          if p.infoTitle then\n"
        "            local o,t=pcall(CTU.getLocalizationText,p.infoTitle)\n"
        "            if o and t then nm=tostring(t) end\n"
        "          end\n"
        "          nm=nm:gsub('%s+',' ')\n"
        "          print(string.format('W %d %.2f %.2f %.2f %s',"
        "p.largeAreaId or 0,mp[1],mp[2],mp[3],nm))\n"
        "        end\n"
        "      end\n"
        "    end\n"
        "  end\n"
        "end\n"
        "print('MARKS_DONE')\n";
    return features::console::submit(features::console::kChannelTeleport, code.c_str(), static_cast<int>(code.size()));
}

}  // namespace

bool init()
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

    load_floraisons();
    log::info("tp: %d Floraison(s) loaded from /tmp/specter-floraisons.json",
              static_cast<int>(g_flora.size()));

    load_waypoints();
    log::info("tp: %d waypoint(s) loaded from /tmp/specter-waypoints.json",
              static_cast<int>(g_wp.size()));
    return true;
}

void request_position()
{
    features::console::submit(features::console::kChannelTeleport, kPosProbe, static_cast<int>(sizeof(kPosProbe) - 1));
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
    // One result may hold several lines: a position ("P x y z space"), a
    // fast-travel scan (a run of "F <zone> <x> <y> <z>" and
    // "W <zone> <x> <y> <z> <name>" lines ending in "MARKS_DONE"), or an error.
    // Handle each line on its own so the probes can share the buffer.
    const char* p = text;
    while (*p) {
        const char* eol = std::strchr(p, '\n');
        std::size_t len =
            eol ? static_cast<std::size_t>(eol - p) : std::strlen(p);
        while (len > 0 && (p[len - 1] == '\r' || p[len - 1] == ' ' ||
                           p[len - 1] == '\t')) {
            --len;
        }
        if (len > 0 && p[0] == 'F' && (p[1] == ' ' || p[1] == '\t')) {
            int zone = 0;
            float x = 0.0f, y = 0.0f, z = 0.0f;
            if (std::sscanf(p + 1, "%d %f %f %f", &zone, &x, &y, &z) == 4 &&
                g_flora_tmp.size() < kMaxFlora) {
                Floraison f;
                f.zone = zone;
                f.x = x;
                f.y = y;
                f.z = z;
                g_flora_tmp.push_back(f);
            }
        } else if (len > 1 && p[0] == 'W' && (p[1] == ' ' || p[1] == '\t')) {
            int zone = 0;
            int off = 0;
            float x = 0.0f, y = 0.0f, z = 0.0f;
            if (std::sscanf(p + 1, "%d %f %f %f %n", &zone, &x, &y, &z,
                            &off) == 4 &&
                g_wp_tmp.size() < kMaxWp) {
                Waypoint w;
                w.zone = zone;
                w.x = x;
                w.y = y;
                w.z = z;
                const char* nm = p + 1 + off;
                std::size_t nl = 0;
                while (nm[nl] && nm[nl] != '\r' && nm[nl] != '\n' &&
                       nl + 1 < sizeof(w.name)) {
                    w.name[nl] = nm[nl];
                    ++nl;
                }
                w.name[nl] = '\0';
                g_wp_tmp.push_back(w);
            }
        } else if (std::strncmp(p, "MARKS_DONE", 10) == 0) {
            // The scan only reports what it found, so keep the cached list if
            // one of the two came back empty (e.g. the player is in a scene
            // without marks yet): never wipe good data with a partial answer.
            if (!g_flora_tmp.empty()) {
                sort_flora(g_flora_tmp);
                g_flora = g_flora_tmp;
                write_floraisons();
            }
            if (!g_wp_tmp.empty()) {
                sort_waypoints(g_wp_tmp);
                g_wp = g_wp_tmp;
                write_waypoints();
            }
            log::info(
                "tp: fetched %d Floraison(s) and %d waypoint(s) from the game",
                static_cast<int>(g_flora.size()),
                static_cast<int>(g_wp.size()));
            g_flora_tmp.clear();
            g_wp_tmp.clear();
            g_marks_pending = false;
        } else if (std::strncmp(p, "ERROR", 5) == 0) {
            g_flora_tmp.clear();
            g_wp_tmp.clear();
            g_marks_pending = false;
        } else {
            float x = 0.0f, y = 0.0f, z = 0.0f;
            int sp = 1;
            if (parse_position(p, &x, &y, &z, &sp)) {
                g_cur[0] = x;
                g_cur[1] = y;
                g_cur[2] = z;
                g_cur_space = sp;
                g_cur_valid = true;
            }
        }
        p = eol ? eol + 1 : p + std::strlen(p);
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

void request_marks()
{
    g_flora_tmp.clear();
    g_wp_tmp.clear();
    if (send_marks_probe()) {
        g_marks_pending = true;
    } else {
        log::error("tp: can't request the fast-travel lists (bridge not ready)");
    }
}

bool marks_pending()
{
    return g_marks_pending;
}

int floraison_count()
{
    return static_cast<int>(g_flora.size());
}

void get_floraison(int idx, int* zone, float* x, float* y, float* z)
{
    if (idx < 0 || idx >= static_cast<int>(g_flora.size())) {
        return;
    }
    const Floraison& f = g_flora[idx];
    if (zone) {
        *zone = f.zone;
    }
    if (x) {
        *x = f.x;
    }
    if (y) {
        *y = f.y;
    }
    if (z) {
        *z = f.z;
    }
}

bool teleport_to_floraison(int idx)
{
    if (idx < 0 || idx >= static_cast<int>(g_flora.size())) {
        return false;
    }
    const Floraison& f = g_flora[idx];
    if (!send_setpos(f.x, f.y, f.z)) {
        return false;
    }
    log::info("tp: teleport to Floraison zone %d (%.2f, %.2f, %.2f)", f.zone,
              static_cast<double>(f.x), static_cast<double>(f.y),
              static_cast<double>(f.z));
    return true;
}

int waypoint_count()
{
    return static_cast<int>(g_wp.size());
}

void get_waypoint(int idx, int* zone, char* name, int cap, float* x, float* y,
                  float* z)
{
    if (idx < 0 || idx >= static_cast<int>(g_wp.size())) {
        if (name && cap > 0) {
            name[0] = '\0';
        }
        return;
    }
    const Waypoint& w = g_wp[idx];
    if (zone) {
        *zone = w.zone;
    }
    if (name && cap > 0) {
        std::snprintf(name, static_cast<std::size_t>(cap), "%s", w.name);
    }
    if (x) {
        *x = w.x;
    }
    if (y) {
        *y = w.y;
    }
    if (z) {
        *z = w.z;
    }
}

bool teleport_to_waypoint(int idx)
{
    if (idx < 0 || idx >= static_cast<int>(g_wp.size())) {
        return false;
    }
    const Waypoint& w = g_wp[idx];
    if (!send_setpos(w.x, w.y, w.z)) {
        return false;
    }
    log::info("tp: teleport to waypoint '%s' zone %d (%.2f, %.2f, %.2f)",
              w.name, w.zone, static_cast<double>(w.x),
              static_cast<double>(w.y), static_cast<double>(w.z));
    return true;
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
