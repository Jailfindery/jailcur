/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#include <list>

#include <curses.h>

#include "basic_win.h"
#include "colour.h"
#include "data.h"
#include "standard.h"
#include "util.h"

using namespace std;
using namespace jailcur;

/* Gets input from the user. For basic_win, this member waits for the user to
 * press a key and then returns a win_data<bool> that has a value of true.
 *
 * To retrieve data, data::data_cast<bool>() must be used.
 *
 * Because abstract_data::ptr is, in fact, a "smart pointer," it need not be
 * deleted or even stored.
 */
abstract_data::ptr basic_win::get_input()
{
    util::get_ch();
    abstract_data::ptr P(new win_data<bool>(true) );
    return P;
}

/* Creates WINDOW* objects in a list with the top left corner of the content
 * window at point (x, y) relative to the top left corner of the screen. The
 * list contains the content and shadow window, in that order (i.e. with shadow
 * window added last) so render can render them in the proper order.
 *
 * NB! TODO: Add content to the content window.
 */
list<WINDOW*> basic_win::create_win_ptr(int y, int x)
{
    list<WINDOW*> my_list;
    WINDOW* shadow;
    WINDOW* content;

    try
    {

        shadow = util::new_win_ptr(get_height(), get_width(), y + 1, x + 2);
        content = util::new_win_ptr(get_height(), get_width(), y, x);

        /* Setting windows to the proper colour */
        util::set_attribute(shadow, standard.get_cp(get_shadow_colour(),
                                                     get_shadow_colour() ) );
        util::clear_screen(shadow);
        util::set_attribute(content, standard.get_cp(get_text_colour(),
                                                      get_bg_colour() ) );
        util::clear_screen(content);

        /* Adding basic content to content window */
        util::draw_border(content);
        util::draw_title(content, get_title() );

        /* We must create the list at the end in order to have the real pointers. */
        my_list.push_back(shadow);
        my_list.push_back(content);

    }
    catch(...) { throw; }

    /* FIXME: Does this cause my_list to be copied? It would still work, but
     *        it would be more expensive. */
    return my_list;
}

