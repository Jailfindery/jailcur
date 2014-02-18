#ifndef JAILCUR_BASIC_CWIN_H_INCLUDED
#define JAILCUR_BASIC_CWIN_H_INCLUDED

#include <list>

#include <curses.h>

#include "basic_message_win.h"

using namespace std;

namespace jailcur
{

/* Contains a sub win embedded inside of a basic_message_win. It contains no
 * real functionality and is simply intended to be derived from.
 */
class basic_cwin : public basic_message_win
{
  protected:
    basic_cwin(string m = "", 
               string t = "", 
               int h = standard.get_maxy() - 4,
               int w = standard.get_maxx() - 4,
               colour f = colour::black,
               colour b = colour::white,
               colour s = colour::black)
        : basic_message_win(m, t, h, w, f, b, s)
    {}
    virtual list<WINDOW*> create_win_ptr(int y, int x);

  private:
    virtual const int get_list_size() { return 3; }
};

}

#endif /* JAILCUR_BASIC_CWIN_H_INCLUDED */

