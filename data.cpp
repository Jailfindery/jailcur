#include <stdexcept>

#include "data.h"

using namespace std;
using namespace jailcur;

/* Retrieves the data value of type T stored in P. If P does not store data of
 * type T, runtime_error is thrown.
 */
template<typename T>
T jailcur::data_cast(abstract_data::ptr& P)
{
    win_data<T>* data_P = dynamic_cast<win_data<T>*>(P.get() );
    if(data_P == nullptr)
        throw runtime_error("jailcur::data_cast(): Bad cast");
    return data_P->get();
}

