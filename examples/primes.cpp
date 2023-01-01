#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <array>

#include "../lib/math_stuff.h"

template<typename Iterator>
void print(Iterator const& first, Iterator const& last) {
    std::cout << "[ ";
    std::for_each(first, last, [] (auto const& item) {
        std::cout << item << ' ';
    });
    std::cout << "]\n";
}

int main() {
    std::list<unsigned int> primes = mst::sieve_of_eratosthenes(200);
    print(primes.begin(), primes.end());

    std::vector<unsigned int> factors = mst::trial_division(12);
    print(factors.begin(), factors.end());

    constexpr std::array<unsigned int, 4> numbers { 12, 13, 23, 56 };
    
    std::for_each(numbers.begin(), numbers.end(), [] (unsigned int n) {
        std::cout << "Is " << n << " a prime?: " << 
            (mst::is_prime(n) ? "Yes\n" : "No\n");
    });

    return 0;
}

