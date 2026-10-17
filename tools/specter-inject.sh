#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# specter-inject.sh — injecte Specter.Internal.dll dans Aniimo.exe en cours de
# run via wine-hostch (map --pe --dllmain --hide-system).
#
# Prérequis : le jeu tourne AU MOINS jusqu'à l'écran, et le tap écoute déjà
#             (sinon la DLL bloque à l'open de la FIFO) :
#
#   tools/specter-tap.sh specter.log          # terminal 1
#   tools/specter-inject.sh                   # terminal 2
#
# Usage :
#   tools/specter-inject.sh [PID]             # PID auto-détecté sinon
#
# Env : SPECTER_TOKEN / WINE_HOSTCH_TOKEN / SPECTER_TOKEN_FILE / WINE_HOSTCH_REPO
# ---------------------------------------------------------------------------
set -euo pipefail
SELF_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck source=hostch-common.sh
source "$SELF_DIR/hostch-common.sh"

TOKEN="$(specter_check_token)" || exit 1
specter_require_client || exit 1

PID="${1:-$(specter_game_pid)}"
[ -n "$PID" ] || { echo "erreur: Aniimo.exe ne tourne pas (pgrep -x Aniimo.exe vide)" >&2; exit 1; }

# Une DLL manualement mappee est INVISIBLE de l'exterieur : ni /proc/<pid>/maps
# ni les modules de Wine ne la montrent. Injecter deux fois ne produit donc
# aucune erreur -- deux images se chargent, et la deuxieme se pose par-dessus la
# premiere. On refuse avant, pas apres.
specter_refuse_double_injection "$PID" || exit 1

echo "== Specter.Internal — injection (wine-hostch) =="
echo "pid   : $PID"
echo "dll   : $DLL"
echo "token : ${TOKEN:0:8}... (masque)"

python3 "$HOSTCH_CLIENT" --pid "$PID" --token "$TOKEN" \
  map --pe "$DLL" --dllmain --hide-system

# On ne note l'injection qu'apres le succes de hostch : un echec doit pouvoir
# etre rejoue sans avoir a passer par SPECTER_FORCE_INJECT.
specter_note_injection "$PID"