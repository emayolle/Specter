#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# Aniimo -> SDK C++  (pipeline reproductible)
#
#   1. dechiffre global-metadata.dat (protection NetEase "NEP2"/NEProtect2)
#   2. corrige le numero de version metadata (le script AFKJ ecrit 29, Aniimo v31)
#   3. genere le sorties avec Il2CppInspectorRedux (C++/C#/IDA/JSON/DLL shims)
#
# Usage:  tools/dump.sh
# Env:    GAME_DIR=/chemin/vers/Aniimo   (defaut: install Steam ci-dessous)
# ---------------------------------------------------------------------------
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
GAME="${GAME_DIR:-/home/cozlex/.local/share/Steam/steamapps/common/Aniimo}"
II="$HERE/tools/Il2CppInspector"

GASM="$GAME/GameAssembly.dll"
ENC="$GAME/Aniimo_Data/il2cpp_data/Metadata/global-metadata.dat"
DEC="$HERE/input/global-metadata.decrypted.dat"

[ -f "$GASM" ] || { echo "GameAssembly.dll introuvable: $GASM"; exit 1; }
[ -f "$ENC" ]  || { echo "global-metadata.dat introuvable: $ENC"; exit 1; }
[ -x "$II" ]   || { echo "Il2CppInspector introuvable: $II"; exit 1; }

mkdir -p "$HERE/input" "$HERE/dump" "$HERE/cpp"
ln -sf "$GASM" "$HERE/input/GameAssembly.dll"
ln -sf "$ENC"  "$HERE/input/global-metadata.encrypted.dat"

echo "[1/3] dechiffrement NEProtect2 ..."
python3 "$HERE/tools/metadata_decrypt.py" "$ENC" "$DEC.raw"

echo "[2/3] correction de la version metadata 29 -> 31 ..."
python3 - "$DEC.raw" "$DEC" <<'PY'
import struct, sys
src, dst = sys.argv[1], sys.argv[2]
d = bytearray(open(src, 'rb').read())
assert struct.unpack_from('<I', d, 0)[0] == 0xFAB11BAF, "magic Unity invalide"
struct.pack_into('<I', d, 4, 31)          # Aniimo = metadata v31
open(dst, 'wb').write(d)
print("      version =", struct.unpack_from('<I', d, 4)[0],
      "| taille =", len(d))
PY
rm -f "$DEC.raw"

echo "[3/3] generation Il2CppInspectorRedux ..."
"$II" \
  -i "$HERE/input/GameAssembly.dll" \
  -m "$DEC" \
  -h "$HERE/cpp" \
  -c "$HERE/dump/dump.cs" \
  -p "$HERE/dump/il2cpp.py" \
  -o "$HERE/dump/metadata.json"

echo
echo "OK -> cpp/appdata/il2cpp-types.h, dump/dump.cs, dump/il2cpp.py, dump/metadata.json"
