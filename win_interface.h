#ifndef JAILCUR_WIN_INTERFACE_H_INCLUDED
#define JAILCUR_WIN_INTERFACE_H_INCLUDED

#include <list>
#include <string>

#include <curses.h>

#include "colour.h"
#include "data.h"

using namespace std;

namespace jailcur
{

class render;   /* Forward declaration */

/* Acts as an interface for all window objects. */
class win_interface
{
  friend class render;

  public:
    colour get_bg_colour() { return bg; }
    colour get_shadow_colour() { return shadow; }
    colour get_text_colour() { return text; }
    void set_bg_colour(colour c) { bg = c; }
    void set_shadow_colour(colour c) { shadow = c; }
    void set_text_colour(colour c) { text = c; }

    string get_title() { return title; }
    void set_title(string str) { title = str; }

    int get_height() { return height; }
    int get_width() { return width; }
    void set_height(int h) { height = h; }
    void set_width(int w) { width = w; }

  private:
    colour bg, shadow, text;
    int height, width;
    string title;

    virtual abstract_data::ptr get_input() = 0;
    virtual list<WINDOW*> create_win_ptr(int y, int x) = 0;
};

}

#endif /* JAILCUR_WIN_INTERFACE_H_INCLUDED */

