#include <iostream>

#include "standard.h"
#include "render.h"
#include "util.h"

using namespace std;
using namespace jailcur;

int main()
{
    standard::set_title("Hello, world!");
    standard::start();
    util::get_ch();
    standard::stop();
}

