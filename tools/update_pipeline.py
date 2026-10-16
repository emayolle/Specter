#!/usr/bin/env python3
"""
update_pipeline.py — pipeline "source qu'on régénère nous-mêmes à chaque update" (Aniimo)

À chaque mise à jour du jeu :
  1. lit LuaCacheVer.txt (identifiant de version)   -> si changé depuis le baseline,
  2. dézippe le nouveau LuaScripts.xdf (ZIP, script bytecode LuaJIT modifié)
     dans <dump-root>/<version>/xfs/luascripts/     (structure identique au précedent)
  3. compare md5 fichier-par-fichier avec le baseline (le dump précédent ou `--seed`)
     -> rapport : fichiers identiques / changés / nouveaux / supprimés
  4. pour chaque fichier changé : tente `luajit -bl` (listing annoté avec debug info)
     et exporte les constantes/strings visibles (fallback lisible).

Usage:
  python3 update_pipeline.py --install <chemin_install> [--dump-root <dir>] [--seed <dir>]

  --install   dossier d'installation du jeu (contient Aniimo_Data/cvs/res/lua/LuaCacheVer.txt)
  --dump-root où stocker les dumps datés par version   (défaut: /tmp/opencode/aniimo_dump)
  --seed      dossier correspondant à un dump déjà extrait (ex: /tmp/opencode/aniimo_lua)
              utilisé comme baseline la première fois, pour éviter de ré-extraire 114 Mo.

Sorties (dans dump-root):
  <version>/xfs/luascripts/...                     le dump complet du .xdf
  current_version.txt                              version actuellement baseline
  diff_<old>_<new>.txt                             rapport de changement
  changed/<rel-path>/.bl.txt                       listings -bl des fichiers changés
"""

import argparse
import hashlib
import os
import shutil
import subprocess
import sys
import zipfile

XFS_PREFIX = "xfs/luascripts/"          # préfixe des entrées dans le .xdf
LUA_CACHE_REL = "Aniimo_Data/cvs/res/lua/LuaCacheVer.txt"
XDF_REL = "Aniimo_Data/cvs/res/lua/LuaScripts.xdf"

LUAJIT = shutil.which("luajit")


def md5_file(path) -> str:
    h = hashlib.md5()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def read_cache_version(install) -> str:
    p = os.path.join(install, LUA_CACHE_REL)
    with open(p, "r", encoding="utf-8", errors="replace") as f:
        return f.read().strip()


def extract_xdf(install, dest) -> None:
    xdf = os.path.join(install, XDF_REL)
    os.makedirs(dest, exist_ok=True)
    with zipfile.ZipFile(xdf) as z:
        # n'extraire que l'arborescence des scripts
        for name in z.namelist():
            if not name.startswith(XFS_PREFIX) or name.endswith("/"):
                continue
            rel = name[len(XFS_PREFIX):]
            target = os.path.join(dest, rel)
            os.makedirs(os.path.dirname(target), exist_ok=True)
            with z.open(name) as src, open(target, "wb") as out:
                shutil.copyfileobj(src, out)
    print(f"[+] .xdf extrait -> {dest} ({sum(len(fn) for _, _, fn in os.walk(dest))} fichiers)")


def walk_lua(root):
    out = {}
    for dirpath, _, files in os.walk(root):
        for fn in files:
            rel = os.path.relpath(os.path.join(dirpath, fn), root)
            out[rel] = os.path.join(dirpath, fn)
    return out


def try_bl(path, out_rel_path) -> None:
    """Tente un listing -bl annoté ; fallback strings/constantes."""
    if LUAJIT is None:
        return
    os.makedirs(os.path.dirname(out_rel_path), exist_ok=True)
    r = subprocess.run([LUAJIT, "-bl", path], capture_output=True, text=True)
    if r.returncode == 0 and r.stdout.strip():
        with open(out_rel_path, "w", encoding="utf-8") as f:
            f.write(r.stdout)
        return
    # fallback: constantes string lisibles
    with open(path, "rb") as f:
        data = f.read()
    import re
    strings = re.findall(rb"[ -~]{4,}", data)
    with open(out_rel_path + ".strings.txt", "w", encoding="utf-8") as f:
        for s in strings:
            try:
                f.write(s.decode("ascii") + "\n")
            except UnicodeDecodeError:
                pass
    print(f"[~] -bl échoue (opcode jeu modifié) ; strings extraites pour {os.path.basename(path)}")


