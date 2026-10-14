// Specter.Internal — resolution of the IL2CPP VM API of Aniimo.
//
// GameAssembly.dll strips the canonical `il2cpp_*` export names: NetEase
// renamed the whole export surface (245 `i…` obfuscated plus a `mono_*`
// compatibility set) and removed the symbol name strings, so neither the
// generated appdata/il2cpp-api-functions.h (empty) nor a GetProcAddress on an
// `il2cpp_*` name can reach the runtime.
//
// The VM functions are still exported — just under other names. We resolve a
// curated set of `mono_*` exports whose bodies were *decompiled and verified*
// on the real binary (see docs/ARCHITECTURE.md, "Resolution de l'API").
//
// Body-verified facts this module depends on:
//   - the classic accessors are tiny, DISTINCT functions (e.g. string_length
//     reads Il2CppString.length at +16, string_chars returns +20). Functions
//     that share one body across many names are either real generic
//     accessors (image_get_name = *(qword*)image) or inert stubs
//     (mono_field_set_value = empty body) and are never used here.
//   - Unity 2023.2 refactored Il2CppClass: name/namespace/methods live in an
//     opaque class-data block (class+80). The accessors below are the safe
//     way to reach them; do NOT walk Il2CppClass fields directly.

#pragma once

#include "il2cpp-appdata.h"  // SDK types: Il2CppDomain, Il2CppClass, MethodInfo, ...

namespace specter {
namespace il2cpp {

// Export names (constants kept here so the resolver and the docs agree).
namespace names {

inline constexpr const char* get_root_domain           = "mono_get_root_domain";
inline constexpr const char* domain_get_assemblies_iter = "mono_domain_get_assemblies_iter";
inline constexpr const char* string_new                = "mono_string_new";
inline constexpr const char* string_length             = "mono_string_length";
inline constexpr const char* string_chars              = "mono_string_chars";
inline constexpr const char* class_get_name            = "mono_class_get_name";
inline constexpr const char* class_get_namespace       = "mono_class_get_namespace";
inline constexpr const char* class_get_image           = "mono_class_get_image";
inline constexpr const char* class_get_type            = "mono_class_get_type";
inline constexpr const char* class_get_flags           = "mono_class_get_flags";
inline constexpr const char* class_num_methods         = "mono_class_num_methods";
inline constexpr const char* class_num_fields          = "mono_class_num_fields";
inline constexpr const char* class_get_methods         = "mono_class_get_methods";
inline constexpr const char* class_get_interfaces      = "mono_class_get_interfaces";
inline constexpr const char* object_get_type           = "mono_object_get_type";
inline constexpr const char* type_get_class            = "mono_type_get_class";
inline constexpr const char* method_get_name           = "mono_method_get_name";
inline constexpr const char* method_get_class          = "mono_method_get_class";
inline constexpr const char* image_get_name            = "mono_image_get_name";
inline constexpr const char* image_get_assembly        = "mono_image_get_assembly";

}  // namespace names

// Body-verified function pointers. All null until resolve() succeeds.
struct Table
{
    // domain
    Il2CppDomain* (*get_root_domain)()                                     = nullptr;
    Il2CppAssembly* (*domain_get_assemblies_iter)(Il2CppDomain*, void**)   = nullptr;

    // strings (Il2CppString layout is stable; length@+16, chars@+20)
    Il2CppString* (*string_new)(Il2CppDomain*, const char*)                = nullptr;
    int32_t       (*string_length)(const Il2CppString*)                    = nullptr;
    Il2CppChar*   (*string_chars)(const Il2CppString*)                     = nullptr;

    // classes — names/namespaces/methods go through the class-data block
    const char*   (*class_get_name)(Il2CppClass*)                          = nullptr;
    const char*   (*class_get_namespace)(Il2CppClass*)                     = nullptr;
    Il2CppImage*  (*class_get_image)(Il2CppClass*)                         = nullptr;
    Il2CppType*   (*class_get_type)(Il2CppClass*)                          = nullptr;
    uint32_t      (*class_get_flags)(Il2CppClass*)                         = nullptr;
    uint16_t      (*class_num_methods)(Il2CppClass*)                       = nullptr;
    uint16_t      (*class_num_fields)(Il2CppClass*)                        = nullptr;
    MethodInfo*   (*class_get_methods)(Il2CppClass*, void**)               = nullptr;
    Il2CppClass*  (*class_get_interfaces)(Il2CppClass*, void**)            = nullptr;

    // types and objects
    Il2CppType*   (*object_get_type)(Il2CppObject*)                        = nullptr;
    Il2CppClass*  (*type_get_class)(Il2CppType*)                           = nullptr;

    // methods (MethodInfo layout: name@+24, klass@+32, verified)
    const char*   (*method_get_name)(const MethodInfo*)                    = nullptr;
    Il2CppClass*  (*method_get_class)(const MethodInfo*)                   = nullptr;

    // images (Il2CppImage: name@+0, assembly@+16, verified)
    const char*   (*image_get_name)(const Il2CppImage*)                    = nullptr;
    Il2CppAssembly* (*image_get_assembly)(const Il2CppImage*)              = nullptr;
};

// Resolve the table from the loaded GameAssembly.dll by export name. Returns
// the number of symbols actually bound (>0 = the runtime is reachable). Safe
// to call again. Never throws.
int resolve();

// The resolved table (zeroed until resolve() succeeds).
Table& table();

// True once resolve() bound every symbol it cares about.
bool ready();

}  // namespace api
}  // namespace specter