/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#include <stdexcept>
#include <string>

#include <curses.h>
#include <menu.h>

#include "standard.h"
#include "util.h"

using namespace std;
using namespace jailcur;

/* Gets a character from the user. */
int util::get_ch()
{
    return getch();
}

/* Creates a new ITEM* using the provided curses function new_item(). The string
 * is used for the item name and not its description; in fact, the description
 * is disabled. The string s must be available for the lifetime of the ITEM*.
 * The returned value must be deallocated with util::delete_item(). Throws
 * runtime_error on failure.
 */
ITEM* util::new_item(string& s)
{
    ITEM* I = ::new_item(s.c_str(), nullptr);
    if(I == nullptr)
        throw runtime_error("jailcur::util::new_item(): "
                            "Unable to allocate memory for an item.");
    return I;
}

/* Creates a new MENU* using the curses function new_menu(). The returned
 * value must be deallocated with util::delete_menu(). Throws runtime_error
 * on failure.
 */
MENU* util::new_menu(ITEM** item_list)
{
    MENU* M = ::new_menu(item_list);
    if(M == nullptr)
        throw runtime_error("jailcur::util::new_menu(): "
                            "Unable to allocate memory for a menu.");
    return M;
}

/* Adds a character to win at point (y,x). On error, runtime_error is thrown. */
void util::add_ch(char c, WINDOW* win, int y, int x)
{
    int rc = mvwaddch(win, y, x, c);
    if(rc)
        throw runtime_error("jailcur::util::add_ch(): "
                            "Unable to add character to window");
}

/* Add a string str to window win at position (y,x). On error,
 * std::runtime_error is thrown.
 */
void util::add_str(string str, WINDOW* win, int y, int x)
{
   int rc = mvwaddstr(win, y, x, str.c_str() );
   if(rc)
        throw runtime_error("jailcur: Unable to add string to window");
}

/* Uses curses functions to get the height and width of win and clears win of
 * any content, thus making the entire window the colour of bg. On failure,
 * std::runtime_error is thrown.
 */
void util::clear_screen(WINDOW* win)
{
    int y, x;
    getmaxyx(win, y, x);

    for(int i = 0; i < y; ++i)
        for(int k = 0; k < x; ++k)
            mvwaddch(win, i, k, ' ');
            /* Whilst mvwaddch() appears to produce a return code, it does not
             * appear to truthfully state how the operation went. Thus, rc-
             * checking for this function is not being done.
             */
}

/* Frees resources associated with an ITEM*. Throws runtime_error on failure.
 * Acts as a wrapper for free_item().
 */
void util::delete_item(ITEM* item)
{
    int rc = free_item(item);
    if(rc != E_OK)
        throw runtime_error("jailcur::util::delete_item(): "
                            "Unable to free menu item. Exited with ");
}

/* Frees resources associated with a MENU*. THrows runtime_error on failure.
 * Acts as a wrapper for free_menu().
 */
void util::delete_menu(MENU* menu)
{
    if(free_menu(menu) != 0)
        throw runtime_error("jailcur::util::delete_menu(): "
                            "Unable to free menu");
}

/* Deletes win. Throws runtime_error on error. Wraps delwin() */
void util::delete_window(WINDOW* win)
{
    int rc = delwin(win);
    if(rc)
        throw runtime_error("jailcur: util::delete_win(): "
                            "Unable to delete window.");
}

/* Draws a border around the perimeter of win. Throw runtime_error on non-zero
 * return.
 */
void util::draw_border(WINDOW* win)
{
    int rc = box(win, ACS_VLINE, ACS_HLINE);
    if(rc)
        throw runtime_error("jailcur::util::draw_border():"
                            "Unable to draw border");
}

/* Draws a centred title on the top row of win. Throws runtime_error on non-zero
 * return.
 */
void util::draw_title(WINDOW* win, string str)
{
    if(str.length() == 0) return;   // Don't need to draw it

    int L, offset;
    getmaxyx(win, offset, L);  // Dumps height in offset, temporarily
    offset = (L - (str.length() + 2) ) / 2;

    string title = ' ' + str + ' ';
    int rc = mvwaddstr(win, 0, offset, title.c_str() );
    if(rc)
        throw runtime_error("jailcur::util::draw_title():"
                            "Unable to add text to window");
}

/* Writes a menu to its associated sub window. The menu is unposted with
 * util::unpost_menu() It acts as a wrapper for post_menu(). Throws
 * runtime_error on failure.
 */
