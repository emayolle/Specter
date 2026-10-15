#!/usr/bin/env bash
# Build and run the offline worker descriptor test (tests/worker_meta).
#
# Exists because this code broke the game twice, and both times the only way to
# find out was to relaunch and watch it die. Here it runs against the system
# LuaJIT in a second, with no game, no DLL and no Wine.
#
# It compiles the SAME src/Specter.Internal/lua/worker_meta.h the DLL compiles,
# and binds capi::p_* to the real library functions — which is the one thing
# worker_meta.h gets for free that the DLL has to resolve through
# GetProcAddress on xlua.dll.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT="${ROOT}/generated/tests"
CXX="${CXX:-clang++}"
LUAJIT_INC="${LUAJIT_INC:-/usr/include/luajit-2.1}"
LUAJIT_LIB="${LUAJIT_LIB:--lluajit-5.1}"

INCS=(-I"${ROOT}/src/Specter.Internal" -I"${ROOT}/third_party/lua51")
if [[ -d "${LUAJIT_INC}" ]]; then
    INCS=(-I"${LUAJIT_INC}" "${INCS[@]}")
fi

mkdir -p "${OUT}"
echo "compilation du test des descripteurs..."
"${CXX}" -std=c++17 -Wall -Wextra -Wno-unused-parameter "${INCS[@]}" \
    "${ROOT}/tests/worker_meta/main.cpp" -o "${OUT}/worker_meta" "${LUAJIT_LIB}"

echo
exec "${OUT}/worker_meta"
