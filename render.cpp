#include <stdexcept>

#include <curses.h>

#include "render.h"
#include "standard.h"

using namespace jailcur;

/* Gets the WINDOW* from the description of standard and draws it on the
 * screen. Throws std::runtime_error on error.
 */
void render::refresh_standard()
{
    WINDOW* stdw = standard::create_win_ptr();
    int rc1 = touchwin(stdw);
    int rc2 = wrefresh(stdw);
    if(rc1 || rc2)
        throw runtime_error("jailcur: render::refresh_standard(): Unable to refresh.");
}

