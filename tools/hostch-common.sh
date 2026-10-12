#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# hostch-common.sh — helpers partages pour les scripts Specter (tap + inject).
#
# Ce fichier est SOURCÉ, jamais exécuté directement.
#
# Resolution du token hostch (ordre) :
#   1. $SPECTER_TOKEN
#   2. $WINE_HOSTCH_TOKEN
#   3. $SPECTER_TOKEN_FILE (defaut : ~/.config/specter/hostch.token, 1re ligne)
#
# Le token n'est JAMAIS versionne (hors repo, chmod 600).
# ---------------------------------------------------------------------------

SPECTER_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
HOSTCH_REPO="${WINE_HOSTCH_REPO:-$HOME/Projects/wine-hostch}"
HOSTCH_CLIENT="$HOSTCH_REPO/host/hostch.py"
DLL="$SPECTER_ROOT/generated/bin/Release/Specter.Internal.dll"
PIPE="${SPECTER_PIPE_FILE:-/tmp/specter.pipe}"

# Token brut (peut etre vide).
specter_token() {
  if [ -n "${SPECTER_TOKEN:-}" ]; then printf '%s' "$SPECTER_TOKEN"; return 0; fi
  if [ -n "${WINE_HOSTCH_TOKEN:-}" ]; then printf '%s' "$WINE_HOSTCH_TOKEN"; return 0; fi
  local f="${SPECTER_TOKEN_FILE:-$HOME/.config/specter/hostch.token}"
  if [ -r "$f" ]; then tr -d '[:space:]' < "$f"; return 0; fi
  echo ""
}

# Token valide (32 hex) ou echec avec message.
specter_check_token() {
  local t; t="$(specter_token)"
  case "$t" in
    ""|REPLACE_ME|FILL_ME)
      echo "erreur: token hostch introuvable." >&2
      echo "        - export SPECTER_TOKEN=..." >&2
      echo "        - ou ecris les 32 hex dans $HOME/.config/specter/hostch.token" >&2
      return 1 ;;
  esac
  [[ "$t" =~ ^[0-9a-fA-F]{32}$ ]] \
    || { echo "erreur: token invalide (attendu 32 hex): '$t'" >&2; return 1; }
  printf '%s' "$t"
}

# PID Linux du processus Windows Aniimo.exe (vide si absent).
specter_game_pid() {
  pgrep -x Aniimo.exe 2>/dev/null | head -1 || true
}

# Preconditions communes : python3 + client hostch + DLL construite.
specter_require_client() {
  command -v python3 >/dev/null 2>&1 \
    || { echo "erreur: python3 introuvable" >&2; return 1; }
  [ -f "$HOSTCH_CLIENT" ] || {
    echo "erreur: client hostch introuvable: $HOSTCH_CLIENT" >&2
    echo "        (override: WINE_HOSTCH_REPO=...)" >&2
    return 1; }
  [ -f "$DLL" ] || {
    echo "erreur: Specter.Internal.dll introuvable: $DLL" >&2
    echo "        (lance tools/build-dll.sh d'abord)" >&2
    return 1; }
}