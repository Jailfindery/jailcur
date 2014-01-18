#include <list>

#include <curses.h>

#include "message_win.h"
#include "util.h"

using namespace jailcur;

/* Adds a button to the bottom centre of the content window. To do this, the
 * line above the button must be cleared of any text placed by basic_message_
 * win::create_win_ptr().
 */
list<WINDOW*> message_win::create_win_ptr(int y, int x)
{
    list<WINDOW*> L;

    try
    {
        L = basic_message_win::create_win_ptr(y, x);
        WINDOW* content_win = L.back();

        for(int y = get_height() - 3, x = 1; x < get_width() - 1; ++x)
            util::add_ch(' ', content_win, y, x);

        util::set_attribute(content_win, standard.get_cp(colour::white,
                                                          colour::red) );
        int o = (get_width() - button_text.length() ) / 2;     // Button offset
        string::iterator i = button_text.begin();
        for(int y = get_height() - 2, x = o; i != button_text.end(); ++x)
        {
            util::add_ch(*i, content_win, y, x);
            ++i;
        }

    }
    catch(...) { throw; }
    return L;
}

