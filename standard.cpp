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
bool standard::started = false;
cp_matrix standard::cp {};
int standard::current_cp = 0;
colour standard::bg = colour::cyan;
colour standard::text = colour::white;
int standard::maxy = -1;
int standard::maxx = -1;
string standard::title {};
WINDOW* standard::standard_win = nullptr;

/* Gets the colour pair from the table generated at start up. As a result,
 * standard::start() must be run in order to have it available. If it has not
 * been called, std::runtime_error is thrown.
 *
 * The value from the table is processed through COLOR_PAIR so the result can
 * be immediately used as a video attribute.
 */
int standard::get_cp(colour f, colour b)
{
    if(!is_started() )
        throw runtime_error("jailcur: standard: get_cp(): jailcur not started");
    return COLOR_PAIR(cp[f][b]);
}

/* Set the background colour to c. If c is not in [colour::min, colour::max),
 * std::runtime_error is thrown.
 */
void standard::set_bg_colour(colour c)
{
    if(!(c >= colour::min && c < colour::max) )
        throw runtime_error("jailcur: standard: set_bg_colour(): out of range");
    bg = c;
}

/* Set the text colour to c. If c is not in [colour::min, colour::max),
 * std::runtime_error is thrown.
 */
void standard::set_text_colour(colour c)
{
    if(!(c >= colour::min && c < colour::max) )
        throw runtime_error("jailcur: standard: set_text_colour(): out of range");
    text = c;
}

/* Starts the curses environment and sets various preferrable attributes. If
 * startup fails, std::runtime_error is thrown.
 */
void standard::start()
{
    standard_win = initscr();   /* Start curses environment.            */
    if(standard_win == nullptr)
        throw runtime_error("jailcur: Unable to start jailcur");
    started = true;

    timeout(-1);                /* Use blocking when reading input.     */
    start_color();              /* Enables use of colour.               */
    cbreak();                   /* Does not process special characters? */
    noecho();                   /* Typed characters do not appear.      */
    keypad(standard_win, true); /* Enables getting arrow key presses.   */
    curs_set(0);                /* Disables the cursor.                 */

    /* TODO: Configure cp's on demand. */
    init_cp_matrix();           /* Initializes colour all colour pairs. */

    render::refresh_standard(); /* Draws standard on screen. */
}

/* Stops the curses environment. Throws std::runtime_error on error. */
void standard::stop()
{
    int rc = endwin();
    if(rc)
        throw runtime_error("jailcur: Unable to stop jailcur; force stopping?");
    started = false;
}

void standard::init_cp_matrix()
{
    for(colour c = colour::min; c < colour::max; ++c)
        for(colour d = colour::min; d < colour::max; ++d)
        {
            int f = static_cast<int>(c);
            int b = static_cast<int>(d);
            cp[f][b] = current_cp;
            ++current_cp;

            /* TESTME: May not return an rc. */
            int rc = init_pair(cp[f][b], f, b);
            /*
            if(rc)
                throw runtime_error("jailcur: Unable to initialize colour pairs");
                */
        }
}

WINDOW* standard::create_win_ptr()
{
    util::set_attribute(standard_win, get_cp(text, bg) | A_BOLD );
    util::clear_screen(standard_win);
    util::add_str(title, standard_win, 0, 0);
    return standard_win;
}

