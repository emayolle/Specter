// Specter.Internal — game input gate (implementation).
//
// NOUS NE TOUCHONS PLUS AU CURSEUR. C'EST LA REGLE.
//
// Ce fichier derivait sept exports user32 avec notre moteur de detour (detour.*,
// port du moteur de l'overlay Steam) :
//   GetRawInputData, GetRawInputBuffer, GetAsyncKeyState, GetKeyState,
//   ClipCursor, ShowCursor, SetCursor
//
// Les quatre premiers restent. Les trois derniers — ClipCursor, ShowCursor et
// SetCursor — ont ete RETIRES.
//
// POURQUOI, ET CE QUE CA COUTAIT
//
// Un jeu a la premiere personne cache son propre curseur : il appelle
// SetCursor(NULL) et rogne la souris a la fenetre. Pour afficher un menu, il
// faut donc deriver le curseur -- ce que faisait enter_menu(), qui enregistrait
// la zone de rognage et le compteur d'affichage, forcait SetCursor(NULL), puis
// restaurait tout a la fermeture.
//
// Ce systeme etait fragile PAR CONSTRUCTION, et la restauration en particulier
// ne pouvait pas etre exacte : le compteur de ShowCursor est une PILE, pas un
// booleen. Il existe meme un etat invalide, ou le jeu croit le curseur visible
// alors qu'il ne l'est pas. Toute la logique etait une reconstruction de la
// pile de Win32, contre un jeu qu'on ne controle pas.
//
// Le resultat etait ce que le menu montrait deja : un curseur inutile.
//
// CE QU'ON FAIT MAINTENANT
//
// On ne touche a rien. Les ClipCursor / ShowCursor / SetCursor du jeu
// s'executent, le jeu garde SON etat de curseur — cache en jeu, ce qui est
// coherent — et le menu se contente de dessiner un POINT a la position souris,
// sur la draw list d'avant-plan. Voir d3d12_overlay.cpp.
//
// Un point ne demande aucune release, aucune sauvegarde, et rien a restaurer :
// il n'y a plus d'etat a synchroniser, donc plus rien a desynchroniser.
//
// Ce qui reste du gate, c'est l'ENTREE : sans ca, un clic dans le menu
// traverserait vers le jeu et le personnage tournerait. Les quatre detours
// d'entree et la sous-classe de fenetre restent donc intacts.
//
// Threading: the hooks run on whatever thread the game polls input from, so they
// only touch the atomic flag and the (immutable after install) trampolines.
// set_menu_open() runs on the render thread.

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>   // GET_X_LPARAM / GET_Y_LPARAM, comme le backend Win32
// L'API d'entree brute est voluntaryment EXCLUE de windows.h par
// WIN32_LEAN_AND_MEAN. Sans ce header, GetRawInputSize et les structures
// RAWINPUT/RAWMOUSE n'existent pas — et c'est exactement ce qu'on consomme pour
// la position du curseur virtuel. Pas une approximation : un header manquant,
// qui se lit comme un appel non declare.
#include <winuser.h>

#include <atomic>
#include <cstdint>

#include "render/input.h"
#include "platform/hook/detour.h"
#include "platform/log.h"

