#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# lua.sh — exécute un chunk Lua dans l'instance Aniimo en cours, depuis le shell.
#
# PRÉCONDITION : la case « Autoriser le shell » doit être cochée dans l'onglet
# Lua Editor de l'overlay. Sans elle, ce script ne fait rien et le DLL ne
# regarde même pas le fichier — la fenêtre est fermée au chargement.
#
# Pourquoi il y a une case : un canal d'exécution déclenché par le système de
# fichiers est un canal que quiconque peut écrire dans ce dossier peut utiliser.
# Pas d'UI, pas d'intention, pas de trace d'une personne ayant demandé. La case
# garde cette précondition, et la fenêtre expire d'elle-même (~10 s).
#
# Usage :
#   tools/lua.sh 'print(1+1)'
#   tools/lua.sh -f script.lua
#   echo '…' | tools/lua.sh
#
# Env : SPECTER_CLI_DIR (défaut /tmp/specter-cli)
# ---------------------------------------------------------------------------
set -uo pipefail
DIR="${SPECTER_CLI_DIR:-/tmp/specter-cli}"
REQ="$DIR/req.lua"
RES="$DIR/res.txt"

case "${1:-}" in
  -f|--file) SRC="${2:?usage: lua.sh -f fichier}"; shift 2 ;;
  --help|-h) sed -n '2,25p' "$0"; exit 0 ;;
  "")        if [ -t 0 ]; then
                echo "usage: lua.sh 'code' | -f fichier | (stdin)" >&2; exit 2
              else
                SRC="$(cat)"
              fi ;;
  *)         SRC="$1" ;;
esac

[ -n "$SRC" ] || { echo "usage: lua.sh 'code' | -f fichier | (stdin)" >&2; exit 2; }

mkdir -p "$DIR" || exit 1

# Une seule requête à la fois : sans ce verrou, deux terminaux pourraient se
# voler la réponse l'un de l'autre.
exec 9>"$DIR/.lock" || exit 1
if ! flock -n 9; then
  echo "lua.sh: une requete est deja en cours (attendez la fin de l'autre)" >&2
  exit 3
fi

# Fingerprint de la réponse courante : on ne veut pas lire celle de la
# précédente si la nôtre n'est jamais traitée.
before=0
[ -f "$RES" ] && before=$(cksum < "$RES")

# Publication atomique : le DLL ne renomme `req.lua` que si le fichier est
# entier. Sans ça, il pourrait exécuter un chunk à moitié écrit.
printf '%s' "$SRC" > "$REQ.tmp" && mv -f "$REQ.tmp" "$REQ"

echo "lua.sh: requete deposee — en attente que le canal s'ouvre." >&2

# On attend longtemps, et on ne republie pas. Le fichier reste sur le disque :
# la DLL le prend des que le canal s'ouvre, meme si c'est apres le depot.
# Republier risque de faire tourner le chunk plusieurs fois.
for _ in $(seq 1 600); do
  sleep 0.1
  [ -f "$RES" ] || continue
  now=$(cksum < "$RES")
  [ "$now" != "$before" ] || continue
  # Première ligne : #ok=<0|1>
  head -1 "$RES"
  tail -n +2 "$RES"
  head -1 "$RES" | grep -q '#ok=1' && exit 0 || exit 1
done

echo "lua.sh: pas de reponse apres 60 s." >&2
echo "        le canal est-il ouvert ? (onglet Lua Editor -> 'Autoriser le shell')" >&2
echo "        ou le DLL est-il trop vieux ? il doit venir d'apres 15:03." >&2
exit 4