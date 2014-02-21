/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#include <stdexcept>
#include <string>

#include <curses.h>

#include "colour.h"
#include "render.h"
#include "util.h"
#include "standard.h"

using namespace std;
using namespace jailcur;

/* FIXME: Error checking on _all_ applicable calls from curses. */

/* Initialization of static members of standard */
bool standard_screen::started = false;
cp_matrix standard_screen::cp {};
int standard_screen::current_cp = 0;
colour standard_screen::bg = colour::blue;
colour standard_screen::text = colour::cyan;
int standard_screen::maxy = -1;
int standard_screen::maxx = -1;
string standard_screen::title {};
WINDOW* standard_screen::standard_window = nullptr;

/* Creation of centralized standard screen object */
standard_screen standard {};

/* Gets the colour pair from the table generated at start up. As a result,
 * standard::start() must be run in order to have it available. If it has not
 * been called, std::runtime_error is thrown.
 *
 * The value from the table is processed through COLOR_PAIR so the result can
 * be immediately used as a video attribute.
 */
int standard_screen::get_cp(colour f, colour b)
{
    if(!is_started() )
        throw runtime_error("jailcur: standard: get_cp(): jailcur not started");
    return COLOR_PAIR(cp[f][b]);
}

/* Set the background colour to c. If c is not in [colour::min, colour::max),
 * std::runtime_error is thrown.
 */
void standard_screen::set_bg_colour(colour c)
{
    if(!(c >= colour::min && c < colour::max) )
        throw runtime_error("jailcur: standard: set_bg_colour(): out of range");
    bg = c;
}

/* Set the text colour to c. If c is not in [colour::min, colour::max),
 * std::runtime_error is thrown.
 */
void standard_screen::set_text_colour(colour c)
{
    if(!(c >= colour::min && c < colour::max) )
        throw runtime_error("jailcur: standard: set_text_colour(): out of range");
    text = c;
}

/* Call for a surprise... */
void standard_screen::engage_disco_mode()
{
    if(!is_started() )
        throw runtime_error("jailcur: engage_disco_mode(): jailcur not started");
    colour orig = get_bg_colour();
    timeout(100);

    int c = util::get_ch();
    while(c != 10)  /* Enter key */
    {
        colour co = get_bg_colour();
        if(co == colour::cyan) co = colour::min;
        ++co;

        set_bg_colour(co);
        render.refresh_all();
        c = util::get_ch();
    }
    /* Set global attributes back to normal. */
    set_bg_colour(orig);
    render.refresh_all();
    timeout(-1);
}

/* Starts the curses environment and sets various preferrable attributes. If
 * startup fails, std::runtime_error is thrown.
 */
void standard_screen::start()
{
    standard_window = initscr();   /* Start curses environment.            */
    if(standard_window == nullptr)
        throw runtime_error("jailcur::standard::start():"
                            "Unable to start jailcur");
    started = true;

    timeout(-1);                   /* Use blocking when reading input.     */
    start_color();                 /* Enables use of colour.               */
    cbreak();                      /* Does not process special characters? */
    noecho();                      /* Typed characters do not appear.      */
    keypad(standard_window, true); /* Enables getting arrow key presses.   */
    curs_set(0);                   /* Disables the cursor.                 */

    /* Set x and y dimensions of screen.
     * TODO: Allow for maximum dimensions to be changed throughout program.
     *       Also, error checking?
     */
    getmaxyx(standard_window, maxy, maxx); 

    /* TODO: Configure cp's on demand. */
    init_cp_matrix();           /* Initializes colour all colour pairs. */

    render.refresh_standard(); /* Draws standard on screen. */
}

/* Stops the curses environment. Throws std::runtime_error on error.
 *
 * TODO: Ensure all WINDOW* objects on render stack have been freed.
 */
void standard_screen::stop()
{
    int rc = endwin();
    if(rc)
        throw runtime_error("jailcur::standard::stop(): "
                            "Unable to stop jailcur");
    started = false;
}

void standard_screen::init_cp_matrix()
{
    for(colour c = colour::min; c < colour::max; ++c)
        for(colour d = colour::min; d < colour::max; ++d)
        {
            int f = static_cast<int>(c);
            int b = static_cast<int>(d);
            cp[f][b] = current_cp;
            ++current_cp;

            /* Whilst init_pair() produces a return code, it functions
             * irrespective of this value. Thus, it will not be checked for
             * the time being.
             */
            init_pair(cp[f][b], f, b);
        }
}

WINDOW* standard_screen::create_window_list()
{
    util::set_attribute(standard_window, get_cp(text, bg) | A_BOLD );
    util::clear_screen(standard_window);
    util::add_str(title, standard_window, 0, 0);
    return standard_window;
}

