#include <iostream>
#include <array>

#include "math_stuff.h"

using number_and_base = std::pair<unsigned int, unsigned int>;

void print_harshads(unsigned int, unsigned int = 10);

int main() {
    std::array<number_and_base, 6> numbers {{
        { 9, 10 },
        { 21, 10 },
        { mst::tobase10("A1", 12), 12 },

        // While it's true that (10A, 12) == (154, 10),
        // the number in question is still checked whether it is harshad or not
        // in base 12 (second argument) 
        { mst::tobase10("10A", 12), 12 },

        // Same line, written without mst::tobase10(). A more detailed 
        // explanation on why this happens is given in armstrong.cpp and in
        // math_stuff.h
        { 154, 12 },

        // (154, 10) is not harshad
        { 154, 10 }
    }};

    std::for_each(numbers.begin(), numbers.end(), [] (auto const& p) {
        auto const& [n, b] = p;
        std::cout << "Is (" << mst::tobase(n, b) << ", " << b << 
        ") a harshad number?: " << (mst::is_harshad(n, b) ? "Yes.\n" : "No.\n");
    });

    print_harshads(mst::tobase10("201", 12), 12);
    print_harshads(201, 10);

    return 0;
}

void print_harshads(unsigned int l, unsigned int b) {
    std::cout << "[ ";
    for (unsigned int n = 1; n < l; n++) {
        if (mst::is_harshad(n, b)) {
            std::cout << mst::tobase(n, b) << ' ';
        }
    }
    std::cout << "]\n";
}
