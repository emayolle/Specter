#!/usr/bin/env bash
# Cross-build Specter.Internal.dll on Linux with clang-cl + the MSVC CRT and the
# Windows SDK headers/libraries fetched by `xwin`. No Windows / Visual Studio
# required.
#
#   xwin --accept-license --arch x86_64 splat --output ~/.xwin     # one time
#   tools/build-dll.sh            # incremental
#   tools/build-dll.sh --clean    # force a full rebuild
#
# The build is incremental and split into cached static libraries:
#   generated/build/specter_sdk.lib     generated SDK (helpers, il2cpp-init)
#   generated/build/specter_imgui.lib   vendored Dear ImGui + D3D12/Win32 backends
# Only the translation units whose source (or a tracked header) changed are
# recompiled, so day-to-day work under src/Specter.Internal/ never rebuilds the
# (large) generated SDK or ImGui. `--clean` wipes the cache.
#
# Output: generated/bin/Release/Specter.Internal.dll  (Release | x64, /MT)
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
XWIN="${XWIN:-$HOME/.xwin}"

CLEAN=0
for a in "$@"; do
  case "$a" in
    --clean|-c) CLEAN=1 ;;
    -h|--help) sed -n '2,20p' "$0"; exit 0 ;;
    *) echo "unknown option: $a" >&2; exit 2 ;;
  esac
done

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
IMGUI="$ROOT/third_party/imgui"
OUT="$ROOT/generated/bin/Release"
OBJ="$ROOT/generated/build/obj"
LIBS="$ROOT/generated/build"

if [[ ! -f "$GEN/framework/il2cpp-init.cpp" ]]; then
  echo "error: generated SDK missing - run tools/dump.sh first." >&2
  exit 1
fi

mkdir -p "$OUT" "$OBJ" "$LIBS"

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
  /I "$GEN/framework" /I "$GEN/appdata" /I "$SRC" \
  /I "$IMGUI" /I "$IMGUI/backends" \
  /DNOMINMAX
)

PCH_H="pch-il2cpp.h"
PCH="$OBJ/pch-il2cpp.pch"
PCH_OBJ="$OBJ/pch-il2cpp.obj"

SDK_LIB="$LIBS/specter_sdk.lib"
IMGUI_LIB="$LIBS/specter_imgui.lib"

