#include <iostream>

#include "math_stuff.h"

int main() {

    std::cout << "Is 6 a perfect number?: " << 
        (mst::is_perfect(6) ? "Yes.\n" : "No.\n");

    std::cout << "Is 33550336 a perfect number?: " << 
        (mst::is_perfect(33550336) ? "Yes.\n" : "No.\n");

    return 0;
}
