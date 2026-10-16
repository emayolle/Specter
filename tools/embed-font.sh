#!/usr/bin/env bash
# Compile the fonts into C headers, so they travel inside the DLL.
#
# WHY EMBEDDED, NOT READ FROM DISK
#   The game's side has no path we control, and a font has to exist before the
#   first frame is drawn. There is no second chance: the atlas is baked the
#   first time ImGui_ImplDX12_NewFrame runs.
#
# DEUX POLICES, DEUX RAISONS
#
#   Inter      le TEXTE du menu. Sans elle, tout s'affiche en ProggyClean, le
#              pixel font par defaut d'ImGui — c'est la premiere chose qui
#              faisait dire que le menu n'etait pas fini. Sous-ensemble latin,
#              30 ko.
#   Lucide     les ICONES. Sous-ensemble de 107 glyphes, 40 ko. La police
#              complete fait 926 ko et n'apporterait rien de plus tant qu'on
#              n'affichera pas les deux mille icones.
#
# Inter est SIL OFL 1.1, Lucide est ISC. Les deux autorisent l'integration.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ICO="${ROOT}/third_party/lucide/lucide-subset.ttf"
TXT="${ROOT}/third_party/inter/inter-ui.ttf"
OUT_ICO="${ROOT}/generated/icon_font.h"
OUT_TXT="${ROOT}/generated/ui_font.h"

[[ -f "${ICO}" ]] || { echo "ERREUR: absent ${ICO}" >&2; exit 1; }
[[ -f "${TXT}" ]] || { echo "ERREUR: absent ${TXT}" >&2; exit 1; }
command -v python3 >/dev/null || { echo "ERREUR: python3 requis" >&2; exit 1; }

mkdir -p "$(dirname "${OUT_ICO}")" "$(dirname "${OUT_TXT}")"

python3 - "${ICO}" "${OUT_ICO}" "${TXT}" "${OUT_TXT}" <<'PY'
import sys

def ecrire(chemin_ttf, chemin_out, nom, commentaire):
    data = open(chemin_ttf, 'rb').read()
    lignes = []
    for i in range(0, len(data), 20):
        lignes.append('    ' + ''.join('0x%02x,' % b for b in data[i:i + 20]))
    with open(chemin_out, 'w', encoding='utf-8') as f:
        f.write(
            '// AUTO-GENERE par tools/embed-font.sh.\n'
            '// Ne pas editer a la main.\n'
            '//\n'
            + commentaire + '\n'
            '#pragma once\n\n'
            'namespace specter::render {\n\n'
            '// NON constexpr : AddFontFromMemoryTTF prend un void* non const, et un\n'
            '// tableau constexpr est const.\n'
            'inline unsigned char ' + nom + '[] = {\n'
            + '\n'.join(lignes) + '\n'
            '};\n\n'
            'inline constexpr unsigned int ' + nom + 'Size = sizeof(' + nom + ');\n\n'
            '}  // namespace specter::render\n')
    return len(data)

n1 = ecrire(sys.argv[1], sys.argv[2], 'kIconFont',
            '// Lucide, sous-ensemble de 107 glyphes (ISC). Les points de code sont\n'
            '// dans third_party/lucide/GLYPHES.txt.')
n2 = ecrire(sys.argv[3], sys.argv[4], 'kUiFont',
            '// Inter, sous-ensemble latin (SIL OFL 1.1). Police du TEXTE du menu.')
print('police icones : %d o' % n1)
print('police texte  : %d o' % n2)
PY

printf "icones : %s -> %s (%s o)\n" "${ICO##*/}" "${OUT_ICO##*/}" "$(wc -c < "${ICO}")"
printf "texte  : %s -> %s (%s o)\n" "${TXT##*/}" "${OUT_TXT##*/}" "$(wc -c < "${TXT}")"
