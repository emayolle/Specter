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

echo "== Specter.Internal — injection (wine-hostch) =="
echo "pid   : $PID"
echo "dll   : $DLL"
echo "token : ${TOKEN:0:8}... (masque)"

exec python3 "$HOSTCH_CLIENT" --pid "$PID" --token "$TOKEN" \
  map --pe "$DLL" --dllmain --hide-system