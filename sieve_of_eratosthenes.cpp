#include <iostream>
#include <list>

#include "math_stuff.h"

void print(std::list<unsigned int> const&);

int main() {
    std::list<unsigned int> primes = mst::sieve_of_eratosthenes(200);
    print(primes);
    return 0;
}

void print(std::list<unsigned int> const& l) {
    std::cout << "[ ";
    for (auto const& n : l) {
        std::cout << n << ' ';
    }
    std::cout << "]\n";
}
