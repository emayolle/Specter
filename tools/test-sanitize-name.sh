#!/usr/bin/env bash
# Build and run the offline sanitize_name test (tests/sanitize_name).
#
# Une fonction qui massacre du texte se verifie en une seconde, ici. Elle a
# transforme "Cote de mare fleur" en "C__te_de_mar__eflore" pendant des semaines
# sans que personne ne le dise, parce qu'on le lisait dans une liste de waypoints
# ou on avait l'habitude des underscores.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT="${ROOT}/generated/tests"
CXX="${CXX:-clang++}"

mkdir -p "${OUT}"
echo "compilation du test de sanitize_name..."
"${CXX}" -std=c++17 -Wall "${ROOT}/tests/sanitize_name/main.cpp" -o "${OUT}/sanitize_name"

echo
exec "${OUT}/sanitize_name"
