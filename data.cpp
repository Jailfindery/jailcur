#include <memory>
#include <stdexcept>

#include "data.h"

using namespace std;
using namespace jailcur;

/* Retrieves the specific data of type T from P and returns it. If data of type
 * T is not stored in P, runtime_error is thrown.
 */
template<typename T>
T data::get(abstract_data::ptr P)
{
    win_data<T>* D = dynamic_cast<win_data<T>*>(P.get() );
    if(D == nullptr)
        throw runtime_error("jailcur: data::get(): Bad cast");
    return D->get();
}