namespace specter {
namespace input {
namespace {

std::atomic<bool> g_open{false};
std::atomic<bool> g_ungate{false};  // true only around a keyboard_sink call
std::atomic<keyboard_sink> g_sink{nullptr};

// LE CURSEUR VIRTUEL DU MENU.
//
// Une position en pixels ecran, mise a jour par les deltas bruts. Distincte de
// la position du curseur de l'OS, qui reste celle du jeu : celle-la ne bouge
// pas tant que le jeu verrouille la souris.
struct CurseurVirtuel {
    int x = 0;
    int y = 0;
    // Bornes de la zone ou le curseur peut aller : la fenetre du jeu, donc le
    // menu est entierement atteignable. Un delta qui deborde est PERDU, pas
    // mis de cote -- c'est ce que font les jeux, et c'est le comportement qu'on
    // attend d'un curseur.
    int min_x = 0, min_y = 0, max_x = 1, max_y = 1;
};
CurseurVirtuel g_curseur;

void accumuler_delta(int dx, int dy)
{
    g_curseur.x += dx;
    g_curseur.y += dy;

    // Le verrouillage n'est PAS un simple clamp : un curseur de jeu se
    // recentre quand il atteint un bord, sinon il devient impossible d'atteindre
    // le coin oppose apres avoir bute dans l'autre sens. Un clamp simple
    // enfermerait le curseur des qu'on le pousse vers une extremite.
    if (g_curseur.x < g_curseur.min_x || g_curseur.x > g_curseur.max_x) {
        g_curseur.x = (g_curseur.min_x + g_curseur.max_x) / 2;
    }
    if (g_curseur.y < g_curseur.min_y || g_curseur.y > g_curseur.max_y) {
        g_curseur.y = (g_curseur.min_y + g_curseur.max_y) / 2;
    }
}
bool g_armed = false;
bool g_gave_up = false;

// Trampolines handed back by the engine (the original user32 code).
using GetRawInputData_t = UINT(WINAPI*)(HRAWINPUT, UINT, LPVOID, PUINT, UINT);
using GetRawInputBuffer_t = UINT(WINAPI*)(PRAWINPUT, PUINT, UINT);
using GetAsyncKeyState_t = SHORT(WINAPI*)(int);
using GetKeyState_t = SHORT(WINAPI*)(int);

GetRawInputData_t real_get_raw_input_data = nullptr;
GetRawInputBuffer_t real_get_raw_input_buffer = nullptr;
GetAsyncKeyState_t real_get_async_key_state = nullptr;
GetKeyState_t real_get_key_state = nullptr;

// ---- hook proxies --------------------------------------------------------

UINT WINAPI hk_get_raw_input_data(HRAWINPUT h, UINT cmd, LPVOID data, PUINT size,
                                  UINT hdr)
{
    if (g_open.load(std::memory_order_relaxed)) {
        if (size) {
            *size = 0;
        }
        return static_cast<UINT>(-1);
    }
    return real_get_raw_input_data(h, cmd, data, size, hdr);
}

UINT WINAPI hk_get_raw_input_buffer(PRAWINPUT data, PUINT size, UINT hdr)
{
    if (g_open.load(std::memory_order_relaxed)) {
        if (size) {
            *size = 0;
        }
        return 0;
    }
    return real_get_raw_input_buffer(data, size, hdr);
}

SHORT WINAPI hk_get_async_key_state(int vk)
{
    if (g_open.load(std::memory_order_relaxed) &&
        !g_ungate.load(std::memory_order_relaxed)) {
        return 0;
    }
    return real_get_async_key_state(vk);
}

SHORT WINAPI hk_get_key_state(int vk)
{
    if (g_open.load(std::memory_order_relaxed) &&
        !g_ungate.load(std::memory_order_relaxed)) {
        return 0;
    }
    return real_get_key_state(vk);
}

// ---- window subclass -----------------------------------------------------
//
// The user32 hooks above cover raw input and polled key state, but Unity also
// reads mouse buttons / keys from window messages (DispatchMessage ->
// WndProc), which is why a left-click still reached the game. Subclassing the
// game window lets us (a) swallow every input message while the menu is up and
// (b) defeat DefWindowProc(WM_SETCURSOR) — which would otherwise restore the
// game's NULL class cursor and hide the cursor again.

WNDPROC g_orig_wndproc = nullptr;
HWND g_wnd = nullptr;

bool is_keyboard_msg(UINT msg)
{
    switch (msg) {
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_CHAR:
        case WM_SYSCHAR:
        case WM_DEADCHAR:
        case WM_UNICHAR:
            return true;
        default:
            return false;
    }
}

LRESULT CALLBACK wnd_proc(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    if (g_open.load(std::memory_order_relaxed)) {
        // Keyboard: feed ImGui (the console needs text input) then swallow, so
        // the game never sees the keystroke. The gate is lifted for the callee
        // so the Win32 ImGui backend reads the real modifier state.
        if (is_keyboard_msg(msg)) {
            keyboard_sink sink = g_sink.load(std::memory_order_relaxed);
            if (sink) {
                g_ungate.store(true, std::memory_order_relaxed);
                sink(h, msg, static_cast<uintptr_t>(w),
                     static_cast<intptr_t>(l));
                g_ungate.store(false, std::memory_order_relaxed);
            }
            return 0;
        }

        // LE CURSEUR VIRTUEL. C'est ici que se joue « la pastille ne bouge pas ».
        //
        // Le jeu a la souris VERROUILLEE : il appelle ClipCursor et SetCursor, qu'on
        // ne touche plus, donc le curseur de l'OS reste captive et ne bouge pas.
        // En meme temps il pilote sa camera par ENTREE BRUTE (WM_INPUT), qu'on avale
        // pour qu'il ne reagisse pas a une case cochee.
        //
        // Resultat : plus de curseur, plus de camera, et un menu inutilisable. C'est
        // la consequence inevitable de « ne touche pas au curseur du jeu » : on ne
        // peut pas liberer SA souris sans manipuler la nôtre.
        //
        // On fait donc ce que font les jeux eux-memes : un curseur VIRTUEL alimente
        // par les deltas bruts. L'OS ne bouge pas, on ne demande rien au jeu, et le
        // menu a un curseur qui repond.
        //
        // WM_MOUSEMOVE ne sert a rien ici : il rapporte la position du curseur de
        // l'OS -- celle du jeu, donc verrouillee. C'est WM_INPUT qui porte le
        // DEPLACEMENT, et c'est exactement le message qu'on avale deja.
        if (msg == WM_MOUSEMOVE) {
            // Passe au jeu : Unity en a besoin meme verrouille, et l'avaler
            // l'empecherait de recalculer son etat interne.
            if (g_orig_wndproc) {
                return ::CallWindowProcW(g_orig_wndproc, h, msg, w, l);
            }
            return ::DefWindowProcW(h, msg, w, l);
        }

        // LE DELTA BRUT, qu'on consomme et qu'on avale ensuite.
        //
        // On appelle le TRAMPOLINE (real_get_raw_input_data) et pas l'export :
        // appeler l'export nous reramenerait dans notre propre hook, qui renvoie
        // un echec -- et le delta disparaitrait en silence.
        //
        // PAS GetRawInputSize : ce SDK de headers ne le declare pas, alors que
        // dwSize -- la taille que GetRawInputData ecrirait -- est deja dans le
        // header RAWINPUT. Une seule lecture suffit, et elle est deja faite.
        if (msg == WM_INPUT) {
            RAWINPUT brut = {};
            UINT lu = sizeof(brut);
            if (real_get_raw_input_data(reinterpret_cast<HRAWINPUT>(l), RID_INPUT,
                                        &brut, &lu, sizeof(RAWINPUTHEADER)) !=
                    static_cast<UINT>(-1) &&
                brut.header.dwType == RIM_TYPEMOUSE) {
                accumuler_delta(brut.data.mouse.lLastX, brut.data.mouse.lLastY);
            }
            return 0;
        }

        switch (msg) {
            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_LBUTTONDBLCLK:
            case WM_RBUTTONDOWN:
            case WM_RBUTTONUP:
            case WM_RBUTTONDBLCLK:
            case WM_MBUTTONDOWN:
            case WM_MBUTTONUP:
            case WM_MBUTTONDBLCLK:
            case WM_XBUTTONDOWN:
            case WM_XBUTTONUP:
            case WM_XBUTTONDBLCLK:
            case WM_MOUSEWHEEL:
            case WM_MOUSEHWHEEL:
            case WM_INPUT:
                return 0;  // the game sees no BUTTON while the menu is open
            default:
                break;
        }
    }
    if (g_orig_wndproc) {
        return ::CallWindowProcW(g_orig_wndproc, h, msg, w, l);
    }
    return ::DefWindowProcW(h, msg, w, l);
}

}  // namespace

bool install(void* hwnd)
{
    (void)hwnd;
    if (g_armed) {
        return true;
    }
    if (g_gave_up) {
        return false;
    }

    HMODULE user32 = ::GetModuleHandleW(L"user32.dll");
    if (!user32) {
        log::error("input: user32.dll not found");
        return false;
    }

    struct Target {
        const char* name;
        const char* proc;
        void* hook;
        void** orig;
    };
    const Target targets[] = {
        {"GetRawInputData", "GetRawInputData", (void*)&hk_get_raw_input_data,
         (void**)&real_get_raw_input_data},
        {"GetRawInputBuffer", "GetRawInputBuffer", (void*)&hk_get_raw_input_buffer,
         (void**)&real_get_raw_input_buffer},
        {"GetAsyncKeyState", "GetAsyncKeyState", (void*)&hk_get_async_key_state,
         (void**)&real_get_async_key_state},
        {"GetKeyState", "GetKeyState", (void*)&hk_get_key_state,
         (void**)&real_get_key_state},
    };

    const int total = static_cast<int>(sizeof(targets) / sizeof(targets[0]));
    int hooked = 0;
    for (const Target& t : targets) {
        void* fn = reinterpret_cast<void*>(::GetProcAddress(user32, t.proc));
        if (!fn) {
            log::error("input: %s not found in user32", t.proc);
            continue;
        }
        if (hook::is_installed(fn)) {
            log::info("input: %s already detoured - reusing", t.name);
            ++hooked;
            continue;
        }
        if (hook::install(fn, t.hook, t.orig, t.name)) {
            ++hooked;
        }
    }

    if (hooked == 0) {
        g_gave_up = true;
        log::error("input: no hooks installed - input gate off");
        return false;
    }

    g_armed = true;

    // Subclass the game window: swallow input messages (the left-click leak)
    // and own WM_SETCURSOR while the menu is open.
    if (hwnd && !g_orig_wndproc) {
        g_wnd = reinterpret_cast<HWND>(hwnd);
        ::SetLastError(0);
        g_orig_wndproc = reinterpret_cast<WNDPROC>(::SetWindowLongPtrW(
            g_wnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&wnd_proc)));
        if (!g_orig_wndproc) {
            const DWORD e = ::GetLastError();
            if (e) {
                log::error("input: window subclass failed (%lu) - the game may "
                           "still see message-level input",
                           e);
            }
        } else {
            log::info("input: game window subclassed (%p)", (void*)g_wnd);
        }
    }

