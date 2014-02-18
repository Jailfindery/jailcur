#include <list>

#include <curses.h>

#include "basic_cwin.h"
#include "basic_message_win.h"
#include "util.h"

using namespace std;
using namespace jailcur;

/* Uses basic_message_win::create_win_ptr() to create the window list and
 * initialize the windows. A sub window is derived from the WINDOW* on the back
 * of the window list. This sub window is placed on the back of the window list.
 */
list<WINDOW*> basic_cwin::create_win_ptr(int y, int x)
{
    list<WINDOW*> L;

    try
    {
        L = basic_message_win::create_win_ptr(y, x);

        WINDOW* sub_window = util::derive_win(L.back(), get_height() - 5,
                                    get_width() - 4, 4, 2);

        util::clear_screen(sub_window);

        L.push_back(sub_window);
    }
    catch(...) { throw; }   // Rethrow exception

    return L;
}

