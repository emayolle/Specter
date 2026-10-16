-- ============================================================
-- Shinoko (Aniimo) — script reconstitué : Effet — playEffectAt sur le joueur
-- Fragments déchiffrés recollés (ordre de l'enqueueur) : 180021530, 1800219A0, 180021E10, 180022280
-- Valeurs numériques/booléennes matérialisées avec `-- INSERTION runtime`
-- ; les textes saisis via le menu sont insérés bruts dans les littéraux de
-- chaîne (impossible de commenter à l'intérieur d'une chaîne Lua).
-- NOTA : valeurs conjecturées — script reconstruit, pas une copie bit-à-bit.
-- ============================================================

pg.game.effect:playEffectAt(
    0,
    "NomEffet",
    pg.me:getPosition(),
    nil,
    pg.me,
    {
        duration=2.0  -- INSERTION runtime: durée (slider menu)
,
        extraScale=1.0  -- INSERTION runtime: extraScale (slider menu)

    },
    true
)