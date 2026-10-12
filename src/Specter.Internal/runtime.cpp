// Specter.Internal — implementation of the IL2CPP runtime seam.

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "runtime.h"
#include "il2cpp-api.h"
#include "log.h"

namespace specter {
namespace runtime {

uintptr_t module_base()
{
    return reinterpret_cast<uintptr_t>(GetModuleHandleW(L"GameAssembly.dll"));
}

bool initialize()
{
    if (module_base() == 0) {
        return false;
    }

    // The IL2CPP VM API is not reachable through `il2cpp_*` names (stripped),
    // but the functions are exported under `mono_*` compatibility names: a
    // curated, body-verified set is resolved here, once.
    //
    // Per-method pointers from appdata/il2cpp-functions.h are offsets relative
    // to module_base() and need no resolution.
    api::resolve();

    log::info("runtime: GameAssembly.dll mapped");
    return true;
}

// ---------------------------------------------------------------------------
// self_check(): first feature — prove the resolved API from inside the
// process. Log-only; any failure is isolated to its own log line.
// ---------------------------------------------------------------------------

static const char* image_name_of(const Il2CppImage* image)
{
    if (!image) {
        return "(no image)";
    }
    const char* n = specter::api::table().image_get_name(image);
    return n ? n : "(unknown)";
}

void self_check()
{
    auto& t = api::table();
    if (!api::ready()) {
        log::error("self_check: runtime API not ready");
        return;
    }

    // 1) Root domain.
    Il2CppDomain* domain = t.get_root_domain();
    if (!domain) {
        log::error("self_check: no root domain");
        return;
    }
    log::info("self_check: root domain %p", (void*)domain);

    // 2) Managed string round-trip through the VM (allocates on the GC heap).
    Il2CppString* s = t.string_new(domain, "specter-self-check");
    if (!s) {
        log::error("self_check: mono_string_new failed");
        return;
    }
    const int32_t len = t.string_length(s);
    const Il2CppChar* chars = t.string_chars(s);
    if (len > 0) {
        log::info("self_check: string_new -> len=%d first=U+%04X", len, chars[0]);
    } else {
        log::info("self_check: string_new -> len=%d", len);
    }

    // 3) Assembly enumeration on the root domain.
    void* iter = nullptr;
    int count = 0;
    const char* first_names[3] = { nullptr, nullptr, nullptr };
    for (Il2CppAssembly* asm_; (asm_ = t.domain_get_assemblies_iter(domain, &iter)) != nullptr;) {
        Il2CppImage* image = asm_ ? asm_->image : nullptr;  // Il2CppAssembly.image @0 (stable layout)
        if (count < 3) {
            first_names[count] = image_name_of(image);
        }
        ++count;
        if (count > 64) {  // stay defensive
            log::info("self_check: assembly enumeration capped at 64");
            break;
        }
    }
    log::info("self_check: %d assemblies (first: %s, %s, %s)",
              count,
              first_names[0] ? first_names[0] : "(?)",
              first_names[1] ? first_names[1] : "(?)",
              first_names[2] ? first_names[2] : "(?)");

    // 4) Class introspection: AppFacade (main game facade, RVA from the dump)
    //    reached through the generated static TypeInfo table.
    if (!app::AppFacade__TypeInfo || !*app::AppFacade__TypeInfo) {
        log::error("self_check: AppFacade TypeInfo not initialized in the SDK table");
        return;
    }
    Il2CppClass* klass = reinterpret_cast<Il2CppClass*>(*app::AppFacade__TypeInfo);
    const char* cname = t.class_get_name(klass);
    const char* cns = t.class_get_namespace(klass);
    const uint16_t nmethods = t.class_num_methods(klass);
    const uint16_t nfields = t.class_num_fields(klass);
    log::info("self_check: class=%s.%s methods=%u fields=%u image=%s",
              cns ? cns : "", cname ? cname : "(?)",
              nmethods, nfields,
              image_name_of(t.class_get_image(klass)));

    void* mit = nullptr;
    for (int i = 0; i < 3; ++i) {
        MethodInfo* m = t.class_get_methods(klass, &mit);
        if (!m) {
            break;
        }
        const char* mn = t.method_get_name(m);
        log::info("self_check:   method[%d]=%s", i, mn ? mn : "(?)");
    }
}

}  // namespace runtime
}  // namespace specter