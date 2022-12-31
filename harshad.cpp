#include <iostream>
#include <array>

#include "math_stuff.h"

using number_and_base = std::pair<unsigned int, unsigned int>;

int main() {
    std::array<number_and_base, 5> numbers {{
        { 9, 10 },
        { 21, 10 },
        { mst::tobase10("A1", 12), 12 },
        { mst::tobase10("10A", 12), 12 },
        { 154, 10 }
    }};

    std::for_each(numbers.begin(), numbers.end(), [] (auto const& p) {
        auto& [n, b] = p;
        std::cout << "Is (" << n << ", " << b << ") a harshad number?: " <<
            (mst::is_harshad(n, b) ? "Yes.\n" : "No.\n");
    });

    return 0;
}
