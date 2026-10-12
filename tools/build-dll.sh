#!/usr/bin/env bash
# Cross-build Specter.Internal.dll on Linux with clang-cl + the MSVC CRT and
# Windows SDK headers/libraries fetched by `xwin`. No Windows / Visual Studio
# required.
#
#   xwin --accept-license --arch x86_64 splat --output ~/.xwin     # one time
#   tools/build-dll.sh
#
# Output: generated/bin/Release/Specter.Internal.dll  (Release | x64, /MT)
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
XWIN="${XWIN:-$HOME/.xwin}"

if [[ ! -d "$XWIN/crt/include" || ! -d "$XWIN/sdk/include" ]]; then
  echo "error: xwin tree not found at '$XWIN'." >&2
  echo "       run: xwin --accept-license --arch x86_64 splat --output '$XWIN'" >&2
  exit 1
fi

SDK_VER="$(ls "$XWIN/sdk/include" | grep -E '^10\.' | sort -V | tail -1)"
CRT_INC="$XWIN/crt/include"
SDK_INC="$XWIN/sdk/include/$SDK_VER"
CRT_LIB="$XWIN/crt/lib/x86_64"
UCRT_LIB="$XWIN/sdk/lib/$SDK_VER/ucrt/x86_64"
UM_LIB="$XWIN/sdk/lib/$SDK_VER/um/x86_64"

SRC="$ROOT/src/Specter.Internal"
GEN="$ROOT/generated/sdk"
OUT="$ROOT/generated/bin/Release"
OBJ="$ROOT/generated/build/obj"

if [[ ! -f "$GEN/framework/il2cpp-init.cpp" ]]; then
  echo "error: generated SDK missing - run tools/dump.sh first." >&2
  exit 1
fi

mkdir -p "$OUT" "$OBJ"

CXX=(clang-cl --target=x86_64-pc-windows-msvc)
FLAGS=(
  /nologo /c /MT /O2 /DNDEBUG
  /DSPECTER_INTERNAL_EXPORTS /D_WINDOWS /D_USRDLL /DUNICODE /D_UNICODE
  /EHsc /std:c++17
  -Wno-c++11-narrowing
  /imsvc "$CRT_INC"
  /imsvc "$SDK_INC/ucrt"
  /imsvc "$SDK_INC/shared"
  /imsvc "$SDK_INC/um"
  /I "$GEN/framework" /I "$GEN/appdata" /I "$SRC"
)

PCH_H="pch-il2cpp.h"
PCH="$OBJ/pch-il2cpp.pch"

echo "== [1/3] precompiled header (SDK $SDK_VER) =="
"${CXX[@]}" "${FLAGS[@]}" "/Yc$PCH_H" /Fp"$PCH" /Fo"$OBJ/pch-il2cpp.obj" \
  "$GEN/framework/pch-il2cpp.cpp"

echo "== [2/3] compiling sources =="
for spec in \
  "$GEN/framework/helpers.cpp:helpers" \
  "$GEN/framework/il2cpp-init.cpp:il2cpp-init" \
  "$SRC/entry.cpp:entry" \
  "$SRC/specter.cpp:specter" \
  "$SRC/runtime.cpp:runtime" \
  "$SRC/nt.cpp:nt" \
  "$SRC/log.cpp:log"; do
  src="${spec%:*}"; name="${spec##*:}"
  echo "   - $name"
  "${CXX[@]}" "${FLAGS[@]}" "/Yu$PCH_H" /Fp"$PCH" /Fo"$OBJ/$name.obj" "$src"
done

echo "== [3/3] linking =="
lld-link /nologo /DLL /MACHINE:X64 \
  /OUT:"$OUT/Specter.Internal.dll" \
  "$OBJ"/*.obj \
  /LIBPATH:"$CRT_LIB" /LIBPATH:"$UCRT_LIB" /LIBPATH:"$UM_LIB" \
  libcmt.lib libcpmt.lib libvcruntime.lib libucrt.lib oldnames.lib \
  kernel32.lib user32.lib

echo
echo "built: $OUT/Specter.Internal.dll"
ls -la "$OUT/Specter.Internal.dll"
