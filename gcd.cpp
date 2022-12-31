#include <iostream>

#include "math_stuff.h"

int main() {

    std::cout << mst::gcd(42, 56) << '\n'
              << mst::gcd(48, 18) << '\n'
              << mst::gcd(49, 17) << '\n';

    std::vector<unsigned int> numbers { 48, 18, 20 };

    std::cout << mst::gcd(numbers.begin(), numbers.end()) << '\n';

    return 0;
}
