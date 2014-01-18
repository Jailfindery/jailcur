#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

#include <curses.h>

#include "render.h"
#include "standard.h"
#include "util.h"
#include "win_interface.h"

using namespace std;
using namespace jailcur;

/* Static members for render */
vector<pair<int, int> > render::coordinate_stack {};
vector<WINDOW*> render::on_screen_stack {};
vector<win_interface*> render::desc_stack {};

/* Empties both the desc_stack and on_screen_stack objects, and deletes all
 * WINDOW*.
 */
void render::empty()
{
    try
    {
        while(!on_screen_stack.empty() )
        {
            util::delete_win(on_screen_stack.back() );
            on_screen_stack.pop_back();
        }

        while(!desc_stack.empty() )
            desc_stack.pop_back();

        while(!coordinate_stack.empty() )
            coordinate_stack.pop_back();
    }
    catch(...) { throw; }
}

/* TODO: Recreates all WINDOW* objects and refreshes them. */
void render::rebuild_all()
{
    try
    {
        throw runtime_error("jailcur::render::rebuild_all(): "
                            "Member not implemented.");
    }
    catch(...) { throw; }
}

/* Recreates the WINDOW* objects corresponding with the top win_interface*
 * object and refreshes them. Uses coordinate_stack to get the coordinate for
 * the WINDOW*.
 */
void render::rebuild_top()
{
    try
    {
        win_interface* top_win = desc_stack.back();
        int list_size = top_win->get_list_size();

        for(int i = 0; i < list_size; ++i)
        {
            util::delete_win(on_screen_stack.back() );
            on_screen_stack.pop_back();
        }

        pair<int, int> top_coor = coordinate_stack.back();
        list<WINDOW*> top_list = top_win->create_win_ptr(top_coor.first,
                                                         top_coor.second);
        while(!top_list.empty() )
        {
            on_screen_stack.push_back(top_list.front() );
            refresh_top();
            top_list.pop_front();
        }
    }
    catch(...) { throw; }
}

/* Refreshes all WINDOW* on the on_screen_stack. */
void render::refresh_all()
{
    try
    {
        refresh_standard();

        vector<WINDOW*>::iterator iter;
        for(iter = on_screen_stack.begin(); iter < on_screen_stack.end(); ++iter)
            util::refresh_win(*iter);
    }
    catch(...) { throw; }
}

/* Gets the WINDOW* from the description of standard and draws it on the
 * screen.
 */
void render::refresh_standard()
{
    try
    {
        WINDOW* stdw = standard.create_win_ptr();
        util::refresh_win(stdw);
    }
    catch(...) { throw; }
}

/* Refreshes the WINDOW* at the top (i.e. back) of the on_screen_stack. */
void render::refresh_top()
{
    try
    {
        util::refresh_win(on_screen_stack.back() );
    }
    catch(...) { throw; }
}

/* Removes the top entry in desc_stack and its corresponding elements on
 * on_screen_stack and coordinate_stack. Then it refreshes all elements of
 * the on_screen_stack.
 */
void render::pull_top()
{
    try
    {
        if(desc_stack.empty() )
            throw runtime_error("jailcur::render::pull_top(): "
                                "Empty window stack.");

        win_interface* temp = desc_stack.back();
        desc_stack.pop_back();
        coordinate_stack.pop_back();

        for(int i = 0; i < temp->get_list_size(); ++i)
            on_screen_stack.pop_back();

        refresh_all();

    }
    catch(...) { throw; }
}

/* Places n_win on the top of desc_stack and places its coordinates on
 * coordinate_stack and builds the corresponding WINDOW*, placing them on
 * the on_screen_stack. The WINDOW* are then rendered on the screen. Throws
 * runtime_error if no windows are on the stack.
 */
void render::put_top(win_interface* n_win, int y, int x)
{
    try
    {
        list<WINDOW*> my_list = n_win->create_win_ptr(y, x);
        desc_stack.push_back(n_win);
        coordinate_stack.push_back(make_pair(y, x) );

        while(!my_list.empty() )
        {
            on_screen_stack.push_back(my_list.front() );
            refresh_top();
            my_list.pop_front();
        }
    }
    catch(...) { throw; }
}

