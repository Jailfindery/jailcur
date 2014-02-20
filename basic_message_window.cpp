/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#include <list>

#include <curses.h>

#include "basic_message_window.h"
#include "basic_window.h"
#include "util.h"

using namespace jailcur;

/* Uses basic_window::create_window_ptr() to create the window list and then adds the
 * message to the content window. If the list is L, L.back() is the content
 * window.
 *
 * Newline (\n) and tab (\t) characters are also interpreted correctly.
 */
list<WINDOW*> basic_message_window::create_window_ptr(int y, int x)
{
    list<WINDOW*> L;

    try
    {
        L = basic_window::create_window_ptr(y, x);

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

