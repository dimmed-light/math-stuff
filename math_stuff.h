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

// m(ath) st(uff)
namespace mst {

// First parameter: Accepts a number in any C++-supported base (decimal, binary,
//                  octal, hexadecimal)
// Second parameter: The base you want to find the digits (default: 10).
// Effectively, this can convert any C++-supported base number to any
// other base. However, passing any number that isn't in any C++-supported base
// will not work. This applies to all other functions too.
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

// Finds all prime numbers up to a certain limit. Definitely not the most 
// optimized implementation but it was fun to make ::D
std::list<unsigned int> sieve_of_eratosthenes(unsigned int);

}