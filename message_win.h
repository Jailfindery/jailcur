/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JAILCUR_MESSAGE_WIN_H_INCLUDED
#define JAILCUR_MESSAGE_WIN_H_INCLUDED

#include <list>
#include <string>

#include <curses.h>

#include "basic_message_win.h"
#include "colour.h"
#include "render.h"
#include "standard.h"

using namespace std;

namespace jailcur {

/* A more user-friendly version of basic_message_win in that it has an OK
 * button, allowing for the "Press any key to continue" to simply be under-
 * stood.
 */
class message_win : public basic_message_win
{
  public:
    message_win(string r = " OK ",
                string m = "",
                string t = "",
                int h = standard.get_maxy() - 4,
                int w = standard.get_maxx() - 4,
                colour f = colour::black,
                colour b = colour::white,
                colour s = colour::black)
        : basic_message_win(m, t, h, w, f, b, s)
    { set_button_text(r); }

    void set_button_text(string str) { button_text = " " + str + " "; }
    string get_button_text()
    {
        return button_text.substr(2, button_text.size() - 3 );
    }

  protected:
    virtual list<WINDOW*> create_win_ptr(int y, int x);

  private:
    string button_text;
};

}

#endif /* JAILCUR_MESSAGE_WIN_H_INCLUDED */

