#include <iostream>
#include "header.h"
using namespace NR;

int main() {
    Settings settin;
    do {
        settin.dialog();

    } while (settin.analysis());

    return 0;
}
