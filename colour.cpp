/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#include <ostream>
#include <stdexcept>

#include "colour.h"

using namespace std;

namespace jailcur {

/* Initializes a cp_vector object with all zeros. */
cp_vector::cp_vector()
{
    for(int i = 0; i < 8; ++i)
        V[i] = 0;
}

}

/* Print colour to ostream */
ostream& operator<< (ostream& out, const colour& c)
{
    switch(c)
    {
      case colour::black:   out << "black";
                            break;
      case colour::red:     out << "red";
                            break;
      case colour::green:   out << "green";
                            break;
      case colour::yellow:  out << "yellow";
                            break;
      case colour::blue:    out << "blue";
                            break;
      case colour::magenta: out << "magenta";
                            break;
      case colour::cyan:    out << "cyan";
                            break;
      case colour::white:   out << "white";
                            break;
      default:              throw runtime_error("jailcur: colour: operator<<(): Invalid colour as parameter");
                            break;
    }
    return out;
}

/* Increments colour to the next value in terms of integers. If value is
 * colour::white (or 7), colour::max (or 8) is returned. This is intended for
 * iteration.
 *
 * Note that colour::max can not be incremented and that colour::min
 * does not need to be handled.
 */
void operator++ (colour& c)
{
    switch(c)
    {
      case colour::black:   c = colour::red;
                            break;
      case colour::red:     c = colour::green;
                            break;
      case colour::green:   c = colour::yellow;
                            break;
      case colour::yellow:  c = colour::blue;
                            break;
      case colour::blue:    c = colour::magenta;
                            break;
      case colour::magenta: c = colour::cyan;
                            break;
      case colour::cyan:    c = colour::white;
                            break;
      case colour::white:   c = colour::max;
                            break;
      case colour::max:     throw runtime_error(
                "jailcur: colour: operator++(): Attempted to increment colour::max");
      default:              throw runtime_error(
                "jailcur: colour: operator++(): Invalid colour as parameter");
                            break;
    }
}

/* Like operator++(), but for decrementation. It is provided only as the inverse
 * of operator++() as it is not particularly useful of iteration.
 */
void operator-- (colour& c)
{
    switch(c)
    {
      case colour::min:     throw runtime_error(
                "jailcur: colour: operator--(): Attempted to decrement colour::min");
                            break;
      case colour::red:     c = colour::black;
                            break;
      case colour::green:   c = colour::red;
                            break;
      case colour::yellow:  c = colour::green;
                            break;
      case colour::blue:    c = colour::yellow;
                            break;
      case colour::magenta: c = colour::blue;
                            break;
      case colour::cyan:    c = colour::magenta;
                            break;
      case colour::white:   c = colour::cyan;
                            break;
      case colour::max:     c = colour::white;
                            break;
      default:              throw runtime_error(
                "jailcur: colour: operator--(): Invalid colour as parameter");
                            break;
    }
}

