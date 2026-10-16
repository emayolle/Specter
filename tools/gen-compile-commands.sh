#!/usr/bin/env bash
# Generate compile_commands.json for editors/IntelliSense (clangd).
#
# The real build cross-compiles with clang-cl + the xwin-provided MSVC CRT and
# Windows SDK (see tools/build-dll.sh). clangd does not know those paths, so an
# editor shows bogus errors such as:
#
#   'pch-il2cpp.h' file not found
#   Unknown type name 'LPCWSTR' / 'DWORD' / 'BOOL' / 'IMAGE_DOS_HEADER'
#
# This script re-derives the exact same flags as tools/build-dll.sh and writes a
# compile_commands.json at the repository root, which clangd picks up
# automatically. Re-run it whenever the build flags change.
#
#   tools/gen-compile-commands.sh
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
XWIN="${XWIN:-$HOME/.xwin}"
OUT_FILE="$ROOT/compile_commands.json"

if [[ ! -d "$XWIN/crt/include" || ! -d "$XWIN/sdk/include" ]]; then
  echo "error: xwin tree not found at '$XWIN'." >&2
  echo "       run: xwin --accept-license --arch x86_64 splat --output '$XWIN'" >&2
  exit 1
fi

SDK_VER="$(ls "$XWIN/sdk/include" | grep -E '^10\.' | sort -V | tail -1)"
CRT_INC="$XWIN/crt/include"
SDK_INC="$XWIN/sdk/include/$SDK_VER"

SRC="$ROOT/src/Specter.Internal"
GEN="$ROOT/generated/sdk"
IMGUI="$ROOT/third_party/imgui"

# Same compiler and flags as tools/build-dll.sh (minus /c /PCH /Fo: clangd only
# parses, it does not compile or link).
COMPILER=(clang-cl --target=x86_64-pc-windows-msvc)
FLAGS=(
  /MT /O2 /DNDEBUG
  /DSPECTER_INTERNAL_EXPORTS /D_WINDOWS /D_USRDLL /DUNICODE /D_UNICODE
  /EHsc /std:c++17
  -Wno-c++11-narrowing
  /imsvc "$CRT_INC"
  /imsvc "$SDK_INC/ucrt"
  /imsvc "$SDK_INC/shared"
  /imsvc "$SDK_INC/um"
  /I "$ROOT/third_party/luajit/include" /I "$ROOT/third_party/luabridge"
  /I "$GEN/framework" /I "$GEN/appdata" /I "$SRC"
  /I "$IMGUI" /I "$IMGUI/backends"
  /DNOMINMAX
)

# Emit one entry per translation unit under src/ (the code we iterate on). The
# generated SDK / ImGui TUs are intentionally left out: indexing them is huge
# and pointless, and headers still resolve through the flags above.
mapfile -t SOURCES < <(find "$SRC" -name '*.cpp' | sort)

python3 - "$OUT_FILE" "$ROOT" "${COMPILER[@]}" "${FLAGS[@]}" -- "${SOURCES[@]}" <<'PY'
import json, sys

out_file, directory = sys.argv[1], sys.argv[2]
rest = sys.argv[3:]
flags = rest[: rest.index("--")]
sources = rest[rest.index("--") + 1 :]

db = [
    {
        "directory": directory,
        "file": src,
        "arguments": flags + [src],
    }
    for src in sources
]

with open(out_file, "w") as f:
    json.dump(db, f, indent=2)
    f.write("\n")
print(f"wrote {out_file} ({len(db)} entries)")
PY
