/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JAILCUR_RENDER_H_INCLUDED
#define JAILCUR_RENDER_H_INCLUDED

#include <utility>
#include <vector>

#include "data.h"
#include "window_interface.h"

using namespace std;

namespace jailcur {

/* Responsible for taking window descriptions and drawing them on the
 * screen.
 *
 * Note that for stack objects, back is equilivalent to the top.
 */
class window_render
{
  public:
    window_render() {}

    static abstract_data::ptr get_top_input() { return get_top()->get_input(); }

    static int size() { return desc_stack.size(); }

    static void make_empty();

    static void pull_top();
    static void put_top(window_interface& n_win, int y, int x);

    static void rebuild_all();
    static void rebuild_top();

    static void refresh_all();
    static void refresh_standard();
    static void refresh_top();

    static window_interface* get_top() { return desc_stack.back(); }

  private:
    /* Stores the coordinates associated with each window_interface* object. The
     * first member is the y component and the second is the x.
     */
    static vector<pair<int, int> > coordinate_stack;
    static vector<WINDOW*> on_screen_stack;
    static vector<window_interface*> desc_stack;
};

static window_render render;

}

#endif /* JAILCUR_RENDER_H_INCLUDED */

