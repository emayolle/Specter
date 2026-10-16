#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Reconstruction des scripts Lua du mod Shinoko (Aniimo) à partir des 93
constantes déchiffrées (lua/<EA>.lua).

Méthode
-------
Le mod n'exécute pas des scripts entiers : il *concatène à l'exécution*
plusieurs constantes de chaîne (+ des valeurs runtime) et envoie le résultat
à `xluaL_loadbuffer`. Chaque ligne du fichier `maps/enqueuers.txt` donne,
pour un enqueueur, la liste ordonnée des déchiffreurs (dec=...) qu'il recolle.

On reproduit donc la concaténation **byte-exacte** (un seul préprocesseur :
les fragments se raccordent parfois au milieu d'un littéral de chaîne Lua,
d'où l'interdiction d'ajouter des retours à la ligne entre fragments).

Insertions
----------
- `('v', val, desc)` → `val  -- INSERTION runtime: desc` puis retour à la
  ligne. Utilisé pour les booléens/nombres (toggle ON/OFF, rayons, délais…).
- `('s', txt)` → texte brut sans commentaire, car il est inséré À L'INTÉRIEUR
  d'un littéral de chaîne (les `"` appartiennent aux fragments) : impossible
  de commenter en plein milieu d'une chaîne Lua.

Les valeurs réelles du menu sont inconnues → valeurs materialisées 1/0 par
défaut (ou valeurs plausibles), toutes marquées `-- INSERTION runtime:`.

La sortie est écrite dans `lua/assembled/` (+ `README-assembled.md`).

Usage : `python3 assemble_scripts.py` depuis ce dossier.
"""
import os

SRC = 'lua'
DST = os.path.join('lua', 'assembled')


def frag(ea):
    return open(os.path.join(SRC, f'{ea}.lua'), 'rb').read().decode('utf-8', 'replace')


def V(val, desc):
    return ('v', val, desc)


def S(txt):
    return ('s', txt)


# (fichier, description, [items]) — ordre = ordre du recollage dans le binaire
SPECS = [
    ("10_god_mode.lua", "God Mode (protection combat, chutes, RPC) — 3 fragments + 2 toggles",
     [('f', '180008B90'), V('1', "état God Mode (1=ON, 0=OFF)"), ('f', '180009000'),
      V('1', "état God Mode (1=ON, 0=OFF)"), ('f', '180009470')]),
    ("11_mob_vacuum.lua", "Mob Vacuum — pousse les mobs vers la cible (global `target`, défini par 99_incomplete_teleport_target)",
     [('f', '180005340')]),
    ("12_kill_aura.lua", "Kill Aura — tue les ennemis dans le rayon, toutes les INTERVAL secondes",
     [('f', '18000D580'), V('1', "état Kill Aura (1=ON, 0=OFF)"), ('f', '18000D9F0'),
      V('15', "rayon de l'aura (slider menu)"), ('f', '18000DE60'),
      V('1.0', "intervalle en secondes (slider menu)"), ('f', '18000E2D0')]),
    ("13_catch_aura.lua", "Catch Aura — capture les entités dans le rayon, toutes les INTERVAL secondes",
     [('f', '18000EE10'), V('1', "état Catch Aura (1=ON, 0=OFF)"), ('f', '18000F280'),
      V('15', "rayon de l'aura (slider menu)"), ('f', '18000F6F0'),
      V('1.0', "intervalle en secondes (slider menu)"), ('f', '18000FB60')]),
    ("14_one_hit.lua", "One Hit — les attaques du joueur tuent en un coup",
     [('f', '1800102A0'), V('1', "état One Hit (1=ON, 0=OFF)"), ('f', '180010710')]),
    ("15_multi_hit.lua", "Multi Hit — chaque attaque frappe HIT_TIMES fois",
     [('f', '180009D80'), V('3', "nombre de coups (slider menu)"), ('f', '18000A1F0'),
      V('1', "état Multi Hit (1=ON, 0=OFF)"), ('f', '18000A660')]),
    ("16_infinite_stamina.lua", "Infini Stamina / Endurance",
     [('f', '18000AAD0'), V('1', "état Inf Stamina (1=ON, 0=OFF)"), ('f', '18000AF50')]),
    ("17_infinite_energy.lua", "Infini Énergie (EP + SP)",
     [('f', '18000B3C0'), V('1', "état Inf Energy (1=ON, 0=OFF)"), ('f', '18000B840')]),
    ("18_no_cooldown.lua", "No Cooldown — reset des CD du joueur et du pet",
     [('f', '18000C160'), V('1', "CD joueur (1=ON, 0=OFF)"), ('f', '18000C5D0'),
      V('1', "CD pet (1=ON, 0=OFF)"), ('f', '18000CA30')]),
    ("19_unlimited_dash.lua", "Unlimited Dash — dash sans limite",
     [('f', '180010E50'), V('1', "état Unlimited Dash (1=ON, 0=OFF)"), ('f', '1800112C0')]),
    ("20_auto_loot.lua", "Auto Loot — ramasse le butin dans le rayon, toutes les INTERVAL secondes",
     [('f', '180011E10'), V('1', "état Auto Loot (1=ON, 0=OFF)"), ('f', '180012280'),
      V('15', "rayon de ramassage (slider menu)"), ('f', '1800126F0'),
      V('1.0', "intervalle en secondes (slider menu)"), ('f', '180012B60')]),
    ("21_rate_limit_bypass.lua", "Rate-Limit Bypass — contourne la limite de taux client (ClientSwitch)",
     [('f', '180016E20'), V('1', "état (1=ON, 0=OFF)"), ('f', '1800172A0')]),
    ("22_teleport_to_scene.lua", "Téléportation de scène",
     [('f', '180014A30'), V('1001', "ID de scène (liste déroulante menu)"), ('f', '180014EA0')]),
    ("23_player_scale_custom.lua", "Échelle du joueur (valeur personnalisée)",
     [('f', '180005A20'), V('1.5', "échelle du modèle (slider menu)"), ('f', '180005E90')]),
    ("24_player_scale_reset.lua", "Échelle du joueur — reset (1.0)",
     [('f', '1800062F0')]),
    ("25_pet_scale_custom.lua", "Échelle du pet (valeur personnalisée)",
     [('f', '1800069D0'), V('1.5', "échelle du modèle (slider menu)"), ('f', '180006E50')]),
    ("26_pet_scale_reset.lua", "Échelle du pet — reset (1.0)",
     [('f', '180007540')]),
    ("27_no_fall_damage_on.lua", "No Fall Damage — ACTIVER",
     [('f', '1800079D0')]),
    ("28_no_fall_damage_off.lua", "No Fall Damage — DÉSACTIVER",
     [('f', '180007E40')]),
    ("29_dumb_enemy_on.lua", "Dumb Enemy — IA désactivée (AiConst.GLOBAL_OPEN_TICK=false)",
     [('f', '1800082B0')]),
    ("30_dumb_enemy_off.lua", "Dumb Enemy — IA normale",
     [('f', '180008720')]),
    ("31_free_cam.lua", "Free Cam / Camera",
     [('f', '180017A10')]),
    ("32_ob_camera_on.lua", "OB Camera — ACTIVER",
     [('f', '18001AB40')]),
    ("33_ob_camera_off.lua", "OB Camera — DÉSACTIVER",
     [('f', '18001AFB0')]),
    ("34_gm_console.lua", "GM Tools — console de debug + setGUI",
     [('f', '180026010')]),
    ("35_gm_hierarchy.lua", "GM Tools — hiérarchie",
     [('f', '180026720')]),
    ("36_gm_inspector.lua", "GM Tools — inspecteur",
     [('f', '180026E20')]),
    ("37_gm_ai_debug.lua", "GM Tools — AI debug",
     [('f', '180027520')]),
    ("38_gm_ability_inspect_on.lua", "GM Tools — onAbilityDataInspectChange(ON)",
     [('f', '180027C70')]),
    ("39_gm_ability_inspect_off.lua", "GM Tools — onAbilityDataInspectChange(OFF)",
     [('f', '1800280E0')]),
    ("40_tips_boss_warning.lua", "UI Tips — warning de boss (id + 2 textes)",
     [('f', '18001B420'), V('1', "ID du boss"), ('f', '18001B890'), S('BOSS'),
      ('f', '18001BCF0'), S('ATTENTION'), ('f', '18001C150')]),
    ("41_tips_hide_boss_warning.lua", "UI Tips — cacher le warning de boss",
     [('f', '18001C5B0')]),
    ("42_tips_common_input.lua", "UI Tips — boîte de saisie réutilisable",
     [('f', '18001CA20'), S('Saisie'), ('f', '18001CE90')]),
    ("43_tips_confirm.lua", "UI Tips — confirmation Oui/Non",
     [('f', '18001D300'), S('Confirmer ?'), ('f', '18001D760'), S('OUI'), ('f', '18001DBC0')]),
    ("44_tips_marquee.lua", "UI Tips — texte défilant",
     [('f', '18001E030'), S('TEXTE'), ('f', '18001E4A0'), V('3.0', "durée en secondes (slider menu)"),
      ('f', '18001E900')]),
    ("45_tips_text_tip.lua", "UI Tips — bulle de texte",
     [('f', '18001ED60'), S('TEXTE'), ('f', '18001F1C0'), V('3.0', "durée en secondes (slider menu)"),
      ('f', '18001F620')]),
    ("46_chat_player_send.lua", "Toplogo — bulle de chat du joueur",
     [('f', '18001FA80'), S('Message'), ('f', '18001FEF0')]),
    ("47_chat_player_clear.lua", "Toplogo — effacer la bulle du joueur",
     [('f', '180020360')]),
    ("48_chat_pet_send.lua", "Toplogo — bulle de chat du pet",
     [('f', '1800207E0'), S('Message'), ('f', '180020C50')]),
    ("49_chat_pet_clear.lua", "Toplogo — effacer la bulle du pet",
     [('f', '1800210C0')]),
    ("50_effect_play.lua", "Effet — playEffectAt sur le joueur",
     [('f', '180021530'), S('NomEffet'), ('f', '1800219A0'), V('2.0', "durée (slider menu)"),
      ('f', '180021E10'), V('1.0', "extraScale (slider menu)"), ('f', '180022280')]),
    ("99_incomplete_teleport_target.lua",
     "⚠ INCOMPLET — définition de `target` (téléport cible ?) — se termine `getForward()*`, suite introuvable",
     [('f', '180004EC0')]),
]

HDR = ("-- ============================================================\n"
       "-- Shinoko (Aniimo) — script reconstitué : {desc}\n"
       "-- Fragments déchiffrés recollés (ordre de l'enqueueur) : {eas}\n"
       "-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`\n"
       "-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de\n"
       "-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).\n"
       "-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.\n"
       "-- ============================================================\n\n")


def build(items):
    body = ''
    for it in items:
        if it[0] == 'f':
            body += frag(it[1])                       # octets exacts, aucun newline ajouté
        elif it[0] == 'v':
            body += f"{it[1]}  -- INSERTION runtime: {it[2]}\n"
        else:
            body += it[1]                             # inline dans une chaîne, sans commentaire
    return body


def main():
    os.makedirs(DST, exist_ok=True)
    for f in os.listdir(DST):
        os.remove(os.path.join(DST, f))

    rows = []
    for fn, desc, items in SPECS:
        eas = [it[1] for it in items if it[0] == 'f']
        with open(os.path.join(DST, fn), 'w') as out:
            out.write(HDR.format(desc=desc, eas=', '.join(eas)) + build(items))
        rows.append((fn, desc, eas))

    # README du dossier
    lines = [
        "# assembled/ — scripts Lua reconstitués",
        "",
        "Recollage **byte-exact** des 93 constantes déchiffrées (`lua/<EA>.lua`) dans",
        "l'ordre donné par `maps/enqueuers.txt` (chaque enqueueur concatène ses",
        "fragments + des valeurs runtime, puis appelle `xluaL_loadbuffer`).",
        "",
        "**Légende des insertions :**",
        "- `-- INSERTION runtime: …` → valeur numérique/booléenne conjecturée (1=ON, 0=OFF",
        "  par défaut ; rayons/délais/échelles = valeurs plausibles).",
        "- texte inséré **brut** (sans guillemets) dans un littéral de chaîne : les `\"`",
        "  appartiennent aux fragments voisins, on ne peut pas commenter en plein milieu",
        "  d'une chaîne Lua. Ces textes sont les saisies du menu (messages, infos boss…).",
        "",
        "**Garde-fous** : `luac -p` passe sur 41/42 fichiers (seul",
        "`99_incomplete_teleport_target.lua` échoue : sa fin `getForward()*` est",
        "réellement coupée dans le binaire, aucune suite trouvée).",
        "",
        "| Fichier | Feature | Fragments (ordre de collage) |",
        "|---|---|---|",
    ]
    for fn, desc, eas in rows:
        lines.append(f"| `{fn}` | {desc} | `{', '.join(eas)}` |")
    with open(os.path.join(DST, 'README-assembled.md'), 'w') as out:
        out.write('\n'.join(lines) + '\n')
    print(f"{len(rows)} scripts + README-assembled.md écrits dans {DST}/")


if __name__ == '__main__':
    main()