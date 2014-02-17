#ifndef JAILCUR_RENDER_H_INCLUDED
#define JAILCUR_RENDER_H_INCLUDED

#include <utility>
#include <vector>

#include "data.h"
#include "win_interface.h"

using namespace std;

namespace jailcur {

/* Responsible for taking window descriptions and drawing them on the
 * screen.
 *
 * Note that for stack objects, back is equilivalent to the top.
 */
class window_render
{
  public:
    window_render() {}

    static abstract_data::ptr get_top_input() { return get_top()->get_input(); }

    static int size() { return desc_stack.size(); }

    static void empty();

    static void rebuild_all();
    static void rebuild_top();

    static void refresh_all();
    static void refresh_standard();
    static void refresh_top();

    static void pull_top();
    static void put_top(win_interface* n_win, int y, int x);

    static win_interface* get_top() { return desc_stack.back(); }

  private:
    /* Stores the coordinates associated with each win_interface* object. The
     * first member is the y component and the second is the x.
     */
    static vector<pair<int, int> > coordinate_stack;
    static vector<WINDOW*> on_screen_stack;
    static vector<win_interface*> desc_stack;
};

static window_render render;

}

#endif /* JAILCUR_RENDER_H_INCLUDED */

