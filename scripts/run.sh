#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# run.sh — exécute un script d'analyse de scripts/ dans l'instance Aniimo.
#
# C'est une fine enveloppe autour de tools/lua.sh (canal de commande fichier
# dans /tmp). Le pont Lua ne répond qu'EN JEU (pas au menu).
#
# Usage :
#   scripts/run.sh chests.lua
#   scripts/run.sh marks-summary.lua
#   scripts/run.sh -e 'print(pg.me.sceneId)'   # code inline
#   scripts/run.sh -f /chemin/absolu.lua
# ---------------------------------------------------------------------------
set -euo pipefail

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LUA="$DIR/../tools/lua.sh"
[ -x "$LUA" ] || { echo "erreur: tools/lua.sh introuvable ($LUA)" >&2; exit 1; }

case "${1:-}" in
  ''|-h|--help)
    sed -n '3,14p' "$0" | sed 's/^# \{0,1\}//'
    exit 0
    ;;
  -e|--eval)
    shift
    # tools/lua.sh n'a pas d'option -e : on lui passe le code en positionnel.
    exec "$LUA" "$1"
    ;;
  -f|--file)
    exec "$LUA" "$@"
    ;;
  *)
    f="$1"; shift
    [ -f "$f" ] || f="$DIR/$f"
    [ -f "$f" ] || { echo "erreur: script introuvable: $1" >&2; exit 2; }
    exec "$LUA" -f "$f" "$@"
    ;;
esac
