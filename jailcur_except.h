/* jailcur: An object-oriented wrapper for curses
 * Copyright (C) 2014 Joshua Schell <joshua.g.schell@gmail.com>
 *
 * This library is licensed under the GNU General Public License version
 * 3. You should have received a copy of it along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JAILCUR_JAILCUR_EXCEPT_H_INCLUDED
#define JAILCUR_JAILCUR_EXCEPT_H_INCLUDED

#include <stdexcept>
#include <string>

using namespace std;

namespace jailcur
{

namespace util {

/* Parent class for window_error and menu_error. It simplifies error handling
 * and child inplementations.
 */
class general_error : public runtime_error
{
  public:
    general_error(const char* w, int e) : runtime_error(w), error_code(e) {}
    general_error(string& w, int e) : runtime_error(w.c_str() ), error_code(e) {}
    virtual const char* what_error() = 0;
    int get_error_code() { return error_code; }
  protected:
    int error_code;
};

/* Handles general errors caused by an error in a util function dealing with
 * windows. It contains the error code produced by a curses function and the
 * ability to interpret it.
 */
class window_error : public general_error
{
  public:
    window_error(const char* w, int e) : general_error(w, e) {}
    window_error(string& w, int e) : general_error(w, e) {}
    const char* what_error();
};

/* Handles general errors caused by an error in a util function dealing with
 * menus. It contains the error code produced by a curses function and the
 * ability to interpret it.
 */
class menu_error : public general_error
{
  public:
    menu_error(const char* w, int e) : general_error(w, e) {}
    menu_error(string& w, int e) : general_error(w, e) {}
    const char* what_error();
};

} // namespace util

} // namespace jailcur

#endif /* JAILCUR_JAILCUR_EXCEPT_H_INCLUDED */

