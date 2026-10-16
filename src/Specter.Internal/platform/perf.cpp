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
std::atomic<long long> g_last_report{0};

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

    const long long ov = g_ns[kOverlay].exchange(0, std::memory_order_relaxed);
    const long long pu = g_ns[kPump].exchange(0, std::memory_order_relaxed);
    const long long nf = g_frames.exchange(0, std::memory_order_relaxed);

    const double fps =
        nf > 0 ? static_cast<double>(nf) * 1e9 / static_cast<double>(dt) : 0.0;
    const double budget_ms = fps > 0.0 ? 1000.0 / fps : 0.0;
    const double den = nf > 0 ? static_cast<double>(nf) : 1.0;

    // CHAQUE NOMBRE EST PAR FRAME, PAS PAR SECONDE.
    //
    // g_ns accumule toute la seconde. Sans diviser par le nombre de frames, le
    // log disait "overlay 2.00 ms (12%)" en face d'un budget de 16.7 ms : vrai
    // pour la seconde, absurde pour une frame. Divise, c'est 0.027 ms, soit
    // 0.2 %. Un compteur qui exagre notre cout de quarante fois fait perdre du
    // temps au lieu d'en economiser -- et c'est exactement ce qu'a produit la
    // premiere version.
    const double ov_ms = static_cast<double>(ov) / 1e6 / den;
    const double pu_ms = static_cast<double>(pu) / 1e6 / den;
    const double tot_ms = ov_ms + pu_ms;

    // Le budget est calcule sur NOTRE fps, pas sur 16.7 : a 143 fps une frame
    // dure 7.0 ms, et dire "12% de 16.7" a ce moment-la n'aurait rien voulu
    // dire. Le pourcentage ne vaut que par rapport au budget reel de l'instant.
    log::info("perf: %5.1f fps (budget %4.1f ms)  |  overlay %5.3f ms  |  "
              "pump %5.3f ms  |  notre total %5.3f ms = %4.1f%% du budget",
              fps, budget_ms, ov_ms, pu_ms, tot_ms,
              budget_ms > 0.0 ? tot_ms / budget_ms * 100.0 : 0.0);

    g_last_report.store(t, std::memory_order_relaxed);
    return true;
}

}  // namespace perf
}  // namespace specter