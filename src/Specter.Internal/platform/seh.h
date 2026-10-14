// Specter.Internal — SEH guard for code that must not take the game down.
//
// WHY: we run our own code from inside the game's main loop, in a DLL that is
// manually mapped, calling into a JIT whose errors are signalled by longjmp.
// A mistake there does not return an error code — it tears down the process.
//
// MSVC and clang-cl lower __try/__except to real SEH, and SEH needs no CRT
// runtime support, so it is available here even though we have no CRT. That
// makes it the only guard that actually works in this environment: a C++
// try/catch would depend on unwinding tables set up by a runtime we never had.
//
// The rule this encodes: an access violation in OUR code is swallowed and
// logged, because losing a frame is not worth losing the game. Anything else is
// re-thrown, so a real fault elsewhere in the process is still reported by the
// system instead of being hidden by us.
//
// USAGE — SEH has no block scope, and __try/__except may not appear in a
// function with non-trivial destructors in scope, so the guard is the
// function's early return:
//
//     void pump(void* self)
//     {
//         SPECTER_SEH_BEGIN
//         ...
//         SPECTER_SEH_END("lua: work skipped for this frame")
//     }
//
// Keep the guarded function's locals POD.

#pragma once

#include <Windows.h>

#include "platform/log.h"

namespace specter::seh {

// Filter for __except. Logs the code and address of EVERY exception — so a Lua
// panic or an escaping C++ exception is visible on the pipe too, not just
// access violations — then swallows only the ones that are ours to swallow.
inline int filter(unsigned long code, EXCEPTION_POINTERS* ep)
{
    const void* addr = (ep != nullptr && ep->ExceptionRecord != nullptr)
                           ? ep->ExceptionRecord->ExceptionAddress
                           : nullptr;
    log::error("seh: exception code=0x%08lX at %p", code, addr);
    return code == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER
                                              : EXCEPTION_CONTINUE_SEARCH;
}

}  // namespace specter::seh

#define SPECTER_SEH_BEGIN                     \
    bool specter_seh_faulted = false;         \
    __try {

// `specter_seh_faulted` must still be in scope at the closing brace, so the
// whole guarded function must live inside the pair.
#define SPECTER_SEH_END(msg)                                              \
    }                                                                    \
    __except (::specter::seh::filter(GetExceptionCode(),                   \
                                     GetExceptionInformation())) {        \
        specter_seh_faulted = true;                                       \
        ::specter::log::error("%s", (msg));                               \
    }                                                                    \
    if (specter_seh_faulted) {                                            \
        return;                                                           \
    }