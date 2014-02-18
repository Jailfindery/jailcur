/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JAILCUR_BASIC_MESSAGE_WIN_H_INCLUDED
#define JAILCUR_BASIC_MESSAGE_WIN_H_INCLUDED

#include <list>
#include <string>

#include <curses.h>

#include "basic_win.h"
#include "colour.h"
#include "render.h"
#include "standard.h"

using namespace std;

namespace jailcur {

class basic_message_win : public basic_win
{
  friend class render;

  public:
    basic_message_win(string m = "",
                      string t = "",
                      int h = standard.get_maxy() - 4,
                      int w = standard.get_maxx() - 4,
                      colour f = colour::black,
                      colour b = colour::white,
                      colour s = colour::black)
        : message(m), basic_win(t, h, w, f, b, s)
    {}
    string get_message() { return message; }
    void set_message(string str) { message = str; }

  protected:
    virtual list<WINDOW*> create_win_ptr(int y, int x);

  private:
    string message;
};

}

#endif /* JAILCUR_BASIC_MESSAGE_WIN_H_INCLUDED */

