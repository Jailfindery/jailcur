/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JAILCUR_PROGRESS_WINDOW_H_INCLUDED
#define JAILCUR_PROGRESS_WINDOW_H_INCLUDED

#include <list>
#include <string>

#include <curses.h>

#include "basic_message_window.h"
#include "colour.h"
#include "util.h"

using namespace std;

namespace jailcur {

class progress_window : public basic_message_window
{
  public:
    progress_window(int& num,
                 int& den,
                 string m = "",
                 string t = "",
                 int h = standard.get_maxy() - 4,
                 int w = standard.get_maxx() - 4,
                 colour f = colour::black,
                 colour b = colour::white,
                 colour s = colour::black)
        : basic_message_window(m, t, h, w, f, b, s),
          numerator(num), denominator(den)
    {}
    bool is_complete();

  protected:
    virtual list<WINDOW*> create_window_ptr(int y, int x);

  private:
    int& numerator;
    int& denominator;
};

}

#endif /* JAILCUR_PROGRESS_WINDOW_H_INCLUDED */

