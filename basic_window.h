/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JAILCUR_BASIC_WINDOW_H_INCLUDED
#define JAILCUR_BASIC_WINDOW_H_INCLUDED

#include <list>
#include <string>

#include <curses.h>

#include "colour.h"
#include "data.h"
#include "standard.h"

#include "window_interface.h"

namespace jailcur
{

class render;   /* Forward declaration */

class basic_window : public window_interface
{
  friend class render;

  public:
    basic_window(string t = "",
              int h = standard.get_maxy() - 4,
              int w = standard.get_maxx() - 4,
              colour f = colour::black,
              colour b = colour::white,
              colour s = colour::black)
        : bg_colour(b), shadow_colour(s), text_colour(f), height(h), width(w),
          title(t)
    {}
    colour get_bg_colour() { return bg_colour; }
    colour get_shadow_colour() { return shadow_colour; }
    colour get_text_colour() { return text_colour; }
    void set_bg_colour(colour c) { bg_colour = c; }
    void set_shadow_colour(colour c) { shadow_colour = c; }
    void set_text_colour(colour c) { text_colour = c; }

    string get_title() { return title; }
    void set_title(string str) { title = str; }

    int get_height() { return height; }
    int get_width() { return width; }
    void set_height(int h) { height = h; }
    void set_width(int w) { width = w; }

  protected:
    virtual list<WINDOW*> create_window_ptr(int y, int x);

  private:
    colour bg_colour, shadow_colour, text_colour;
    int height, width;
    string title;

    virtual const int get_list_size() { return 2; }
    virtual abstract_data::ptr get_input();
};

}

#endif /* JAILCUR_BASIC_WINDOW_H_INCLUDED */

