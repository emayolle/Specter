#!/usr/bin/env bash
# Compile-check scripts/init.lua and embed it into a C header, so the bootstrap
# travels inside the DLL instead of being read from disk at run time.
#
# WHY EMBEDDED, NOT READ FROM DISK
#   - no path to get wrong on the game's side (Z:\... vs /home/...),
#   - no file IO on the Lua thread while a state is being built,
#   - and the script cannot go missing between build and run.
#
# Same technique nova uses for its InitScript (R"LUA_INIT(...)LUA_INIT").
#
# WHY THE SCRIPT IS CHECKED AND NOT COMPILED TO BYTECODE
#
# The sandbox assembles a chunk as  kPrefix + your code + kSuffix  and loads it
# with luaL_loadbuffer, because the preamble is TEXT — it closes over the store
# and the specter table that only exist at run time. Precompiled LuaJIT bytecode
# cannot be concatenated with that prefix, so embedding bytecode would mean
# bypassing the sandbox for the bootstrap: the init script would no longer see
# `specter.store` or `specter.var.*`, which is the entire reason it exists.
#
# So the source is embedded, and what we get instead of bytecode is the check:
# a syntax error fails the BUILD. Which is the half of "compile at build time"
# that actually matters — a typo should not survive to a reconnect.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SRC="${ROOT}/scripts/init.lua"
OUT="${ROOT}/generated/lua_init.h"

[[ -f "${SRC}" ]] || { echo "ERREUR: absent ${SRC}" >&2; exit 1; }

# ---- 0. TOUS les scripts : ils compilent, et ils tiennent dans le tampon -----
#
# La limite kMaxCode est ecrite dans le C++ (features/console/console.cpp, et
# lua/pump.cpp qui la partage). Aucun outil ne la connaissait, donc aucun outil
# ne pouvait dire "ce script est trop gros".
#
# Ce que ca a coute : g_src faisait 16 Ko dans la console alors que kMaxCode en
# fait 32. Coller chest-open.lua (18 198 o) le tronquait en silence au milieu
# d'une ligne, et le seul symptome etait
#
#     SpecterManager.lua:492: unexpected symbol near ')'
#
# -- un nom de fichier interne, qui ne parle pas du script et accuse le pont
# Lua alors que le pont va tres bien.
#
# On lit donc la constante depuis le C++ plutot que de la recopier ici : une
# recopie serait juste un second endroit a maintenir, et c'est exactement
# l'erreur qu'on vient de corriger.
KMAX="$(sed -n 's/^constexpr int kMaxCode = \([0-9]*\) \* \([0-9]*\);/\1 \2/p' \
        "${ROOT}/src/Specter.Internal/features/console/console.cpp" \
        | head -1 | awk '{print $1 * $2}')"
[[ -n "${KMAX}" ]] || { echo "ERREUR: kMaxCode introuvable dans console.cpp" >&2; exit 1; }

echo "-- scripts : compilation + taille (max ${KMAX} o) --"
for f in "${ROOT}"/scripts/*.lua; do
  [[ -f "$f" ]] || continue
  n=$(wc -c < "$f")
  if [[ "$n" -gt "$KMAX" ]]; then
    echo "ERREUR: ${f##*/} fait ${n} octets, la console n'en accepte que ${KMAX}." >&2
    echo "         Il sera tronque en silence au collage, et l'erreur qui en" >&2
    echo "         sortira ne parlera pas de la taille." >&2
    exit 1
  fi
  if command -v luajit >/dev/null 2>&1; then
    luajit -e 'local fn,e = loadfile("'"$f"'") if not fn then io.stderr:write("ERREUR Lua: "..tostring(e).."\n") os.exit(1) end' \
      || { echo "ERREUR: ${f##*/} ne compile pas." >&2; exit 1; }
  fi
  printf '   %-24s %6d o\n' "${f##*/}" "$n"
done

# ---- 1. le litteral C ne doit pas pouvoir se refermer tout seul ------------
if grep -q ')LUA_INIT' "${SRC}"; then
    echo "ERREUR: ${SRC} contient ')LUA_INIT', ce qui fermerait le litteral." >&2
    exit 1
fi

# ---- 2. le script doit compiler -------------------------------------------
# On fait vraiment charger le fichier, pas un « lu et compris » : luajit
# signale la ligne, et le fichier en cause.
if command -v luajit >/dev/null 2>&1; then
    if ! luajit -e 'local f, err = loadfile("'"${SRC}"'"); if not f then io.stderr:write("ERREUR Lua: "..tostring(err).."\n"); os.exit(1) end' ; then
        echo "ERREUR: ${SRC} ne compile pas. La DLL n'est PAS produite :" >&2
        echo "         une faute ici echouerait a la reconnexion, dans le jeu." >&2
        exit 1
    fi
    CHECKED="syntaxe verifiee (luajit)"
elif command -v lua5.1 >/dev/null 2>&1; then
    if ! lua5.1 -e 'local f, err = loadfile("'"${SRC}"'"); if not f then io.stderr:write("ERREUR Lua: "..tostring(err).."\n"); os.exit(1) end' ; then
        echo "ERREUR: ${SRC} ne compile pas. La DLL n'est PAS produite." >&2
        exit 1
    fi
    CHECKED="syntaxe verifiee (lua5.1)"
else
    # Sans interpreteur, on ne bloque pas la construction — mais on le dit, fort.
    CHECKED="NON VERIFI (ni luajit ni lua5.1 sur cette machine)"
    echo "ATTENTION: pas de luajit ni de lua5.1 — ${SRC##*/} n'a PAS ete" >&2
    echo "          verifie. Une faute de syntaxe ne sera vue qu'a la" >&2
    echo "          reconnexion, dans le jeu." >&2
fi

# ---- 3. embarquer ----------------------------------------------------------
mkdir -p "$(dirname "${OUT}")"
{
    echo "// AUTO-GENERE par tools/embed-lua.sh depuis scripts/init.lua."
    echo "// Ne pas editer a la main : editer scripts/init.lua et reconstruire."
    echo "#pragma once"
    echo
    echo "namespace specter::lua::init {"
    echo
    echo "static constexpr const char* kInitScript = R\"LUA_INIT("
    cat "${SRC}"
    echo ")LUA_INIT\";"
    echo
    echo "}  // namespace specter::lua::init"
} > "${OUT}"

printf "init embarque : scripts/init.lua -> generated/lua_init.h (%s lignes, %s)\n" \
    "$(wc -l < "${SRC}")" "${CHECKED}"