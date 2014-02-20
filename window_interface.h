/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JAILCUR_WINDOW_INTERFACE_H_INCLUDED
#define JAILCUR_WINDOW_INTERFACE_H_INCLUDED

#include <list>
#include <string>

#include <curses.h>

#include "colour.h"
#include "data.h"

using namespace std;

namespace jailcur
{

class window_render;   /* Forward declaration */

/* Acts as an interface for all window objects. Allows any type of window to be
 * rendered by render.
 */
class window_interface
{
  friend class window_render;

  public:
    window_interface() {}

  protected:
    virtual list<WINDOW*> create_window_ptr(int y, int x) = 0;

  private:
    /* Returns the number of elements returned from create_win_ptr(). */
    virtual const int get_list_size() = 0;

    virtual abstract_data::ptr get_input() = 0;
};

}

#endif /* JAILCUR_WINDOW_INTERFACE_H_INCLUDED */

