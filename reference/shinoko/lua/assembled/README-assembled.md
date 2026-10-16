# assembled/ — scripts Lua reconstitués

Recollage **byte-exact** des 93 constantes déchiffrées (`lua/<EA>.lua`) dans
l'ordre donné par `maps/enqueuers.txt` (chaque enqueueur concatène ses
fragments + des valeurs runtime, puis appelle `xluaL_loadbuffer`).

**Légende des insertions :**
- `-- INSERTION runtime: …` → valeur numérique/booléenne conjecturée (1=ON, 0=OFF
  par défaut ; rayons/délais/échelles = valeurs plausibles).
- texte inséré **brut** (sans guillemets) dans un littéral de chaîne : les `"`
  appartiennent aux fragments voisins, on ne peut pas commenter en plein milieu
  d'une chaîne Lua. Ces textes sont les saisies du menu (messages, infos boss…).

**Garde-fous** : `luac -p` passe sur 41/42 fichiers (seul
`99_incomplete_teleport_target.lua` échoue : sa fin `getForward()*` est
réellement coupée dans le binaire, aucune suite trouvée).

| Fichier | Feature | Fragments (ordre de collage) |
|---|---|---|
| `10_god_mode.lua` | God Mode (protection combat, chutes, RPC) — 3 fragments + 2 toggles | `180008B90, 180009000, 180009470` |
| `11_mob_vacuum.lua` | Mob Vacuum — pousse les mobs vers la cible (global `target`, défini par 99_incomplete_teleport_target) | `180005340` |
| `12_kill_aura.lua` | Kill Aura — tue les ennemis dans le rayon, toutes les INTERVAL secondes | `18000D580, 18000D9F0, 18000DE60, 18000E2D0` |
| `13_catch_aura.lua` | Catch Aura — capture les entités dans le rayon, toutes les INTERVAL secondes | `18000EE10, 18000F280, 18000F6F0, 18000FB60` |
| `14_one_hit.lua` | One Hit — les attaques du joueur tuent en un coup | `1800102A0, 180010710` |
| `15_multi_hit.lua` | Multi Hit — chaque attaque frappe HIT_TIMES fois | `180009D80, 18000A1F0, 18000A660` |
| `16_infinite_stamina.lua` | Infini Stamina / Endurance | `18000AAD0, 18000AF50` |
| `17_infinite_energy.lua` | Infini Énergie (EP + SP) | `18000B3C0, 18000B840` |
| `18_no_cooldown.lua` | No Cooldown — reset des CD du joueur et du pet | `18000C160, 18000C5D0, 18000CA30` |
| `19_unlimited_dash.lua` | Unlimited Dash — dash sans limite | `180010E50, 1800112C0` |
| `20_auto_loot.lua` | Auto Loot — ramasse le butin dans le rayon, toutes les INTERVAL secondes | `180011E10, 180012280, 1800126F0, 180012B60` |
| `21_rate_limit_bypass.lua` | Rate-Limit Bypass — contourne la limite de taux client (ClientSwitch) | `180016E20, 1800172A0` |
| `22_teleport_to_scene.lua` | Téléportation de scène | `180014A30, 180014EA0` |
| `23_player_scale_custom.lua` | Échelle du joueur (valeur personnalisée) | `180005A20, 180005E90` |
| `24_player_scale_reset.lua` | Échelle du joueur — reset (1.0) | `1800062F0` |
| `25_pet_scale_custom.lua` | Échelle du pet (valeur personnalisée) | `1800069D0, 180006E50` |
| `26_pet_scale_reset.lua` | Échelle du pet — reset (1.0) | `180007540` |
| `27_no_fall_damage_on.lua` | No Fall Damage — ACTIVER | `1800079D0` |
| `28_no_fall_damage_off.lua` | No Fall Damage — DÉSACTIVER | `180007E40` |
| `29_dumb_enemy_on.lua` | Dumb Enemy — IA désactivée (AiConst.GLOBAL_OPEN_TICK=false) | `1800082B0` |
| `30_dumb_enemy_off.lua` | Dumb Enemy — IA normale | `180008720` |
| `31_free_cam.lua` | Free Cam / Camera | `180017A10` |
| `32_ob_camera_on.lua` | OB Camera — ACTIVER | `18001AB40` |
| `33_ob_camera_off.lua` | OB Camera — DÉSACTIVER | `18001AFB0` |
| `34_gm_console.lua` | GM Tools — console de debug + setGUI | `180026010` |
| `35_gm_hierarchy.lua` | GM Tools — hiérarchie | `180026720` |
| `36_gm_inspector.lua` | GM Tools — inspecteur | `180026E20` |
| `37_gm_ai_debug.lua` | GM Tools — AI debug | `180027520` |
| `38_gm_ability_inspect_on.lua` | GM Tools — onAbilityDataInspectChange(ON) | `180027C70` |
| `39_gm_ability_inspect_off.lua` | GM Tools — onAbilityDataInspectChange(OFF) | `1800280E0` |
| `40_tips_boss_warning.lua` | UI Tips — warning de boss (id + 2 textes) | `18001B420, 18001B890, 18001BCF0, 18001C150` |
| `41_tips_hide_boss_warning.lua` | UI Tips — cacher le warning de boss | `18001C5B0` |
| `42_tips_common_input.lua` | UI Tips — boîte de saisie réutilisable | `18001CA20, 18001CE90` |
| `43_tips_confirm.lua` | UI Tips — confirmation Oui/Non | `18001D300, 18001D760, 18001DBC0` |
| `44_tips_marquee.lua` | UI Tips — texte défilant | `18001E030, 18001E4A0, 18001E900` |
| `45_tips_text_tip.lua` | UI Tips — bulle de texte | `18001ED60, 18001F1C0, 18001F620` |
| `46_chat_player_send.lua` | Toplogo — bulle de chat du joueur | `18001FA80, 18001FEF0` |
| `47_chat_player_clear.lua` | Toplogo — effacer la bulle du joueur | `180020360` |
| `48_chat_pet_send.lua` | Toplogo — bulle de chat du pet | `1800207E0, 180020C50` |
| `49_chat_pet_clear.lua` | Toplogo — effacer la bulle du pet | `1800210C0` |
| `50_effect_play.lua` | Effet — playEffectAt sur le joueur | `180021530, 1800219A0, 180021E10, 180022280` |
| `99_incomplete_teleport_target.lua` | ⚠ INCOMPLET — définition de `target` (téléport cible ?) — se termine `getForward()*`, suite introuvable | `180004EC0` |
