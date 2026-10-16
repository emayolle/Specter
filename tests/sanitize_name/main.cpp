// Compile et execute JUSTE sanitize_name, hors du jeu, comme pour
// worker_meta. Une fonction qui massacre du texte se verifie en une ligne de
// test ; la decouvrir dans une liste de waypoints, non.
#include <cstdio>
#include <cstring>

void sanitize_name(char* out, std::size_t cap, const char* src)
{
    std::size_t n = 0;
    if (!src) {
        src = "";
    }
    for (; src[n] && n + 1 < cap; ++n) {
        const unsigned char c = static_cast<unsigned char>(src[n]);
        const bool ok = (c >= 0x20u && c != 0x7Fu);
        out[n] = ok ? static_cast<char>(c) : ' ';
    }
    out[n] = '\0';
}

int g_ok = 0, g_ko = 0;

void verifie(const char* nom, const char* entree, const char* attendu)
{
    char buf[64];
    sanitize_name(buf, sizeof(buf), entree);
    const bool ok = (std::strcmp(buf, attendu) == 0);
    if (ok) {
        ++g_ok;
    } else {
        ++g_ko;
    }
    std::printf("  %s %-34s [%s] -> [%s] (attendu [%s])\n", ok ? "ok  " : "ECHEC",
                nom, entree, buf, attendu);
}

int main()
{
    std::printf("sanitize_name, hors du jeu\n");

    // les cas vues dans la liste
    verifie("cote de mare fleur", "C\xC3\xB4te de mare fleur", "C\xC3\xB4te de mare fleur");
    verifie(" foret des foudres", "For\xC3\xAAt des foudres", "For\xC3\xAAt des foudres");
    verifie(" espaces preserves", "Colline de primepousse", "Colline de primepousse");

    // ce qui doit encore etre nettoye
    verifie(" saut de ligne -> espace", "a\nb", "a b");
    verifie(" tabulation -> espace", "a\tb", "a b");
    verifie(" carriage return", "a\rb", "a b");
    verifie(" DEL", "a\x7F" "b", "a b");

    // ce qui doit passer intact
    verifie(" ascii", "Test 123", "Test 123");
    verifie(" tiret et accent grave", "a-b_c", "a-b_c");
    verifie(" chinois", "\xE6\xB5\x8B\xE8\xAF\x95", "\xE6\xB5\x8B\xE8\xAF\x95");
    verifie(" vide", "", "");

    // null
    char buf[16];
    sanitize_name(buf, sizeof(buf), nullptr);
    std::printf("  %s null -> [%s]\n", buf[0] == '\0' ? "ok  " : "ECHEC", buf);
    (buf[0] == '\0') ? ++g_ok : ++g_ko;

    std::printf("\n%d ok, %d echec(s)\n", g_ok, g_ko);
    return g_ko ? 1 : 0;
}