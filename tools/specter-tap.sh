#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# specter-tap.sh — recoit les logs de Specter.Internal sur Linux.
#
# La DLL (sous Wine/Proton) ecrit dans une FIFO via le disque Z:, qui pointe
# vers la racine Linux. Par defaut :
#
#     Windows : Z:\tmp\specter.pipe
#     Linux   : /tmp/specter.pipe
#
# Ce script cree la FIFO (si besoin) et affiche le flux en continu. Cote
# Windows, aucune trace dans le prefixe du jeu : juste un handle vers la FIFO.
#
# Usage :
#   tools/specter-tap.sh                 # affiche sur stdout
#   tools/specter-tap.sh specter.log     # affiche ET enregistre dans un fichier
#
# Env :
#   SPECTER_PIPE_FILE=/autre/chemin.pipe # doit correspondre au SPECTER_PIPE cote Windows
# ---------------------------------------------------------------------------
set -euo pipefail

PIPE="${SPECTER_PIPE_FILE:-/tmp/specter.pipe}"
LOG="${1:-}"

if [ -e "$PIPE" ] && [ ! -p "$PIPE" ]; then
    echo "erreur : $PIPE existe mais n'est pas une FIFO" >&2
    exit 1
fi
[ -p "$PIPE" ] || mkfifo "$PIPE"

echo "tap : $PIPE   (cote Windows : Z:$(printf '%s' "$PIPE" | tr '/' '\\'))"
echo "en attente de la DLL (Specter.Internal)... Ctrl-C pour quitter"

if [ -n "$LOG" ]; then
    exec tee -a "$LOG" < "$PIPE"
else
    exec cat "$PIPE"
fi
