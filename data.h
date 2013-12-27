#ifndef JAILCUR_DATA_H_INCLUDED
#define JAILCUR_DATA_H_INCLUDED

#include <memory>

using namespace std;

namespace jailcur
{

/* Base class to allow for polymorphic behaviour for windows returning user
 * input.
 */
class abstract_data
{
  public:
    using ptr = unique_ptr<abstract_data>;
    abstract_data() {}
    virtual ~abstract_data() {}
};

/* Concrete version of abstract_data that stores user input from windows. */
template<typename T>
class win_data : public abstract_data
{
  public:
    using ptr = unique_ptr<win_data<T> >;   /* FIXME: Is this necessary? */
    win_data(T x) : input(x) {}
    virtual ~win_data() {}
    T get() { return input; }
  private:
    T input;
};

namespace data
{

T get(abstract_data::ptr P);

}

}

#endif /* JAILCUR_DATA_H_INCLUDED */

