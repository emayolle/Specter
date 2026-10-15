#!/usr/bin/env bash
# Build and run the offline Lua binding test (tests/lua_binding).
#
# Runs on the host, against the system LuaJIT and the SAME vendored headers the
# DLL compiles against. It exists so that a change to the binding layer fails
# here, in a second, instead of in the game after an injection.
#
# Needs libluajit-5.1 (package luajit on most distributions) and clang++ with
# C++17. It does NOT need the game, the DLL, or Wine.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT="${ROOT}/generated/tests"

CXX="${CXX:-clang++}"
LUAJIT_INC="${LUAJIT_INC:-/usr/include/luajit-2.1}"
LUAJIT_LIB="${LUAJIT_LIB:--lluajit-5.1}"

# Prefer the system LuaJIT headers; fall back to the vendored 5.1 ones if the
# dev package is not installed, since the API surface used here is 5.1 either
# way.
INCS=(-I"${ROOT}/third_party/lua51" -I"${ROOT}/third_party/luabridge")
if [[ -d "${LUAJIT_INC}" ]]; then
    INCS=(-I"${LUAJIT_INC}" "${INCS[@]}")
fi

mkdir -p "${OUT}"
echo "compilation du test de liaison..."
"${CXX}" -std=c++17 -Wall "${INCS[@]}" \
    "${ROOT}/tests/lua_binding/main.cpp" -o "${OUT}/lua_binding" "${LUAJIT_LIB}"

echo
"${OUT}/lua_binding"