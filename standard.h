#ifndef JAILCUR_STANDARD_H_INCLUDED
#define JAILCUR_STANDARD_H_INCLUDED

#include <string>

#include <curses.h>

#include "colour.h"

using namespace std;

namespace jailcur {

class render;   /* Forward reference */

/* A simple coordinate implementation to ease Cartesian point things. */
struct coordinate
{
    coordinate() : x(0), y(0) {}
    coordinate(int _x, int _y) : x(_x), y(_y) {}
    int x, y;
};

/* Static class to manage everything related to curses' stdscr and other
 * global curses data.
 */
class standard
{
  friend class render;

  public:
    static bool is_started() { return started; }

    static int get_cp(colour f, colour b);

    /* TODO: Should get_max*() check if jailcur has been started? */
    static int get_maxx() { return maxx; }
    static int get_maxy() { return maxy; }
    static coordinate get_maxyx() { return coordinate(maxx, maxy); }
    /* Note: get_maxyx() is so named because it is similar to what the
     * equilivalent curses function is named.
     */

    static colour get_bg_colour(colour c) { return bg; }
    static colour get_text_colour(colour c) { return text; }
    static void set_bg_colour(colour c);
    static void set_text_colour(colour c);

    static string get_title() { return title; }
    static void set_title(string str) { title = str; }

    static void start();
    static void stop();

  private:
    static bool started;

    static cp_matrix cp;
    static colour bg;
    static colour text;
    static int current_cp;      /* Used for colour pair allocation */
    static void init_cp_matrix();

    static int maxy, maxx;      /* FIXME: Required? */

    static string title;

    static WINDOW* standard_win;

    static WINDOW* create_win_ptr();
};

}

#endif /* JAILCUR_STANDARD_H_INCLUDED */

