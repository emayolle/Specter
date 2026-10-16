# reference/ — intel tiers, lecture seule

Ce dossier contient les artefacts produits en **reverse-engineering d'autres mods /
binaires** (pas le jeu, pas Specter). C'est de la **matière de référence**, pas du
produit :

| | |
|---|---|
| Contrat | **lecture seule** — on n'édite jamais ces fichiers ; on régénère/remplace en bloc. |
| Versionné | Oui pour le **texte** (rapports, Lua déchiffrés, tables, pseudocode). |
| Non versionné | Les **binaires lourds** (`.dll`, `.i64`) vivent dans `*/binary/`, exclus par `.gitignore`. |
| Rapport à `generated/` | `generated/` = *notre* pipeline (`tools/dump.sh`) sur le jeu. `reference/` = artefacts externes, non reproduits par nos outils. |

Chaque cible a son propre sous-dossier (`reference/shinoko/`, …).
