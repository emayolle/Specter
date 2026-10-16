// Specter.Internal — per-frame cost meter.
//
// WHY THIS EXISTS
//
// « je ne sais pas si c'est le script de auto farm ou pas », 170 fps au début,
// 59 fps apres. Sans mesure, la seule façon d'en savoir est de redémarrer le
// jeu et de hope — et le redémarrage ne prouve rien, parce que le jeu
// accumule lui aussi.
//
// Donc on mesure. Deux points seulement, parce que ce sont les deux seuls
// endroits où NOTRE code tourne par frame :
//
//   kOverlay  render_frame()  — le hook Present : fence, ImGui, command list
//   kPump     pump_impl()     — le hook Lua : notre passage sur le thread Lua
//
// Si ces deux nombres sont petits, la chute n'est pas chez nous, et inutile de
// deviner davantage. S'ils sont gros, on sait où.
//
// LE RAPPORT EST UNE FOIS PAR SECONDE, PAS PAR FRAME
//
// Un log par frame NOIERAIT le log lui-même, et il le ferait d'autant plus
// fort qu'on cherche à mesurer un problème de performance.
//
// ET CHAQUE NOMBRE EST PAR FRAME, PAS PAR SECONDE. Mesure : le total de la
// seconde affiche "2.00 ms" a cote d'un budget de 16.7 ms laisse croire a 12%.
// Divise par le nombre de frames, c'est 0.027 ms, soit 0.2%. Un compteur qui
// exagre notre cout de quarante fois fait perdre du temps au lieu d'en
// economiser.

#pragma once

namespace specter {
namespace perf {

// Horloge. QueryPerformanceCounter : GetTickCount64 a ~15 ms de resolution,
// ce qui est inutile pour mesurer une frame. Exposee parce que les deux points
// instrumentes doivent utiliser LA MEME horloge que le rapport.
long long now_ns();

enum Slot {
    kOverlay = 0,
    kPump = 1,
    kSlotCount,
};

// Nanosecondes passees depuis le dernier reset.
long long ns(Slot s);
void add(Slot s, long long ns);

// Images vues par le thread qui appelle report().
void frame();
long long frames();

// Ecrit une ligne si une seconde s'est ecoulee. Retourne true si elle a
// ecrit. A appeler au plus une fois par frame.
bool report();

}  // namespace perf
}  // namespace specter