#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# lua.sh — exécute un chunk Lua DANS l'instance Aniimo en cours, depuis le shell.
#
# Specter expose un canal de commande fichier (dans /tmp, jamais dans le
# prefixe ni dans le dossier du jeu) :
#   * ce script publie le code de façon atomique (cmd.tmp -> cmd.lua) ;
#   * la DLL le "réclame" (cmd.lua -> cmd.run), l'exécute sur le thread Lua du
#     jeu et publie le résultat dans out.txt (et sur le pipe de logs).
#   * ce script attend alors la nouvelle sortie et l'affiche.
#
# Usage :
#   tools/lua.sh 'print(1+1)'
#   tools/lua.sh -f script.lua
#   echo 'print("hi")' | tools/lua.sh
#   tools/lua.sh --no-wait 'print("fire and forget")'
#
# Env :
#   SPECTER_LUA_DIR   (defaut /tmp/specter-lua)
#   SPECTER_LUA_WAIT  (secondes d'attente du resultat, defaut 10)
# ---------------------------------------------------------------------------
set -euo pipefail

DIR="${SPECTER_LUA_DIR:-/tmp/specter-lua}"
IN="$DIR/cmd.lua"
TMP="$DIR/cmd.tmp"
OUT="$DIR/out.txt"
WAIT="${SPECTER_LUA_WAIT:-10}"

usage() { sed -n '3,20p' "$0" | sed 's/^# \{0,1\}//'; }

wait_out=1
code=""
while [ $# -gt 0 ]; do
  case "$1" in
    -f|--file) shift; [ $# -ge 1 ] || { echo "erreur: -f attend un fichier" >&2; exit 2; }; code="$(cat "$1")"; shift ;;
    --no-wait) wait_out=0; shift ;;
    -h|--help) usage; exit 0 ;;
    --) shift; code="${1:-}"; shift || true ;;
    -*) echo "option inconnue: $1" >&2; exit 2 ;;
    *) code="$1"; shift ;;
  esac
done
if [ -z "$code" ] && [ ! -t 0 ]; then
  code="$(cat)"
fi
if [ -z "$code" ]; then
  echo "usage: tools/lua.sh 'lua code' | -f fichier | (stdin)" >&2
  exit 2
fi

if [ ! -d "$DIR" ]; then
  echo "erreur: $DIR introuvable." >&2
  echo "        Le jeu tourne-t-il avec Specter injecte (tools/specter-up.sh) ?" >&2
  exit 1
fi

# Numero de sequence du dernier resultat publie (0 si aucun).
seq_of() { [ -f "$OUT" ] && sed -n '1s/^#seq=\([0-9][0-9]*\).*/\1/p' "$OUT" || echo 0; }
before="$(seq_of)"; before="${before:-0}"

# Publication atomique du chunk.
printf '%s' "$code" > "$TMP"
mv -f "$TMP" "$IN"

if [ "$wait_out" -eq 0 ]; then
  exit 0
fi

deadline=$(( $(date +%s) + WAIT ))
while :; do
  cur="$(seq_of)"; cur="${cur:-0}"
  if [ "$cur" != "$before" ]; then
    tail -n +2 "$OUT"
    exit 0
  fi
  if [ "$(date +%s)" -ge "$deadline" ]; then
    echo "timeout: aucune reponse en ${WAIT}s." >&2
    echo "         (le jeu est-il bien en jeu/connecte ? le pont Lua n'agit qu'en jeu)" >&2
    exit 1
  fi
  sleep 0.2
done
