#pragma once

#include <iostream>

#include <vector>
#include <list>
#include <set>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <string_view>
#include <string>

// m(ath) st(uff)
namespace mst {

// First parameter: Accepts a number in any C++-supported base (decimal, binary,
//                  octal, hexadecimal)
// Second parameter: The base you want to find the digits (default: 10).
// Effectively, this can convert any C++-supported base number to any
// other base. However, passing any number that isn't in any C++-supported base
// will not work. This applies to other functions that use this function.
std::vector<uint8_t> split_into_digits(unsigned int, unsigned int = 10);

// Perfect digital invariant function. See first comment.
unsigned int pdif(unsigned int, unsigned int = 2, unsigned int = 10);

// Checks if a number is b-happy or b-sad/unhappy. See first comment.
bool is_happy(unsigned int, unsigned int = 10);

// Checks if a number is an Armstrong number (also known as narcissistic number)
// See first comment.
bool is_armstrong(unsigned int, unsigned int = 10);

// Used by tobase10()
unsigned int calculate_base_sum(std::vector<uint8_t> const&, unsigned int);

// Converts any number in base < 10 to decimal
unsigned int tobase10(unsigned int, unsigned int);

// Converts any number in base > 10 to decimal
unsigned int tobase10(std::string_view, unsigned int);

// Converts base-10 numbers to other bases
std::string tobase(unsigned int, unsigned int);

// Finds all prime numbers up to a certain limit (l). Definitely not the most 
// optimized implementation but it was fun to make ::D
std::list<unsigned int> sieve_of_eratosthenes(unsigned int);

// Finds all lucky numbers up to a certain limit (l). 
std::list<unsigned int> lucky_numbers(unsigned int);

// Proceeds to find factors of a given number
std::vector<unsigned int> trial_division(unsigned int);

bool is_prime(unsigned int);

// Checks if a number is a harshad number in a given base
bool is_harshad(unsigned int, unsigned int = 10);

// Checks if a number is perfect
bool is_perfect(unsigned int);

// Greatest common divisor
// Euclid's algorithm, non-recursive
unsigned int gcd(unsigned int, unsigned int);

// Gretest commond divisor, but it accepts more than 2 numbers
template<class Iterator>
typename 
    std::enable_if_t<
        std::is_same_v<
            typename Iterator::value_type, 
            unsigned int
        >, 
        unsigned int
    >
gcd(Iterator first, Iterator last) {
    unsigned int result = *first;
	for (Iterator it = std::next(first); it != last; it++) {
        result = gcd(result, *it);
    }
    return result;
}

}