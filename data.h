#ifndef JAILCUR_DATA_H_INCLUDED
#define JAILCUR_DATA_H_INCLUDED

#include <memory>
#include <stdexcept>

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
    win_data(T x) : input(x) {}
    virtual ~win_data() {}
    T get() { return input; }
  private:
    T input;
};

/* Retrieves the data value of type T stored in P. If P does not store data of
 * type T, runtime_error is thrown.
 *
 * FIXME: Should be implemented in data.cpp, but this causes an undefined
 *        reference error.
 */
template<typename T>
T data_cast(abstract_data::ptr& P)
{
    win_data<T>* data_P = dynamic_cast<win_data<T>*>(P.get() );
    if(data_P == nullptr)
        throw runtime_error("jailcur::data_cast(): Bad cast");
    return data_P->get();
}

}

#endif /* JAILCUR_DATA_H_INCLUDED */

