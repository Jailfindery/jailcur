/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JAILCUR_COLOUR_H_INCLUDED
#define JAILCUR_COLOUR_H_INCLUDED

#include <ostream>

using namespace std;

namespace jailcur {

/* Used to specify colours for use in jailcur. Integer values for each colour
 * matches those defined in curses.
 */
enum class colour
{
    black = 0,
    red = 1,
    green = 2,
    yellow = 3,
    blue = 4,
    magenta = 5,
    cyan = 6,
    white = 7,

    min = 0,    /* Equal to colour::black */
    max = 8     /* Equal to colour::white "plus 1" */
};

/* Used as a data handle for cp_matrix in order to implement
 * pseudo-operator[][]. It is hard-coded to be an 8-vector.
 */
class cp_vector
{
  public:
    cp_vector();
    int& operator[] (const colour& x) { return V[static_cast<int>(x)]; }
    int& operator[] (const int& x) { return V[x]; }
  private:
    int V[8];
};

/* Used to store unique colour pair integers which can be looked-up using
 * a pair of colour values. Uses cp_vector to store rows. It is hard-coded to
 * be an 8-matrix.
 */
class cp_matrix
{
  public:
    cp_matrix() {}  /* Initialized through cp_vector::cp_vector() */
    cp_vector& operator[] (const colour& x) { return M[static_cast<int>(x)]; }
    cp_vector& operator[] (const int& x) { return M[x]; }
  private:
    cp_vector M[8];
};

}

using namespace jailcur;

/* colour operations */
ostream& operator<< (ostream& out, const colour& c);    /* Print to ostream */
void operator++ (colour& c);                            /* Increment */
void operator-- (colour& c);                            /* Decrement */

#endif /* JAILCUR_COLOUR_H_INCLUDED */

