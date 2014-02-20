/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JAILCUR_UTILITY_H_INCLUDED
#define JAILCUR_UTILITY_H_INCLUDED

#include <string>

#include <curses.h>
#include <menu.h>

using namespace std;

namespace jailcur {

/* util acts as a static class where curses operations are wrapped so they do
 * not need to be invoked manually.
 */
namespace util
{

int get_ch();
ITEM* new_item(string& s);
MENU* new_menu(ITEM** item_list);
void add_ch(char c, WINDOW* win, int y, int x);
void add_str(string str, WINDOW* win, int y, int x);
void clear_screen(WINDOW* win);
void delete_item(ITEM* item);
void delete_menu(MENU* menu);
void delete_window(WINDOW* win);
void draw_border(WINDOW* win);
void draw_title(WINDOW* win, string str);
void post_menu(MENU* menu);
void refresh_window(WINDOW* win);
void set_attribute(WINDOW* win, int attrib);
void set_menu_base(MENU* menu, WINDOW* base);
void set_menu_marker(MENU* menu, const char* mark);
void set_menu_selected_colour(MENU* menu, colour t, colour b);
void set_menu_sub_window(MENU* menu, WINDOW* sub);
void set_menu_unselected_colour(MENU* menu, colour t, colour b);
void unpost_menu(MENU* menu);
WINDOW* new_window_ptr(int h, int w, int y, int x);
WINDOW* derive_window(WINDOW* b, int h, int w, int y, int x);

}

}

#endif /* JAILCUR_UTILITY_H_INCLUDED */

