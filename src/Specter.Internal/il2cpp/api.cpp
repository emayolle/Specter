// Specter.Internal — export-name resolution of the IL2CPP VM API.

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "il2cpp/api.h"
#include "platform/log.h"

namespace specter {
namespace il2cpp {

static Table g_table;

Table& table() { return g_table; }

namespace {

template <typename T>
bool bind(HMODULE module, const char* export_name, T& slot)
{
    void* p = reinterpret_cast<void*>(GetProcAddress(module, export_name));
    if (!p) {
        return false;
    }
    slot = reinterpret_cast<T>(p);
    return true;
}

}  // namespace

int resolve()
{
    HMODULE module = GetModuleHandleW(L"GameAssembly.dll");
    if (!module) {
        return 0;
    }

    Table& t = g_table;
    int bound = 0;

    // Bind every body-verified export we rely on. The tiny generic accessors
    // are real functions (see api.h); the inert stubs are not listed.
    auto req = [&](const char* name, auto& slot) {
        if (bind(module, name, slot)) {
            ++bound;
        } else {
            log::error("api: export missing: %s", name);
        }
    };

    req(names::get_root_domain, t.get_root_domain);
    req(names::domain_get_assemblies_iter, t.domain_get_assemblies_iter);
    req(names::string_new, t.string_new);
    req(names::string_length, t.string_length);
    req(names::string_chars, t.string_chars);
    req(names::class_get_name, t.class_get_name);
    req(names::class_get_namespace, t.class_get_namespace);
    req(names::class_get_image, t.class_get_image);
    req(names::class_get_type, t.class_get_type);
    req(names::class_get_flags, t.class_get_flags);
    req(names::class_num_methods, t.class_num_methods);
    req(names::class_num_fields, t.class_num_fields);
    req(names::class_get_methods, t.class_get_methods);
    req(names::class_get_interfaces, t.class_get_interfaces);
    req(names::object_get_type, t.object_get_type);
    req(names::type_get_class, t.type_get_class);
    req(names::method_get_name, t.method_get_name);
    req(names::method_get_class, t.method_get_class);
    req(names::image_get_name, t.image_get_name);
    req(names::image_get_assembly, t.image_get_assembly);

    log::info("api: resolved %d VM functions from GameAssembly.dll exports", bound);
    return bound;
}

bool ready()
{
    return g_table.get_root_domain && g_table.domain_get_assemblies_iter &&
           g_table.string_new && g_table.string_length && g_table.string_chars &&
           g_table.class_get_name && g_table.class_get_namespace &&
           g_table.class_num_methods && g_table.class_get_methods &&
           g_table.method_get_name;
}

}  // namespace api
}  // namespace specter