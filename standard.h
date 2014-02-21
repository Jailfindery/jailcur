/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JAILCUR_STANDARD_H_INCLUDED
#define JAILCUR_STANDARD_H_INCLUDED

#include <string>

#include <curses.h>

#include "colour.h"

using namespace std;

namespace jailcur {

class window_render;   /* Forward reference */

/* Static class to manage everything related to curses' stdscr and other
 * global curses data.
 */
class standard_screen
{
  friend class window_render;

  public:
    standard_screen() {}

    static bool is_started() { return started; }

    static int get_cp(colour f, colour b);

    /* TODO: Should get_max*() check if jailcur has been started? */
    static int get_maxx() { return maxx; }
    static int get_maxy() { return maxy; }
    /* Note: get_maxyx() is so named because it is similar to what the
     * equilivalent curses function is named.
     */

    static colour get_bg_colour() { return bg; }
    static colour get_text_colour() { return text; }
    static void set_bg_colour(colour c);
    static void set_text_colour(colour c);

    static string get_title() { return title; }
    static void set_title(string str) { title = str; }

    static void engage_disco_mode();

    static void start();
    static void stop();

  private:
    static bool started;

    static cp_matrix cp;
    static colour bg;
    static colour text;
    static int current_cp;      /* Used for colour pair allocation */
    static void init_cp_matrix();

    static int maxy, maxx;      /* FIXME: Required? */

    static string title;

    static WINDOW* standard_window;

    static WINDOW* create_window_list();
};

static standard_screen standard;

}

#endif /* JAILCUR_STANDARD_H_INCLUDED */

