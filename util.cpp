#include <stdexcept>
#include <string>

#include <curses.h>

#include "util.h"

using namespace std;
using namespace jailcur;

/* Gets a character from the user. */
int util::get_ch()
{
    return getch();
}

/* Add a string str to window win at position (y,x). On error,
 * std::runtime_error is thrown.
 */
void util::add_str(string str, WINDOW* win, int y, int x)
{
   int rc = mvwaddstr(win, y, x, str.c_str() );
   if(rc)
        throw runtime_error("jailcur: Unable to add string to window");
}

/* Uses curses functions to get the height and width of win and clears win of
 * any content, thus making the entire window the colour of bg. On failure,
 * std::runtime_error is thrown.
 */
void util::clear_screen(WINDOW* win)
{
    int y, x;
    getmaxyx(win, y, x);

    for(int i = 0; i < y; ++i)
        for(int k = 0; k < x; ++k)
            mvwaddch(win, i, k, ' ');
            /* Whilst mvwaddch() appears to produce a return code, it does not
             * appear to truthfully state how the operation went. Thus, rc-
             * checking for this function is not being done.
             */
}

/* Set video attributes of a window (e.g. give colour to a window). Throws
 * std::runtime_error on failure.
 */
void util::set_attribute(WINDOW* win, int attrib)
{
    int rc = wattrset(win, attrib);
    if(rc)
        throw runtime_error("jailcur: util::set_attribute: Unable to set attribute(s)");
}

