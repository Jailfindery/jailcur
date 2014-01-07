#ifndef JAILCUR_UTILITY_H_INCLUDED
#define JAILCUR_UTILITY_H_INCLUDED

#include <string>

#include <curses.h>

using namespace std;

namespace jailcur {

/* util acts as a static class where curses operations are wrapped so they do
 * not need to be invoked manually.
 */
namespace util
{

int get_ch();
void add_ch(char c, WINDOW* win, int y, int x);
void add_str(string str, WINDOW* win, int y, int x);
void clear_screen(WINDOW* win);
void delete_win(WINDOW* win);
void draw_border(WINDOW* win);
void draw_title(WINDOW* win, string str);
void refresh_win(WINDOW* win);
void set_attribute(WINDOW* win, int attrib);
WINDOW* new_win_ptr(int h, int w, int y, int x);

}

}

#endif /* JAILCUR_UTILITY_H_INCLUDED */

