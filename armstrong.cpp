#include <iostream>
#include <array>
#include <algorithm>

#include "math_stuff.h"

using number_and_base = std::pair<unsigned int, unsigned int>;

char const* yes_or_no(bool);

int main() {
	std::array<number_and_base, 10> numbers {{ 
		{ 99, 10 }, 
		{ 153 , 10 }, 
		{ 1634, 10 },

		// I give an octal number as input and I'm trying to find if this number
		// is an armstrong number in base 8 (second argument)
		{ 064, 8 }, 

		// I give a binary number as input and I'm trying to find if this number
		// is an armstrong number in base 10 (second argument)
		{ 0b101110010, 10 },

		// I give an decimal number as input and I'm trying to find if this 
		// number is an armstrong number in base 5 (second argument)
		{ 13, 5 },

		// Same as above, but I give the number in octal base
		{ 015, 5 },

		// Now, I give the same number in base 5 (or do I?) and I'm trying to 
		// find if this number is an armstrong number in base 5 (second 
		// argument). This will NOT work!
		// { 23, 5 },

		// To compensate for this, you can use mst::tobase10 in order to convert
		// any number that has base < 10 to decimal
		{ mst::tobase10(23, 5), 5 },

		// There is an overloaded version that accepts numbers in base > 10 
		// using strings
		{ mst::tobase10("A83", 12), 12 },

		{ 0x99A, 16 }
	}};

	std::for_each(numbers.begin(), numbers.end(), [](auto const& p){
		auto const& [n, b] = p;
		// make 10tobase()
		std::cout << "Is (" << n << ", " << b << ") an armstrong number?: " << 
			yes_or_no(mst::is_armstrong(n, b));
	});

	return 0;
}

char const* yes_or_no(bool result) {
	return (result ? "Yes.\n" : "No.\n"); 
}