if [[ "$CLEAN" == 1 ]]; then
  echo "== clean: removing cached objects and libraries =="
  rm -f "$OBJ"/*.obj "$OBJ"/*.pch "$SDK_LIB" "$IMGUI_LIB"
fi

# --- incremental freshness helpers -------------------------------------------

# header_newer OBJ DIR...  -> true (0) if any *.h under DIR is newer than OBJ.
header_newer() {
  local obj="$1"; shift
  local d
  for d in "$@"; do
    [[ -d "$d" ]] || continue
    if find "$d" -name '*.h' -newer "$obj" -print -quit 2>/dev/null | grep -q .; then
      return 0
    fi
  done
  return 1
}

# obj_fresh OBJ SRC PCH_OR_EMPTY HDRDIR... -> true (0) when OBJ can be reused.
obj_fresh() {
  local obj="$1" src="$2" pch="$3"; shift 3
  [[ -f "$obj" ]] || return 1
  if [[ "$src" -nt "$obj" ]]; then return 1; fi
  if [[ -n "$pch" && -f "$pch" && "$pch" -nt "$obj" ]]; then return 1; fi
  if header_newer "$obj" "$@"; then return 1; fi
  return 0
}

# lib_stale LIB OBJ... -> true (0) when LIB must be (re)archived.
lib_stale() {
  local lib="$1"; shift
  [[ -f "$lib" ]] || return 0
  local o
  for o in "$@"; do
    if [[ "$o" -nt "$lib" ]]; then return 0; fi
  done
  return 1
}

# build_obj NAME OBJ SRC MODE HDRDIR...
#   MODE is "pch" (compile with /Yu$PCH_H) or "nopch". Recompiles only when the
#   object is missing or any tracked input is newer.
build_obj() {
  local name="$1" obj="$2" src="$3" mode="$4"; shift 4
  local pch=""
  [[ "$mode" == "pch" ]] && pch="$PCH"
  if obj_fresh "$obj" "$src" "$pch" "$@"; then
    echo "   - $name (cached)"
    return 0
  fi
  echo "   - $name"
  if [[ "$mode" == "pch" ]]; then
    "${CXX[@]}" "${FLAGS[@]}" "/Yu$PCH_H" /Fp"$PCH" /Fo"$obj" "$src"
  else
    "${CXX[@]}" "${FLAGS[@]}" /Fo"$obj" "$src"
  fi
}

# --- [1/5] precompiled header ------------------------------------------------

echo "== [1/5] precompiled header (SDK $SDK_VER) =="
if [[ -f "$PCH_OBJ" ]] && obj_fresh "$PCH" "$GEN/framework/pch-il2cpp.cpp" "" \
      "$GEN/appdata" "$GEN/framework"; then
  echo "   - pch-il2cpp (cached)"
else
  echo "   - pch-il2cpp"
  "${CXX[@]}" "${FLAGS[@]}" "/Yc$PCH_H" /Fp"$PCH" /Fo"$PCH_OBJ" \
    "$GEN/framework/pch-il2cpp.cpp"
fi

# --- [2/5] generated SDK -> specter_sdk.lib ----------------------------------

echo "== [2/5] generated SDK library =="
build_obj helpers     "$OBJ/helpers.obj"     "$GEN/framework/helpers.cpp"     pch "$GEN/appdata" "$GEN/framework"
build_obj il2cpp-init "$OBJ/il2cpp-init.obj" "$GEN/framework/il2cpp-init.cpp" pch "$GEN/appdata" "$GEN/framework"
SDK_OBJS=("$OBJ/helpers.obj" "$OBJ/il2cpp-init.obj")
if lib_stale "$SDK_LIB" "${SDK_OBJS[@]}"; then
  echo "   - archiving specter_sdk.lib"
  rm -f "$SDK_LIB"
  llvm-lib /nologo /out:"$SDK_LIB" "${SDK_OBJS[@]}"
else
  echo "   - specter_sdk.lib (cached)"
fi

# --- [3/5] Specter internals (the part we iterate on) ------------------------

echo "== [3/5] Specter internals =="
OUR_OBJS=()
for spec in \
  "$SRC/app/entry.cpp:app-entry" \
  "$SRC/app/specter.cpp:app-specter" \
  "$SRC/il2cpp/runtime.cpp:il2cpp-runtime" \
  "$SRC/il2cpp/api.cpp:il2cpp-api" \
  "$SRC/platform/nt.cpp:platform-nt" \
  "$SRC/platform/log.cpp:platform-log" \
  "$SRC/platform/hook/detour.cpp:platform-detour" \
  "$SRC/render/dxgi_hook.cpp:render-dxgi_hook" \
  "$SRC/render/d3d12_overlay.cpp:render-d3d12_overlay" \
  "$SRC/render/d3dcompiler_shim.cpp:render-d3dcompiler_shim" \
  "$SRC/render/input.cpp:render-input" \
  "$SRC/features/console/console.cpp:features-console" \
  "$SRC/features/lua_dump/lua_dump.cpp:features-lua_dump" \
  "$SRC/features/teleport/teleport.cpp:features-teleport"; do
  src="${spec%:*}"; name="${spec##*:}"; obj="$OBJ/$name.obj"
  build_obj "$name" "$obj" "$src" pch "$SRC" "$GEN/appdata" "$GEN/framework"
  OUR_OBJS+=("$obj")
done

# --- [4/5] vendored ImGui -> specter_imgui.lib -------------------------------

echo "== [4/5] vendored ImGui library =="
IMGUI_OBJS=()
for spec in \
  "$IMGUI/imgui.cpp:imgui" \
  "$IMGUI/imgui_draw.cpp:imgui_draw" \
  "$IMGUI/imgui_tables.cpp:imgui_tables" \
  "$IMGUI/imgui_widgets.cpp:imgui_widgets" \
  "$IMGUI/imgui_demo.cpp:imgui_demo" \
  "$IMGUI/backends/imgui_impl_win32.cpp:imgui_impl_win32" \
  "$IMGUI/backends/imgui_impl_dx12.cpp:imgui_impl_dx12"; do
  src="${spec%:*}"; name="${spec##*:}"; obj="$OBJ/$name.obj"
  build_obj "$name" "$obj" "$src" nopch "$IMGUI" "$IMGUI/backends"
  IMGUI_OBJS+=("$obj")
done
if lib_stale "$IMGUI_LIB" "${IMGUI_OBJS[@]}"; then
  echo "   - archiving specter_imgui.lib"
  rm -f "$IMGUI_LIB"
  llvm-lib /nologo /out:"$IMGUI_LIB" "${IMGUI_OBJS[@]}"
else
  echo "   - specter_imgui.lib (cached)"
fi

# --- [5/5] link --------------------------------------------------------------

echo "== [5/5] linking =="
lld-link /nologo /DLL /MACHINE:X64 \
  /OUT:"$OUT/Specter.Internal.dll" \
  "${OUR_OBJS[@]}" "$SDK_LIB" "$IMGUI_LIB" \
  /LIBPATH:"$CRT_LIB" /LIBPATH:"$UCRT_LIB" /LIBPATH:"$UM_LIB" \
  libcmt.lib libcpmt.lib libvcruntime.lib libucrt.lib oldnames.lib \
  kernel32.lib user32.lib dxgi.lib

echo
echo "built: $OUT/Specter.Internal.dll"
ls -la "$OUT/Specter.Internal.dll"
