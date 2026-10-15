#!/usr/bin/env python3
"""Protocole de descripteurs de worker.cpp, rejoue hors du jeu.

Le crash venait de l'arithmetique de parcours de la chaine : en sautant une
directive, le code C faisait p = nl + 1, ce qui laissait la charge utile d'une
chaine ('S') au milieu du flux. Ce test rejoue exactement cette arithmetique.

Un test qui reproduit le defaut vaut mieux qu'un test qui le contourne.
"""
import sys

SPACE, NL = 0x20, 0x0A


def describe(values, role):
    """Coté jeu : describe_args / describe_upvalues."""
    out = b""
    for i, v in enumerate(values, 1):
        p = f"{role} ".encode()
        if v is None:
            out += p + f"Z {i}\n".encode()
        elif isinstance(v, bool):
            out += p + f"B {i} {1 if v else 0}\n".encode()
        elif isinstance(v, (int, float)):
            out += p + f"N {i} {v:.17g}\n".encode()
        elif isinstance(v, str):
            b = v.encode()
            out += p + f"S {i} {len(b)}\n".encode() + b + b"\n"
        else:
            raise TypeError(v)
    return out


def skip_spaces(data, p, limit):
    while p < limit and data[p] == SPACE:
        p += 1
    return p


def read_int(data, p):
    q = p
    while q < len(data) and chr(data[q]) in "0123456789":
        q += 1
    return int(data[p:q]), q


def take_desc(data, p, want):
    """take_desc() de worker.cpp. Retourne (p apres, valeur ou None)."""
    end = len(data)
    nl = data.index(b"\n", p)

    role = data[p]
    p = skip_spaces(data, p + 1, nl)
    kind = chr(data[p])
    p = skip_spaces(data, p + 1, nl)
    idx, after = read_int(data, p)
    after = skip_spaces(data, after, nl)
    payload_start = after

    if kind == "Z":
        return nl + 1, (None if want else "SKIP")
    if kind == "N":
        return nl + 1, (float(data[payload_start:nl]) if want else "SKIP")
    if kind == "B":
        return nl + 1, (data[payload_start:payload_start + 1] == b"1" if want else "SKIP")
    if kind == "L":
        return nl + 1, (data[payload_start:nl].decode() if want else "SKIP")
    if kind == "S":
        # `payload` est la LONGUEUR ; les octets sont sur les lignes apres nl.
        # Les lire dans payload serait decale d'un octet.
        slen = int(data[payload_start:nl])
        bstart = nl + 1
        if slen < 0 or bstart + slen > end:
            raise ValueError("chaine tronquee")
        val = data[bstart:bstart + slen].decode() if want else "SKIP"
        q = bstart + slen
        if q < end and data[q] == NL:
            q += 1
        return q, val
    raise ValueError(f"descripteur inconnu '{kind}'")


def walk(data, role):
    """apply_meta() de worker.cpp, pour un role donne.

    Le point important : quand on saute une directive de l'AUTRE role, on la
    consomme quand meme en entier, charge utile comprise. C'est exactement ce
    que le C faisait mal (p = nl + 1, qui laissait la charge d'un 'S' trainer).
    """
    out, p, end = [], 0, len(data)
    while p < end:
        if b"\n" not in data[p:end]:
            break
        r = chr(data[p])
        want = (r == role)
        p, v = take_desc(data, p, want)
        if want:
            out.append(v)
    return out


CAS = [
    ("les 4 types", describe([42, "bonjour", True, None], "A"),
     "A", [42.0, "bonjour", True, None]),
    ("que des nombres", describe([1, 2, 3], "A"), "A", [1.0, 2.0, 3.0]),
    ("chaine avec retours a la ligne", describe([1, "avec\nun\nretour", 9], "A"),
     "A", [1.0, "avec\nun\nretour", 9.0]),
    ("chaine vide", describe([""], "A"), "A", [""]),
    ("chaine de 1 octet", describe(["x"], "A"), "A", ["x"]),
    ("mixte U puis A", describe([3], "U") + describe(["x", 1.5], "A"),
     "A", ["x", 1.5]),
    ("mixte U puis A, cote U", describe([3], "U") + describe(["x", 1.5], "A"),
     "U", [3.0]),
    ("chaine avant un nombre", describe(["abc", 7], "A"), "A", ["abc", 7.0]),
    ("deux chaines consecutives", describe(["un", "deux"], "A"), "A", ["un", "deux"]),
    ("upvalues multiples", describe([1, "deux", False], "U"), "U",
     [1.0, "deux", False]),
]


def main():
    fails = 0
    for nom, data, role, attendu in CAS:
        try:
            got = walk(data, role)
        except Exception as e:
            print(f"  ECHEC {nom:32s} exception: {e}")
            fails += 1
            continue
        if got == attendu:
            print(f"  ok    {nom:32s} {got}")
        else:
            print(f"  ECHEC {nom:32s} obtenu {got} / attendu {attendu}")
            fails += 1

    # le role qu'on ne demande pas doit rendre une liste vide, jamais planter
    for nom, data, role, _ in CAS[:4]:
        try:
            vide = walk(data, "U" if role == "A" else "A")
        except Exception as e:
            print(f"  ECHEC {nom:32s} (role inverse) exception: {e}")
            fails += 1
            continue
        if vide != []:
            print(f"  ECHEC {nom:32s} (role inverse) obtenu {vide} / attendu []")
            fails += 1
        else:
            print(f"  ok    {nom:32s} (role inverse) []")

    print()
    print(f"ECHECS : {fails}" if fails else "TOUT PASSE")
    return 1 if fails else 0


sys.exit(main())