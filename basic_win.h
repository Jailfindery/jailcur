#ifndef JAILCUR_BASIC_WIN_H_INCLUDED
#define JAILCUR_BASIC_WIN_H_INCLUDED

#include <list>
#include <string>

#include <curses.h>

#include "colour.h"
#include "data.h"
#include "standard.h"

namespace jailcur
{

class render;   /* Forward declaration */

class basic_win : public win_interface
{
  friend class render;

  public:
    basic_win(string t,
              int h = standard::get_maxy() - 4,
              int w = standard::get_maxx() - 4,
              colour f = colour::black,
              colour b = colour::white,
              colour s = colour::black)
        : title(t), height(h), width(w), text(f), bg(b), shadow(s)
    {}

  private:
    /* TODO: Define these member functions */
    virtual abstract_data::ptr get_input();
    virtual list<WINDOW*> create_win_ptr(int y, int x);
};

}

#endif /* JAILCUR_BASIC_WIN_H_INCLUDED */

