// Specter.Internal — multiplicateurs de vitesse (curseurs). See vitesse.h.

#pragma once

namespace specter::features {
namespace vitesse {

// UNE CASE, DES CURSEURS.
//
// Le multiplicateur est un `float*` : `specter.var.vit_marche` et le curseur
// doivent etre LE MEME octet. Un getter/setter re-creerait deux copies, dont une
// se desynchronise a chaque reconnexion -- exactement le probleme que flag()
// resout pour les cases.
bool* actif();
float* mult(const char* nom);

// Les curseurs, dans l'ordre d'affichage.
//
// La liste est declaree ICI, pas dans le script Lua, et c'est volontaire : le C++
// tire les noms de `vit_<nom>`, et le script sait lire `specter.vit_<nom>`. Une
// methode de jeu renommee casse donc le lien de maniere visible (le binding
// manque) plutot que de decaler silencieusement les curseurs d'une ligne.
struct Curseur {
    const char* nom;    // cle du binding : vit_<nom>
    const char* label;  // libelle affiche
    float min_v;
    float max_v;
    float defaut;
    const char* aide;   // pourquoi ce curseur existe, et son piege
};

// L'interrupteur maitre. Decocher restaure les originaux cote Lua -- sans quoi
// decocher ne changerait rien de visible et le seul moyen de revenir a une
// vitesse normale serait de relancer le jeu.
void draw_ui();

}  // namespace vitesse
}  // namespace features