void util::post_menu(MENU* menu)
{
    if(::post_menu(menu) != 0)
        throw runtime_error("jailcur::util::post_menu(): Unable to post menu");
}

/* Refresh a window on the screen in order to remove overlaps of windows no
 * longer on the screen among other things. Wraps touchwin() and wrefresh().
 */
void util::refresh_window(WINDOW* win)
{
    if(win == nullptr)
        throw runtime_error("jailcur::util::refresh_win(): "
                            "Passed null window.");

    int rc1 = touchwin(win);
    if(rc1)
        throw runtime_error("jailcur::util::refresh_win(): "
                            "Unable to touch window");

    int rc2 = wrefresh(win);
    if(rc2)
        throw runtime_error("jailcur::util::refresh_win(): "
                            "Unable to refresh window");
}

/* Set video attributes of a window (e.g. give colour to a window). Throws
 * std::runtime_error on failure.
 */
void util::set_attribute(WINDOW* win, int attrib)
{
    int rc = wattrset(win, attrib);
    if(rc)
        throw runtime_error("jailcur: util::set_attribute: "
                            "Unable to set attribute(s)");
}

/* Associates a menu with a base window. It acts as a wrapper for set_menu_win()
 * and throws runtime_error on failure.
 */
void util::set_menu_base(MENU* menu, WINDOW* base)
{
    if(set_menu_win(menu, base) != 0)
        throw runtime_error("jailcur::util::set_menu_base(): "
                            "Unable to associate menu with base window.");
}

/* Sets the selected entry marker for a menu. It acts as a wrapper for
 * set_menu_mark(). Throws runtime_error on failure.
 */
void util::set_menu_marker(MENU* menu, const char* mark)
{
    if(set_menu_mark(menu, mark) != 0)
        throw runtime_error("jailcur::util::set_menu_marker(): "
                            "Unable to set thee menu marker.");
}

/* Sets the colour of selected entries of a menu. It acts as a wrapper for
 * set_menu_fore(). Throws runtime_error on failure.
 */
void util::set_menu_selected_colour(MENU* menu, colour t, colour b)
{
    if(set_menu_fore(menu, standard.get_cp(t, b) ) != 0)
        throw runtime_error("jailcur::util::set_menu_selected_colour(): "
                            "Unable to set selected entry colours.");
}

/* Associates a menu with a sub window. It acts as a wrapper for set_menu_win()
 * and throws runtime_error on failure.
 */
void util::set_menu_sub_window(MENU* menu, WINDOW* sub)
{
    if(set_menu_sub(menu, sub) != 0)
        throw runtime_error("jailcur::util::set_menu_base(): "
                            "Unable to associate menu with base window.");
}

/* Sets the colour of unselected entries of a menu. It acts as a wrapper for
 * set_menu_back(). Throws runtime_error on failure.
 */
void util::set_menu_unselected_colour(MENU* menu, colour t, colour b)
{
    if(set_menu_back(menu, standard.get_cp(t, b) ) != 0)
        throw runtime_error("jailcur::util::set_menu_unselected_colour(): "
                            "Unable to set unselected entry colours.");
}

/* Erases a menu with its associated sub window. It is the complement function
 * for util::post_menu() and is a wrapper for unpost_menu(). Throws
 * runtime_error on failure.
 */
void util::unpost_menu(MENU* menu)
{
    if(::unpost_menu(menu) != 0)
        throw runtime_error("jailcur::util::unpost_menu(): "
                            "Unable to unpost a menu.");
}

/* Creates a WINDOW* with height h and width w, with the top left corner at
 * point (x, y) relative to the top left corner of the screen. Throws runtime_
 * error on error. It acts as a wrapper for newwin().
 */
WINDOW* util::new_window_ptr(int h, int w, int y, int x)
{
    WINDOW* win = newwin(h, w, y, x);
    if(win == nullptr)
        throw runtime_error("jailcur: create_win_ptr(): Cannot create window");
    return win;
}

/* Creates a WINDOW* that has been derived from another WINDOW*, b. The y and x
 * coordinates are relative to the upper left corner of b. Throws runtime_error
 * on error. It acts as a wrapper for derwin().
 */
WINDOW* util::derive_window(WINDOW* b, int h, int w, int y, int x)
{
    WINDOW* sub = derwin(b, h, w, y, x);
    if(sub == nullptr)
        throw runtime_error("jailcur::derive_win(): "
                            "Cannot create derived window");
    return sub;
}

