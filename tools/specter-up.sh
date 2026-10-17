#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# specter-up.sh — la séquence quotidienne en une commande :
#
#   1. démarre le tap (FIFO /tmp/specter.pipe) en arrière-plan ;
#   2. attend que Aniimo.exe apparaisse (ouvre le jeu via Steam) ;
#   3. injecte Specter.Internal.dll (map --pe --dllmain --hide-system) ;
#   4. passe le tap au premier plan : les logs coulent jusqu'à Ctrl-C.
#
# La FIFO doit être écoutée AVANT l'injection (la DLL bloque à l'open sinon) —
# d'où l'ordre ci-dessus. Le jeu, lui, continue après Ctrl-C.
#
# Usage :
#   tools/specter-up.sh
#
# Env : SPECTER_LOG (defaut specter.log dans la racine du repo),
#       SPECTER_TOKEN / WINE_HOSTCH_TOKEN / SPECTER_TOKEN_FILE,
#       WINE_HOSTCH_REPO
# ---------------------------------------------------------------------------
set -euo pipefail
SELF_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck source=hostch-common.sh
source "$SELF_DIR/hostch-common.sh"

TOKEN="$(specter_check_token)" || exit 1
specter_require_client || exit 1

LOG="${SPECTER_LOG:-$SPECTER_ROOT/specter.log}"
TIMEOUT="${SPECTER_WAIT:-120}"   # secondes max pour voir Aniimo.exe
POLL=2

# 1. tap en arrière-plan
bash "$SELF_DIR/specter-tap.sh" "$LOG" &
TAP_PID=$!
cleanup() { kill "$TAP_PID" 2>/dev/null || true; }
trap cleanup EXIT
sleep 1

# 2. attendre le processus du jeu
echo "en attente de Aniimo.exe (max ${TIMEOUT}s) — ouvre le jeu via Steam..."
PID=""; waited=0
while [ "$waited" -lt "$TIMEOUT" ]; do
  PID="$(specter_game_pid)"
  [ -n "$PID" ] && break
  sleep "$POLL"; waited=$((waited + POLL))
done
if [ -z "$PID" ]; then
  echo "erreur: Aniimo.exe n'est jamais apparu. Lance le jeu, puis relance." >&2
  exit 1
fi
echo "Aniimo.exe détecté (pid $PID)"

# 2b. attendre la pile graphique. Injecter trop tôt échoue (dxgi pas chargé) ;
# trop tard, le jeu a déjà recréé son swapchain et l'overlay ne s'arme pas.
GW=0
while [ "$GW" -lt 60 ]; do
  specter_graphics_ready "$PID" && break
  [ "$GW" -eq 0 ] && echo "en attente de la pile graphique (dxgi.dll)..."
  sleep 1; GW=$((GW + 1))
done
if specter_graphics_ready "$PID"; then
  echo "pile graphique chargée"
else
  echo "avertissement: dxgi.dll toujours absent, l'injection peut échouer"
fi

# 3. injection
echo "== injection Specter.Internal =="
# Meme garde-fou que specter-inject.sh, et pour la meme raison : la DLL est
# manuellement mappee, donc rien de visible de l'exterieur ne dit qu'elle est
# deja la. Injecter deux fois ne donne aucune erreur.
specter_refuse_double_injection "$PID" || exit 1

python3 "$HOSTCH_CLIENT" --pid "$PID" --token "$TOKEN" \
  map --pe "$DLL" --dllmain --hide-system

specter_note_injection "$PID"

# 4. suivre le tap au premier plan (Ctrl-C quitte le tap, pas le jeu)
echo
echo "== tap actif — Ctrl-C pour quitter (le jeu continue) =="
echo "   Lua : deux chemins, tous les deux dans l'overlay ou dans tools/lua.sh."
echo "         - onglet 'Lua Editor' -> bouton Execute"
echo "         - tools/lua.sh       -> canal OUVERT par defaut (case a decocher"
echo "           dans l'overlay pour le fermer). Toute execution est dans le log."
trap - EXIT
wait "$TAP_PID"