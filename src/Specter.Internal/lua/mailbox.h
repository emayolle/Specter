// Specter.Internal — cross-thread transport between the render thread and the
// game's Lua thread.
//
// WHY: the render thread (ImGui, the DXGI Present hook) must never touch the
// game's Lua state. It can only *submit*; the Lua thread (see lua/pump.h) runs
// it and *publishes* the result back. Both halves need a rendez-vous point.
//
// This is that point, and nothing more. It deliberately knows nothing about
// Lua, about chunks, or about what any particular feature does with the bytes —
// so it stays trivially testable and reusable by every feature.
//
// INVARIANTS (the DLL is manually mapped, so they are not negotiable):
//   * a Mailbox is a POD with zero initialisation. No constructor runs at load
//     time — the CRT guard that would call it is not initialised for a manually
//     mapped image. `submit`/`publish` from another thread may therefore run
//     before any static initialisation happened.
//   * no `std::mutex`, no `std::function`, no heap. A CRITICAL_SECTION plus a
//     fixed-capacity POD slot array is the whole thing.
//
// The lock is created lazily on first use, but *safely*: it goes through
// InitOnceExecuteOnce, which guarantees exactly one initialiser runs however
// many threads race into it. (The pattern this replaces — a bare
// `if (!g_lock_ready) { InitializeCriticalSection(&g); g_lock_ready = true; }` —
// is a data race: two threads can both read `false` and both initialise.)

#pragma once

#include <atomic>
#include <cstddef>
#include <windows.h>

namespace specter::lua {

// Policy: what happens when a new item arrives and the mailbox is full.
struct Replace {
    // The oldest pending item is dropped in favour of the newcomer. Right for a
    // "submit a command" slot: the user wants the last thing they asked for, not
    // a backlog of superseded ones.
    static constexpr bool overwrites = true;
};

struct Drop {
    // The newcomer is discarded and `submit` returns false. Right for anything
    // where losing the oldest would corrupt state — a queued move, a result the
    // consumer must not miss.
    static constexpr bool overwrites = false;
};

// A bounded, thread-safe rendez-vous between one producer and one consumer.
//
// `Req` and `Res` must be PODs: they are stored inline, copied, and never
// constructed. Keeping them as two parameters is not decoration -- a feature
// that submits a 32 KB chunk and receives 48 KB of text would otherwise pay for
// a second 32 KB request slot it never uses.
template <typename Req, typename Res = Req, std::size_t Slots = 1,
          typename Policy = Replace>
class Mailbox {
public:
    Mailbox() = default;

    Mailbox(const Mailbox&) = delete;
    Mailbox& operator=(const Mailbox&) = delete;

    // --- producer side (any thread) -----------------------------------------

    // Hand `v` to the consumer. Returns false only when the mailbox is full and
    // the policy is Drop.
    bool submit(const Req& v) {
        lock();
        bool ok = true;
        std::size_t slot;
        if (Policy::overwrites) {
            // Single-slot semantics: always the newest.
            slot = 0;
        } else {
            const std::size_t next = (m_sub_tail + 1) % Slots;
            if (next == m_sub_head) {
                ok = false;  // full
            }
            slot = m_sub_tail;
            m_sub_tail = next;
        }
        if (ok) {
            m_pending[slot] = v;
            if (Policy::overwrites) {
                // With Replace there is no head/tail movement to observe, so
                // this flag IS the "something is waiting" signal. Without it
                // take_pending() would never see a single-slot submission.
                m_pending_ready = true;
            }
        }
        unlock();
        return ok;
    }

    // Publish a result back to the producer side. Never blocks, never fails:
    // a result nobody reads is not worth an error path.
    void publish(const Res& v) {
        lock();
        m_result = v;
        unlock();
        m_result_ready.store(true, std::memory_order_release);
    }

    // --- consumer side (the Lua thread) -------------------------------------

    // Take one pending item. Returns false when there is none. With Replace the
    // single slot is cleared; with Drop the FIFO advances.
    bool take_pending(Req& out) {
        lock();
        if (Policy::overwrites) {
            if (!m_pending_ready) {
                unlock();
                return false;
            }
            out = m_pending[0];
            m_pending_ready = false;
        } else {
            if (m_sub_head == m_sub_tail) {
                unlock();
                return false;
            }
            out = m_pending[m_sub_head];
            m_sub_head = (m_sub_head + 1) % Slots;
        }
        unlock();
        return true;
    }

    // --- producer side, result polling --------------------------------------

    // Take the published result. Single consumer: consumes it (returns false
    // next time).
    bool take_result(Res& out) {
        if (!m_result_ready.load(std::memory_order_acquire)) {
            return false;
        }
        lock();
        out = m_result;
        unlock();
        m_result_ready.store(false, std::memory_order_release);
        return true;
    }

    bool has_pending() const {
        lock();
        const bool any = Policy::overwrites ? m_pending_ready
                                            : (m_sub_head != m_sub_tail);
        unlock();
        return any;
    }

    bool has_result() const {
        return m_result_ready.load(std::memory_order_acquire);
    }

private:
    // InitOnceExecuteOnce passes `param` through untouched, so the routine gets
    // the section as an argument instead of reaching into `this`: it may run on
    // another thread, and `this` is not available during the very first call.
    static BOOL CALLBACK init_once_routine(PINIT_ONCE, PVOID param, PVOID*) {
        ::InitializeCriticalSection(static_cast<CRITICAL_SECTION*>(param));
        return TRUE;
    }

    void lock() {
        ::InitOnceExecuteOnce(&m_once, &init_once_routine, &m_lock, nullptr);
        ::EnterCriticalSection(&m_lock);
    }

    void unlock() { ::LeaveCriticalSection(&m_lock); }

    // Zero-initialised POD: safe to use before any dynamic initialisation.
    INIT_ONCE m_once = INIT_ONCE_STATIC_INIT;
    CRITICAL_SECTION m_lock;
    Req m_pending[Slots];
    Res m_result;
    std::size_t m_sub_head = 0;  // next read  (Drop policy)
    std::size_t m_sub_tail = 0;  // next write (Drop policy)
    bool m_pending_ready = false;
    std::atomic<bool> m_result_ready{false};
};

}  // namespace specter::lua