    if (hooked == total) {
        log::info("input: gate armed (%d/%d user32 functions hooked)", hooked,
                  total);
    } else {
        log::error("input: gate armed PARTIAL (%d/%d hook failed - see above)",
                   hooked, total);
    }
    return true;
}

void set_keyboard_sink(keyboard_sink fn)
{
    g_sink.store(fn, std::memory_order_relaxed);
}


void set_menu_open(bool open)
{
    // UN SEUL FLAG, ET C'EST TOUT.
    //
    // Ce fonction faisait 60 lignes : il enregistrait la zone de rognage du
    // jeu et le compteur d'affichage du curseur, forcait SetCursor(NULL) a
    // l'ouverture, puis les restaurait exactement a la fermeture — y compris un
    // rattrapage du compteur ShowCursor, boucle de 64 iterations, parce que le
    // compteur de Win32 est une pile et non un booleen.
    //
    // Tout cela etait la pour une FLICHE. On dessine maintenant un point (voir
    // d3d12_overlay.cpp), donc plus personne ne touche au curseur du jeu : ses
    // propres ClipCursor / ShowCursor / SetCursor s'executent normalement, et
    // l'etat dans lequel il les laisse est le sien.
    //
    // Ce qui reste, c'est le blocage d'ENTREE : sans lui, un clic dans le menu
    // traverserait vers le jeu et le personnage tournerait.
    g_open.store(open, std::memory_order_relaxed);

    // A L'OUVERTURE, LE CURSEUR VIRTUEL AU CENTRE DE LA FENETRE.
    //
    // Pas a zero : (0,0) est le coin haut-gauche, donc le menu s'ouvrirait avec
    // le curseur colle en haut a gauche, au-dessus du premier onglet. Et pas
    // « la ou etait le curseur de l'OS » : celle-la est verrouillee au centre par
    // le jeu, donc on commencerait exactement la ou on a fini la derniere fois.
    if (open && g_wnd) {
        RECT r = {};
        if (::GetClientRect(g_wnd, &r)) {
            g_curseur.min_x = 0;
            g_curseur.min_y = 0;
            g_curseur.max_x = r.right - 1;
            g_curseur.max_y = r.bottom - 1;
            g_curseur.x = (r.right - 1) / 2;
            g_curseur.y = (r.bottom - 1) / 2;
        }
    }
}

bool curseur_pos(int* x, int* y)
{
    if (!g_wnd) {
        return false;
    }
    if (x) *x = g_curseur.x;
    if (y) *y = g_curseur.y;
    return true;
}

bool armed()
{
    return g_armed;
}

short real_async_key_state(int vk)
{
    if (real_get_async_key_state) {
        return real_get_async_key_state(vk);
    }
    return ::GetAsyncKeyState(vk);
}

}  // namespace game_input
}  // namespace specter::dxgi
