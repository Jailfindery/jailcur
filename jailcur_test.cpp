#include <iostream>
#include <stdexcept>

#include "jailcur.h"

/*
#include "basic_message_win.h"
#include "basic_win.h"
#include "colour.h"
#include "data.h"
#include "message_win.h"
#include "render.h"
#include "standard.h"
#include "util.h"
*/

using namespace jailcur;

int main()
{
    try
    {
        standard.set_title("jailcur Test Program");
        standard.start();

        basic_win my_win1("", 15, 60, colour::magenta, colour::green, colour::magenta);
        basic_win my_win2("Hello, world!", 15, 60, colour::blue, colour::yellow, colour::red);

        message_win my_win3("That's alright...");
        my_win3.set_title("User-Friendly Message Window");
        my_win3.set_height(15);
        my_win3.set_width(60);
        my_win3.set_message("This is a test message. ;)");

        basic_message_win my_win4;
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

        int n = 0;
        int d = 11;
        progress_win my_p(n, d);
        my_p.set_title("Progress Test");
        my_p.set_height(15);
        my_p.set_width(71);
        my_p.set_message("Press a button to increase progress.");

        util::get_ch();
        render.put_top(&my_win1, 2, 2);
        util::get_ch();
        render.put_top(&my_win2, 5, 5);
        util::get_ch();
        render.put_top(&my_win4, 11, 11);
        util::get_ch();
        render.put_top(&my_win3, 8, 8);
        util::get_ch();
        render.put_top(&my_p, 4, 4);

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
        while(render.size() > 0)
        {
            abstract_data::ptr P = render.get_top_input();
            bool D = data_cast<bool>(P);
            if(!D) throw runtime_error("False return from window");

            render.pull_top();
        }

        util::get_ch();
        standard.stop();
    }
    catch(...)
    {
        standard.stop();
        throw;  /* Let the default handler do its thing. */
    }

}

