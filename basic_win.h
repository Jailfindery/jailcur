#ifndef JAILCUR_BASIC_WIN_H_INCLUDED
#define JAILCUR_BASIC_WIN_H_INCLUDED

#include <list>
#include <string>

#include <curses.h>

#include "colour.h"
#include "data.h"
#include "standard.h"

#include "win_interface.h"

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
        : win_interface(t, h, w, f, b, s)
    {}

  private:
    virtual const int get_list_size() { return 2; }
    virtual abstract_data::ptr get_input();
    virtual list<WINDOW*> create_win_ptr(int y, int x);
};

}

#endif /* JAILCUR_BASIC_WIN_H_INCLUDED */

