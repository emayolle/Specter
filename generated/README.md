# generated/

Ce dossier est **entièrement reproductible** : tout son contenu (sauf ce
README) est produit par `tools/dump.sh` et **n'est pas versionné**.

| Sous-dossier | Contenu | Producteur |
|---|---|---|
| `input/` | liens vers le jeu + `global-metadata.decrypted.dat` (v31) | étapes 1–2 de `dump.sh` |
| `sdk/appdata/` | SDK C++ : `il2cpp-types.h`, `il2cpp-functions.h`, `il2cpp-types-ptr.h`, … | Il2CppInspectorRedux |
| `sdk/framework/` | scaffold d'injection (`dllmain`, `il2cpp-init`, `helpers`, `pch`) | Il2CppInspectorRedux |
| `dump/` | `dump.cs`, `il2cpp.py` (script IDA), `metadata.json` | Il2CppInspectorRedux |
| `shims/` | assemblies .NET factices (ILSpy/dnSpy) | Il2CppInspectorRedux |
| `bin/`, `obj/` | sorties de build de `src/Specter.Internal` | MSVC |

Le code écrit à la main vit sous `src/`. Ne modifie jamais un fichier ici :
la prochaine exécution de `tools/dump.sh` l'écrasera.

Pour tout régénérer :

```bash
tools/dump.sh
```
