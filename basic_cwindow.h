/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JAILCUR_BASIC_CWINDOW_H_INCLUDED
#define JAILCUR_BASIC_CWINDOW_H_INCLUDED

#include <list>

#include <curses.h>

#include "basic_message_window.h"

using namespace std;

namespace jailcur
{

/* Contains a sub win embedded inside of a basic_message_window. It contains no
 * real functionality and is simply intended to be derived from.
 */
class basic_cwindow : public basic_message_window
{
  protected:
    basic_cwindow(string m = "", 
                  string t = "", 
                  int h = standard.get_maxy() - 4,
                  int w = standard.get_maxx() - 4,
                  colour f = colour::black,
                  colour b = colour::white,
                  colour s = colour::black)
        : basic_message_window(m, t, h, w, f, b, s)
    {}
    virtual list<WINDOW*> create_window_list(int y, int x);

  private:
    virtual const int get_list_size() { return 3; }
};

}

#endif /* JAILCUR_BASIC_CWINDOW_H_INCLUDED */