def diff_trees(old_root, new_root, out_report, out_changed_dir):
    old = walk_lua(old_root)
    new = walk_lua(new_root)
    same, changed, added, removed = [], [], [], []
    for rel in new:
        if rel not in old:
            added.append(rel)
        elif md5_file(old[rel]) == md5_file(new[rel]):
            same.append(rel)
        else:
            changed.append(rel)
    for rel in old:
        if rel not in new:
            removed.append(rel)

    with open(out_report, "w", encoding="utf-8") as f:
        f.write(f"# diff: {os.path.basename(old_root)} -> {os.path.basename(new_root)}\n")
        f.write(f"# identiques={len(same)}  changés={len(changed)}  nouveaux={len(added)}  supprimés={len(removed)}\n\n")
        f.write(f"## CHANGÉS ({len(changed)})\n")
        for rel in sorted(changed):
            f.write(rel + "\n")
        f.write(f"\n## NOUVEAUX ({len(added)})\n")
        for rel in sorted(added):
            f.write(rel + "\n")
        f.write(f"\n## SUPPRIMÉS ({len(removed)})\n")
        for rel in sorted(removed):
            f.write(rel + "\n")

    for rel in sorted(changed) + sorted(added):
        rel_out = os.path.join(out_changed_dir, rel)
        try_bl(new[rel], rel_out + ".bl.txt")

    print(f"\n[=] identiques={len(same)}  CHANGÉS={len(changed)}  nouveaux={len(added)}  supprimés={len(removed)}")
    print(f"[+] rapport -> {out_report}")
    if changed:
        print(f"[+] listings/strings des fichiers changés -> {out_changed_dir}")
    return changed, added


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--install", required=True, help="dossier d'install du jeu")
    ap.add_argument("--dump-root", default="/tmp/opencode/aniimo_dump")
    ap.add_argument("--seed", default=None,
                    help="dossier d'un dump déjà extrait (baseline initial, évite la ré-extraction)")
    args = ap.parse_args()

    root = args.dump_root
    os.makedirs(root, exist_ok=True)
    verfile = os.path.join(root, "current_version.txt")

    version = read_cache_version(args.install)
    short = version.split(",")[0] if version else version
    print(f"[.] version LuaCacheVer.txt = {version}")

    if os.path.exists(verfile):
        prev_ver = open(verfile).read().strip()
    else:
        prev_ver = None

    # Détermination / extraction du dump courant
    curr_dir = os.path.join(root, short)
    if not os.path.isdir(curr_dir):
        if prev_ver is None and args.seed:
            # baseline = seed (on évite de re-extraire 114 Mo la première fois)
            curr_dir = os.path.abspath(args.seed)
            print(f"[i] baseline amorcé depuis --seed ({curr_dir})")
        else:
            extract_xdf(args.install, curr_dir)

    if prev_ver is None:
        # premier passage : on pose juste le baseline enregistré
        open(verfile, "w").write(short)
        print(f"[i] baseline initial enregistré : version '{short}' -> {curr_dir}")
        print(f"[i] au prochain passage, si la version change, le diff sera produit automatiquement.")
        return 0

    if prev_ver == short:
        print(f"[=] version inchangée ({short}) — rien à faire.")
        return 0

    prev_dir = os.path.join(root, prev_ver)
    if not os.path.isdir(prev_dir):
        print(f"[!] baseline '{prev_ver}' introuvable ({prev_dir}) ; re-extraire ou --seed.")
        return 2

    print(f"[i] UPDATE détectée : {prev_ver} -> {short}")
    out_changed = os.path.join(root, f"changed_{prev_ver}_{short}")
    diff_trees(prev_dir, curr_dir,
               os.path.join(root, f"diff_{prev_ver}_{short}.txt"),
               out_changed)
    open(verfile, "w").write(short)
    return 0


if __name__ == "__main__":
    sys.exit(main())