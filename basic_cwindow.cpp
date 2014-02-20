/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#include <list>

#include <curses.h>

#include "basic_cwindow.h"
#include "basic_message_window.h"
#include "util.h"

using namespace std;
using namespace jailcur;

/* Uses basic_message_window::create_window_ptr() to create the window list and
 * initialize the windows. A sub window is derived from the WINDOW* on the back
 * of the window list. This sub window is placed on the back of the window list.
 */
list<WINDOW*> basic_cwindow::create_window_ptr(int y, int x)
{
    list<WINDOW*> L;

    try
    {
        L = basic_message_window::create_window_ptr(y, x);

        WINDOW* sub_window = util::derive_window(L.back(), get_height() - 5,
                                    get_width() - 4, 4, 2);

        util::clear_screen(sub_window);

        L.push_back(sub_window);
    }
    catch(...) { throw; }   // Rethrow exception

    return L;
}

