#!/usr/bin/env bash
# Embed scripts/init.lua into a C header, so the bootstrap travels inside the
# DLL instead of being read from disk at run time.
#
# Why embed rather than read a file:
#   - no path to get wrong on the game's side (Z:\... vs /home/...),
#   - no file IO on the Lua thread while a state is being built,
#   - and the script cannot go missing between build and run.
#
# Same technique nova uses for its InitScript (R"LUA_INIT(...)LUA_INIT").
#
# Re-run by tools/build-dll.sh whenever scripts/init.lua changes.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SRC="${ROOT}/scripts/init.lua"
OUT="${ROOT}/generated/lua_init.h"

[[ -f "${SRC}" ]] || { echo "absent: ${SRC}" >&2; exit 1; }

# `)LUA_INIT` inside the script would close the literal early. Refuse it rather
# than emit a header that does not compile for a reason nobody would connect to
# this file.
if grep -q ')LUA_INIT' "${SRC}"; then
    echo "ERREUR: ${SRC} contient ')LUA_INIT', ce qui fermerait le litteral." >&2
    exit 1
fi

mkdir -p "$(dirname "${OUT}")"
{
    echo "// AUTO-GENERE par tools/embed-lua.sh depuis scripts/init.lua."
    echo "// Ne pas editer a la main : editer scripts/init.lua et reconstruire."
    echo "#pragma once"
    echo
    echo "namespace specter::lua::init {"
    echo
    echo "static constexpr const char* kInitScript = R\"LUA_INIT("
    cat "${SRC}"
    echo ")LUA_INIT\";"
    echo
    echo "}  // namespace specter::lua::init"
} > "${OUT}"

printf "init embarque : %s -> %s (%s lignes)\n" \
    "scripts/init.lua" "generated/lua_init.h" "$(wc -l < "${SRC}")"