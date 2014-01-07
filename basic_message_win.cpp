#include <list>

#include <curses.h>

#include "basic_message_win.h"
#include "basic_win.h"
#include "util.h"

using namespace jailcur;

/* Uses basic_win::create_win_ptr() to create the window list and then adds the
 * message to the content window. If the list is L, L.back() is the content
 * window.
 *
 * Newline (\n) and tab (\t) characters are also interpreted correctly.
 */
list<WINDOW*> basic_message_win::create_win_ptr(int y, int x)
{
    list<WINDOW*> L;

    try
    {
        L = basic_win::create_win_ptr(y, x);

        const int text_height = get_height() - 2;
        const int text_width = get_width() - 2;
        const int start_height = 2;
        const int start_width = 2;

        WINDOW* content_win = L.back();

        string::iterator i = message.begin();

        for(int y = start_height; y < text_height && i != message.end(); ++y)
        {
            for(int x = start_width; x < text_width && i != message.end(); ++x)
            {
                if(*i == '\n')  // Support for newline characters
                {
                    ++i;
                    break;
                }
                if(*i == '\t')  // Support for tab characters
                {
                    ++i;
                    x += 4;
                }
                util::add_ch(*i, content_win, y, x);
                ++i;
            }
        }
    }
    catch(...) { throw; }
    return L;
}

