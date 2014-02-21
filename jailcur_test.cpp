/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <stdexcept>

#include "jailcur.h"

/*
#include "basic_message_window.h"
#include "basic_window.h"
#include "colour.h"
#include "data.h"
#include "message_window.h"
#include "render.h"
#include "standard.h"
#include "util.h"
*/

using namespace jailcur;

int main()
{
    int choice;     // Required for testing jailcur::menu_window

    try
    {
        standard.set_title("jailcur Test Program");
        standard.start();

        basic_window my_win1("", 15, 60, colour::magenta, colour::green, colour::magenta);
        basic_window my_win2("Hello, world!", 15, 60, colour::yellow, colour::black, colour::red);

        message_window my_win3("That's alright...");
        my_win3.set_title("User-Friendly Message Window");
        my_win3.set_height(15);
        my_win3.set_width(60);
        my_win3.set_message("This is a test message. ;)");

        basic_message_window my_win4;
        my_win4.set_title("Message Test");
        my_win4.set_message("Here is a list of things:\n"
                            "\t* Thoughts strewn across your mind.\n"
                            "\t* A time when you were not alone.\n"
                            "\t* A feeling of doubt and meaninglessness.\n\n"
                            "This is a simple list; "
                            "do not think too deeply about it.\n"
                           );

        my_win4.set_height(15);
        my_win4.set_width(60);

        menu_window my_menu;
        my_menu.set_height(20);
        my_menu.set_width(65);
        my_menu.set_title("Menu Test");
        my_menu.set_message("Please select an entry: ");
        my_menu.add_item("Item Zero");
        my_menu.add_item("Item One");
        my_menu.add_item("Item Two");
        my_menu.set_highlight_bg_colour(colour::green);

        int n = 0;
        int d = 5;
        progress_window my_p(n, d);
        my_p.set_title("Progress Test");
        my_p.set_height(15);
        my_p.set_width(71);
        my_p.set_message("Press a button to increase progress.");

        // Constructor is protected, so an object can not be created.
        //basic_cwindow my_cwin;

        util::get_ch();
        render.put_top(my_menu, 15, 15);
        util::get_ch();
        render.put_top(my_win1, 2, 2);
        util::get_ch();
        render.put_top(my_win2, 5, 5);
        util::get_ch();
        render.put_top(my_win4, 11, 11);
        util::get_ch();
        render.put_top(my_win3, 8, 8);
        util::get_ch();
        render.put_top(my_p, 4, 4);

        util::get_ch();
        standard.engage_disco_mode();

        /* Testing the progress win */
        while(!my_p.is_complete() )
        {
            util::get_ch();
            ++n;
            render.rebuild_top();
        }
        util::get_ch();
        ++n;
        render.rebuild_top();

        /* Removing windows */
        while(render.size() > 1)    // Leave the menu
        {
            abstract_data::ptr P = render.get_top_input();
            bool D = data_cast<bool>(P);
            if(!D) throw runtime_error("False return from window");

            render.pull_top();
        }

        /* Testing the menu win */
        auto P = render.get_top_input();
        choice = data_cast<int>(P);
        render.pull_top();

        standard.stop();
    }
    catch(util::general_error& e)
    {
        standard.stop();
        cout << "Caught an exception of type jailcur::util::error" << endl
             << "what(): " << e.what() << endl
             << "Error code: " << e.get_error_code() << " (" << e.what_error()
                << ")" << endl;
        return -1;
    }
    catch(...)
    {
        standard.stop();
        throw;  /* Let the default handler do its thing. */
    }

    cout << "You selected: " << choice << endl;
}

