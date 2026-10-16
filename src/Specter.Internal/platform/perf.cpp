// Specter.Internal — per-frame cost meter. See perf.h for why.

#include "platform/perf.h"

#include <windows.h>

#include <atomic>

#include "platform/log.h"

namespace specter {
namespace perf {
namespace {

std::atomic<long long> g_ns[kSlotCount] = {};
std::atomic<long long> g_frames{0};

// GetTickCount64 has ~15 ms resolution, which is useless per frame. The
// performance counter is the only clock fine enough to time a frame.
long long now_ns_impl()
{
    LARGE_INTEGER f, c;
    if (!::QueryPerformanceFrequency(&f) || f.QuadPart == 0) {
        return 0;
    }
    ::QueryPerformanceCounter(&c);
    return (c.QuadPart * 1000000000LL) / f.QuadPart;
}

std::atomic<long long> g_last_report{0};

}  // namespace

long long now_ns()
{
    return now_ns_impl();
}

long long ns(Slot s)
{
    return g_ns[s & (kSlotCount - 1)].load(std::memory_order_relaxed);
}

void add(Slot s, long long delta)
{
    if (delta > 0) {
        g_ns[s & (kSlotCount - 1)].fetch_add(delta, std::memory_order_relaxed);
    }
}

void frame()
{
    g_frames.fetch_add(1, std::memory_order_relaxed);
}

long long frames()
{
    return g_frames.load(std::memory_order_relaxed);
}

bool report()
{
    const long long t = now_ns_impl();
    const long long last = g_last_report.load(std::memory_order_relaxed);
    if (last == 0) {
        g_last_report.store(t, std::memory_order_relaxed);
        return false;
    }
    const long long dt = t - last;
    if (dt < 1000000000LL) {  // moins d'une seconde
        return false;
    }

    const long long f0 = 0;
    (void)f0;
    const long long ov = g_ns[kOverlay].exchange(0, std::memory_order_relaxed);
    const long long pu = g_ns[kPump].exchange(0, std::memory_order_relaxed);
    const long long nf = g_frames.exchange(0, std::memory_order_relaxed);

    const double fps = nf > 0 ? (static_cast<double>(nf) * 1e9 / static_cast<double>(dt))
                              : 0.0;
    const double ov_ms = static_cast<double>(ov) / 1e6;
    const double pu_ms = static_cast<double>(pu) / 1e6;

    // Le pourcentage est la part du TEMPS MESURE, pas du temps total : il dit
    // combien de milli-secondes nous coute la frame, ce qui est la seule chose
    // qu'on peut comparer a un budget de 16.7 ms (60 fps).
    log::info("perf: %5.1f fps  |  overlay %6.2f ms  (%4.1f%% de 16.7)  |  "
              "pump %6.3f ms  |  notre total %5.2f ms",
              fps, ov_ms, ov_ms / 16.7 * 100.0, pu_ms, ov_ms + pu_ms);

    g_last_report.store(t, std::memory_order_relaxed);
    return true;
}

}  // namespace perf
}  // namespace specter