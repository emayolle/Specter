// Specter.Internal — the interface of the injected runtime.
//
// This is the whole surface the DLL presents: bring the runtime up, tear it
// down. Everything else (locating GameAssembly, resolving the IL2CPP API,
// hooks, features) is implementation behind these two calls.

#pragma once

namespace specter {

// Bring Specter up. Called once from the injected thread (Run()).
// Returns true if the runtime is ready. Idempotent.
bool start();

// Tear down and detach (best effort). Called on process detach.
void stop();

}  // namespace specter
