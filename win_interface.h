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

/* Acts as an interface for all window objects. Allows any type of window to be
 * rendered by render.
 */
class win_interface
{
  friend class render;

  public:
    win_interface() {}

  private:
    /* Returns the number of elements returned from create_win_ptr(). */
    virtual const int get_list_size() = 0;

    virtual abstract_data::ptr get_input() = 0;
    virtual list<WINDOW*> create_win_ptr(int y, int x) = 0;
};

}

#endif /* JAILCUR_WIN_INTERFACE_H_INCLUDED */

