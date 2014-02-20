#ifndef JAILCUR_MENU_WINDOW_H_INCLUDED
#define JAILCUR_MENU_WINDOW_H_INCLUDED

#include <list>
#include <string>
#include <vector>

#include <curses.h>
#include <menu.h>

#include "basic_cwindow.h"
#include "colour.h"
#include "data.h"
#include "standard.h"

using namespace std;

namespace jailcur
{

class menu_window : public basic_cwindow
{
  public:
    menu_window(string m = "", 
             string t = "", 
             int h = standard.get_maxy() - 4,
             int w = standard.get_maxx() - 4,
             colour f = colour::black,
             colour b = colour::white,
             colour s = colour::black)
        : basic_cwindow(m, t, h, w, f, b, s),
          highlight_bg(colour::red), highlight_text(colour::white),
          item_list(nullptr), menu(nullptr)
    {
        // marker can not be initialized nor assigned
        marker[0] = '*';
        marker[1] = ' ';
        marker[2] = '\n';
    }
    ~menu_window();

    char get_marker() { return marker[0]; }
    colour get_highlight_bg_colour() { return highlight_bg; }
    colour get_highlight_text_colour() { return highlight_text; }
    int size() { return menu_options.size(); }
    void add_item(string s) { menu_options.push_back(s); }
    void remove_item() { menu_options.pop_back(); }
    void set_highlight_bg_colour(colour c) { highlight_bg = c; }
    void set_highlight_text_colour(colour c) { highlight_text = c; }
    void set_marker(char c) { marker[0] = c; }
    void clear_list() { menu_options.clear(); }
  protected:
    virtual list<WINDOW*> create_window_ptr(int y, int x);
  private:
    char marker[3];
    colour highlight_bg;
    colour highlight_text;
    ITEM** item_list;
    MENU* menu;
    vector<string> menu_options;

    virtual abstract_data::ptr get_input();
    void delete_menu_objects();
};

}

#endif /* JAILCUR_MENU_WINDOW_H_INCLUDED */

