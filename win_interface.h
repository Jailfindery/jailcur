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
    win_interface(string t, int h, int w, colour f, colour b, colour s)
        : title(t), height(h), width(w), text_colour(f),
          bg_colour(b), shadow_colour(s)
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

  private:
    colour bg_colour, shadow_colour, text_colour;
    int height, width;
    string title;

    /* Returns the number of elements returned from create_win_ptr(). */
    virtual const int get_list_size() = 0;

    virtual abstract_data::ptr get_input() = 0;
    virtual list<WINDOW*> create_win_ptr(int y, int x) = 0;
};

}

#endif /* JAILCUR_WIN_INTERFACE_H_INCLUDED */

