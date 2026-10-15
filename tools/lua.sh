#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# RETIRE — ce script ne peut plus rien faire.
#
# Il deposait un chunk dans /tmp/specter-lua/cmd.lua et attendait que la DLL le
# relise. Cette lecture automatique n'existe plus : la pompe Lua n'a plus de
# canal CLI.
#
# Pourquoi elle a ete retiree, et pas simplement fermee : un canal d'execution
# declenche par la presence d'un fichier est declenche par TOUT ce qui peut
# ecrire ce fichier - pas d'UI, pas d'authentification, pas d'intention. C'etait
# aussi le chemin par lequel du code entrait dans le jeu sans que personne ait
# appuye sur quoi que ce soit.
#
# Pour executer du Lua, c'est le bouton Execute de l'onglet "Lua Editor" de
# l'overlay. Chaque execution part dans un environnement construit pour elle
# (voir lua/pump.cpp).
#
# Si un jour le shell doit pouvoir piloter Lua, la seule voie acceptable est une
# action explicite et authentifiee - pas un fichier pose sur un disque.
# ---------------------------------------------------------------------------
cat >&2 <<'EOF'
tools/lua.sh : RETIRE.

Le canal CLI n'existe plus. Le deposer de fichier etait un canal d'execution de
code declenche par le systeme de fichiers, sans UI ni authentification.

Utilisez le bouton "Execute" de l'onglet "Lua Editor" de l'overlay.
EOF
exit 2
