/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#include <list>
#include <string>

#include <curses.h>

#include "progress_window.h"
#include "util.h"

using namespace std;
using namespace jailcur;

/* Tests if whatever the window tracks is complete or not. */
bool progress_window::is_complete()
{
    if(numerator >= denominator)
        return true;
    return false;
}

/* Uses basic_message_window::create_window_list() to create the window list and
 * initialize the content. L.back() is the content window. This adds the
 * progress bar with the relevant information.
 */
list<WINDOW*> progress_window::create_window_list(int y, int x)
{
    list<WINDOW*> L;

    try
    {
        L = basic_message_window::create_window_list(y, x);
        WINDOW* content = L.back();

        int width = get_width();
        int height = get_height();

        /* Add numeric data (first line):
         *   - Fractional data (e.g. 42/100)
         *   - Percent data (e.g. 42%)
         */
        string fract_data = to_string(numerator) + "/" + to_string(denominator);
        util::add_str(fract_data, content, (height - 3), 2);

        string per_len = to_string(int(float(numerator) / float(denominator)
                         * 100) )
                         + " %";
        util::add_str(per_len, content, (height - 3), (width - per_len.size() - 2) );

        /* Add progress bar:
         *   - Progress bar ends (i.e. [ ... ] )
         *   - Progress fill (e.g. ====)
         *   - Progress tip (e.g. >)
         * The bar string is constructed to fit perfectly within the window.
         */
        int bar_length;
       
        if(numerator == denominator)
            bar_length = (width - 6);
        else if(numerator > denominator)
            bar_length = (width - 6);
        else
            bar_length = int( (width - 6)
                         * ( float(numerator) / float(denominator) ) );

        string bar = "[";
        for(int i = 0; i < (bar_length - 1) && i < (width - 7) ; ++i)
            bar += "=";
        bar += ">";

        for(int i = 0; bar.size() <= (width - 6); ++i)
            bar += " ";
        bar += "]";

        util::add_str(bar, content, (height - 2), 2);
    }
    catch(...) { throw; } // Rethrow

    return L;
}

