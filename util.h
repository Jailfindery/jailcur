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

using namespace std;

namespace jailcur {

/* util acts as a static class where curses operations are wrapped so they do
 * not need to be invoked manually.
 */
namespace util
{

int get_ch();
void add_ch(char c, WINDOW* win, int y, int x);
void add_str(string str, WINDOW* win, int y, int x);
void clear_screen(WINDOW* win);
void delete_win(WINDOW* win);
void draw_border(WINDOW* win);
void draw_title(WINDOW* win, string str);
void refresh_win(WINDOW* win);
void set_attribute(WINDOW* win, int attrib);
WINDOW* new_win_ptr(int h, int w, int y, int x);
WINDOW* derive_win(WINDOW* b, int h, int w, int y, int x);

}

}

#endif /* JAILCUR_UTILITY_H_INCLUDED */

