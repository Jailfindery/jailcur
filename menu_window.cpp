/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#include <list>
#include <string>

#include <curses.h>

#include "menu_window.h"
#include "util.h"

using namespace std;
using namespace jailcur;

/* Calls delete_menu_objects() to deallocate memory resources. */
menu_window::~menu_window()
{
    try
    {
        delete_menu_objects();
    }
    catch(...) { throw; }    // Rethrow exceptions
}

/* Use basic_cwindow::create_window_list() to create the window list and initialize
 * the windows. If the item list or menu is non-null, they are deleted. The menu
 * associated with the window and sub window, allowing it to be displayed.
 */
list<WINDOW*> menu_window::create_window_list(int y, int x)
{
    list<WINDOW*> L;

    try
    {
        L = basic_cwindow::create_window_list(y, x);

        // In order to edit the windows, they must be removed from the list.
        WINDOW* sub_window = L.back();
        L.pop_back();
        WINDOW* content_window = L.back();
        L.pop_back();

        delete_menu_objects();

        // Create item_list
        item_list = new ITEM*[size() + 1];
        for(int i = 0; i < size(); ++i)
           item_list[i] = util::new_item(menu_options[i]);
        item_list[size()] = static_cast<ITEM*>(nullptr);

        // Create and configure menu
        menu = util::new_menu(item_list);
        util::set_menu_base(menu, content_window);
        util::set_menu_sub_window(menu, sub_window);
        util::set_menu_selected_colour(menu, highlight_text, highlight_bg);
        util::set_menu_unselected_colour(menu, get_text_colour(),
                                         get_bg_colour() );
        util::set_menu_marker(menu, marker);
        util::post_menu(menu);

        // Put windows back in list
        L.push_back(content_window);
        L.push_back(sub_window);
    }
    catch(...) { throw; }   // Rethrow exceptions
    return L;
}

/* Prompts the user to select a menu entry. Returns an integer inside of an
 * abstract_data::ptr.
 */
abstract_data::ptr menu_window::get_input()
{
    abstract_data::ptr P;

    try
    {
        int ch; 
        int choice = -1; 

        while(choice == -1) 
        {   
            /* Refresh windows */
            render.refresh_top();   // The menu is guaranteed to be on top

            /* Get and interpret input */
            ch = getch();
            switch(ch)
            {   
              case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
              case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
              case 10:  /* Enter key */
                choice = item_index(current_item(menu) );
                break;
              default:
                break;
            }   
        }

        /* Wrapping data in polymorphic type */
        window_data<int>* D = new window_data<int>(choice);
        P = abstract_data::ptr(dynamic_cast<abstract_data*>(D) );
        if(P.get() == nullptr)
            throw runtime_error("jailcur::menu_window::get_input(): "
                                "Bad cast from window_data<int>* to abstract_data*");
    }
    catch(...) { throw; } // Rethrow exception

    return P;
}

/* Deallocates resources associated with item_list and menu using the provided
 * curses functions. If these members are non-null, they are deallocated;
 * otherwise, they have not been used and, thus, need not be freed.
 */
void menu_window::delete_menu_objects()
{
    try
    {
        if(menu != nullptr)
        {
            util::unpost_menu(menu);
            util::delete_menu(menu);
            menu = nullptr;
        }

        if(item_list != nullptr)
        {
            for(int i = 0; i < size(); ++i)
                util::delete_item(item_list[i]);
            delete[] item_list;
            item_list = nullptr;
        }
    }
    catch(...) { throw; }    // Rethrow exceptions
}

