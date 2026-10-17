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

# ---------------------------------------------------------------------------
# PAS DE DOUBLE INJECTION.
#
# La DLL est MANUELLEMENT MAPPEE : elle n'apparait ni dans /proc/<pid>/maps ni
# dans aucune liste de modules de Wine. De l'exterieur, on ne peut donc pas la
# voir -- et surtout pas voir l'AUTRE instance.
#
# Ce qu'on peut voir, c'est ce que la DLL annonce elle-meme au demarrage par le
# pipe : `overlay: D3D12 ImGui ready` puis `overlay: frame pipeline armed`.
# Deux occurrences de cette banniere pour un meme PID = deux images chargees,
# donc deux fois les hooks, deux fois l'overlay, deux fois le bootstrap Lua, et
# deux `specter.store` qui divergent. Ca ne se voit pas au premier launch : la
# deuxieme instance se pose PAR-DESSUS, et le symptome est un overlay fantome
# qu'on ne peut plus piloter.
#
# On note donc le PID injecte avec son temps de demarrage (champ 22 de
# /proc/pid/stat), parce qu'un PID Linux est REATTRIBUE : sans le starttime, le
# verrou d'un processus mort ferait refuser a tort l'injection parfaitement
# legitime dans un jeu qu'on vient de relancer.
# ---------------------------------------------------------------------------
SPECTER_LOCK="${SPECTER_LOCK_FILE:-/tmp/specter-injected}"

# starttime du processus, ou vide si /proc n'est pas lisible.
#
# On ne compte PAS les champs depuis le debut : le champ comm (2) est entre
# parentheses et peut contenir des espaces ET des parentheses, ce qui rend
# "awk '{print $22}'" faux des que le nom du process contient une espace. On
# coupe donc sur la DERNIERE ')' -- le nom du noyau est entre parentheses, et un
# ')' dedans rend la premiere parenthese fermante ambiguë.
specter_pid_starttime() {
  local pid="$1" s
  [ -r "/proc/$pid/stat" ] || return 1
  s="$(sed -n 's/^.*) //p' "/proc/$pid/stat" 2>/dev/null | cut -d' ' -f20)"
  [ -n "$s" ] || return 1
  printf '%s' "$s"
}

# 0 = aucune instance connue pour ce PID, 1 = deja injectee.
specter_already_injected() {
  local pid="$1" lpid lstart cur
  [ -f "$SPECTER_LOCK" ] || return 1
  lpid="$(cut -d' ' -f1 "$SPECTER_LOCK" 2>/dev/null || true)"
  lstart="$(cut -d' ' -f2 "$SPECTER_LOCK" 2>/dev/null || true)"
  [ "$lpid" = "$pid" ] || return 1
  cur="$(specter_pid_starttime "$pid")" || return 1
  [ -n "$cur" ] && [ "$lstart" = "$cur" ]
}

specter_note_injection() {
  local pid="$1" st
  st="$(specter_pid_starttime "$pid" || echo '?')"
  printf '%s %s\n' "$pid" "$st" > "$SPECTER_LOCK"
}

# A appeler AVANT d'injecter. sortie 1 = on refuse.
specter_refuse_double_injection() {
  local pid="$1"
  if specter_already_injected "$pid"; then
    echo "REFUS: Aniimo.exe (pid $pid) a deja recu Specter." >&2
    echo "       Une seconde injection charge deux images : deux overlay, deux" >&2
    echo "       jeux de hooks, deux bootstraps Lua, deux stores divergents." >&2
    echo "       Pour repartir de zero : relance le JEU, puis injecte." >&2
    echo "       Pour forcer quand meme :  SPECTER_FORCE_INJECT=1" >&2
    return 1
  fi
  return 0
}

# Le processus est pret quand la pile graphique est chargee. Injecter avant donne
# "dxgi.dll: module not loaded in guest" ; injecter apres que le jeu ait
# recree son swapchain donne un overlay qui ne s'arme jamais. Wine charge les
# DLL Windows comme des .so Linux, donc /proc/<pid>/maps les montre.
specter_graphics_ready() {
  local pid="$1"
  [ -n "$pid" ] || return 1
  [ -r "/proc/$pid/maps" ] || return 1
  grep -qi 'dxgi.dll' "/proc/$pid/maps"
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