# lua/ — fragments Lua déchiffrés & scripts reconstitués

## Fichiers bruts (`<EA>.lua`)

Les 93 fichiers `lua/*.lua` sont **chacun une constante de chaîne déchiffrée** depuis le binaire Shinoko. Ce ne sont **pas** des scripts complets, mais des **briques** que le mod concatène à l'exécution avec des valeurs runtime (`xluaL_loadbuffer`).

- `maps/enqueuers.txt` — qui assemble quelles briques (`dec=...`).
- `maps/decryptors*.txt` — inventaire des 93 déchiffreurs (EA, N, table, seed).
- `maps/decoded_lua_bundle.txt` — concaténation brute de toutes ces constantes (utile pour inspection globale).
- `maps/decoded_summary*.txt` — aperçu rapide de chaque fragment.

## Scripts reconstitués (`assembled/`)

Dossier `lua/assembled/` : reconstruction **byte-exacte** des scripts tels qu'assemblés par Shinoko.

- 42 fichiers générés.
- **41/42** passent `luac -p` (seul `99_incomplete_teleport_target.lua` échoue : se termine par `getForward()*` sans suite trouvée dans le binaire).
- **Insertions runtime** : 
  - `-- INSERTION runtime: …` pour nombres/booléens (valeurs conjecturées, marquées 1/0 par défaut).
  - texte **inséré brut** directement dans les littéraux de chaîne quand le collage coupe une chaîne (impossible de commenter au milieu d'une chaîne Lua).
- Détails complets : [`assembled/README-assembled.md`](assembled/README-assembled.md).

## Régénération

`reference/shinoko/assemble_scripts.py` régénère intégralement `lua/assembled/` depuis `lua/*.lua` + `maps/enqueuers.txt`. Exécuter depuis `reference/shinoko/` :

```bash
cd /home/cozlex/Projects/Specter/reference/shinoko
python3 assemble_scripts.py
```

Vérification syntaxique rapide :

```bash
luac -p lua/assembled/*.lua 2>&1 | tail -5
```

## Remarque

Le fait que `taille == N-1` pour tous les fragments à `N` fixe est **normal** : le déchiffreur écrit au plus N−1 octets puis null-terminate. **Rien n'est tronqué côté extraction** ; les « fins en plein milieu » correspondent aux **points d'insertion** de valeurs runtime.