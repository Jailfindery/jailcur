#include <curses.h>
#include <menu.h>

#include "jailcur_except.h"

using namespace std;

/* Converts the error code of a curses function to what it represents. */
const char* jailcur::util::window_error::what_error()
{
    switch(error_code)
    {
      case OK:
        return "OK";
        break;
      case ERR:
        return "Error";
        break;
    }
    return "Unknown error";
}

/* Converts the error code of a curses function to what it represents. */
const char* jailcur::util::menu_error::what_error()
{
    switch(error_code)
    {
      case E_OK:
        return "OK";
        break;
      case E_BAD_ARGUMENT:
        return "Bad argument";
        break;
      case E_BAD_STATE:
        return "Bad state";
        break;
      case E_NO_MATCH:
        return "Character failed to match";
        break;
      case E_NO_ROOM:
        return "Menu is too large for its window";
        break;
      case E_NOT_CONNECTED:
        return "Menu is not connected to a window";
        break;
      case E_NOT_POSTED:
        return "Menu has not been posted";
        break;
      case E_NOT_SELECTABLE:
        return "Menu item not selectable";
        break;
      case E_POSTED:
        return "Menu is already posted";
        break;
      case E_REQUEST_DENIED:
        return "Menu driver could not process request";
        break;
      case E_SYSTEM_ERROR:
        return "System error";
        break;
      case E_UNKNOWN_COMMAND:
        return "Menu driver encountered an unknown request";
    }
    return "Unknown error";
}

