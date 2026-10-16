#!/usr/bin/env bash
# Compile the icon font into a C header, so it travels inside the DLL.
#
# WHY EMBEDDED, NOT READ FROM DISK
#   Same reason as tools/embed-lua.sh: the game's side has no path we control,
#   and the font has to exist before the first frame is drawn. There is no
#   second chance to load it -- the atlas is baked the first time
#   ImGui_ImplDX12_NewFrame runs.
#
# WHY THE WHOLE FONT AND NOT A SUBSET
#   A subset would be 20 ko instead of 420 ko, and it would be right for the
#   seven icons we use today and wrong the first time somebody adds an eighth.
#   Font Awesome Free is SIL OFL 1.1, which allows embedding and redistribution.
#   The cost is compile time on this one file, and the file does not change.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TTF="${ROOT}/third_party/lucide/lucide-subset.ttf"
OUT="${ROOT}/generated/icon_font.h"

[[ -f "${TTF}" ]] || { echo "ERREUR: absent ${TTF}" >&2; exit 1; }
command -v python3 >/dev/null || { echo "ERREUR: python3 requis" >&2; exit 1; }

mkdir -p "$(dirname "${OUT}")"

python3 - "${TTF}" "${OUT}" <<'PY'
import sys

ttf, out = sys.argv[1], sys.argv[2]
data = open(ttf, 'rb').read()

lignes = []
for i in range(0, len(data), 20):
    bloc = data[i:i + 20]
    lignes.append('    ' + ''.join('0x%02x,' % b for b in bloc))

corps = '\n'.join(lignes)

with open(out, 'w', encoding='utf-8') as f:
    f.write(
        '// AUTO-GENERE par tools/embed-font.sh.\n'
        '// Ne pas editer a la main.\n'
        '//\n'
        '// Font Awesome Free 6.5.2, SIL OFL 1.1 (voir third_party/fontawesome/\n'
        '// LICENSE.txt). Integre en entier : un sous-ensemble aurait ete correct\n'
        '// pour les sept icones d aujourd hui et faux des la huitieme.\n'
        '#pragma once\n'
        '\n'
        'namespace specter::render {\n'
        '\n'
        '// NON constexpr : AddFontFromMemoryTTF prend un void* non const, et un\n'
        '// tableau constexpr est const.\n'
        'inline unsigned char kIconFont[] = {\n'
        + corps + '\n'
        '};\n'
        '\n'
        'inline constexpr unsigned int kIconFontSize =\n'
        '    sizeof(kIconFont);\n'
        '\n'
        '}  // namespace specter::render\n')

print('font_awesome.h : %d octets de police, %d lignes' % (len(data), len(lignes)))
PY

printf "police embarquee : %s -> %s (%s o)\n" \
    "${TTF##*/}" "${OUT##*/}" "$(wc -c < "${TTF}")"
