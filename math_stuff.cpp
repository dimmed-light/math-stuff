#include "math_stuff.h"

namespace mst {

std::vector<uint8_t> split_into_digits(unsigned int n, unsigned int b) {
	std::vector<uint8_t> digits;
	while (n > 0) {
		digits.push_back(n % b);
		n /= b;
	}
	return digits;
} 

unsigned int pdif(unsigned int n, unsigned int p, unsigned int b) {
	unsigned int sum = 0;
	std::vector<uint8_t> digits = split_into_digits(n, b);
	std::for_each(digits.begin(), digits.end(), [&sum, p] (uint8_t const& d) {
		sum += std::pow(d, p);
	});
	return sum;
}

bool is_happy(unsigned int n, unsigned int b) {
	std::set<unsigned int> checked_numbers;
	while (n > 1 && !checked_numbers.contains(n)) {
		checked_numbers.insert(n);
		n = pdif(n, 2, b);
	}
	return n == 1;
}

bool is_armstrong(unsigned int n, unsigned int b) {
	return n == pdif(n, split_into_digits(n, b).size(), b);
}

unsigned int tobase10(unsigned int n, unsigned int b) {
	if (b > 10) {
		return 0;
	} else if (b == 10) {
		return n;
	}

	std::vector<uint8_t> digits = split_into_digits(n);
	unsigned int sum = 0; // number in base 10
	unsigned int p = 0; // power to which each digit is raised
	std::for_each(digits.begin(), digits.end(), 
		[&sum, &p, &b] (uint8_t const& d) {
			sum += d * std::pow(b, p);
			p++;
		}
	);
	return sum;
}

unsigned int tobase10(std::string_view n, unsigned int b) {
	std::vector<uint8_t> digits;
	std::transform(n.begin(), n.end(), std::back_inserter(digits), 
		[] (char const& c) {
			if (c <= '9') {
				return (uint8_t) c - '0';
			}
			return (uint8_t) c - 'A' + 10;
		}
	);

	unsigned int sum = 0;
	unsigned int p = digits.size() - 1;
	std::for_each(digits.begin(), digits.end(), 
		[&sum, &p, &b] (uint8_t const& d) {
			sum += d * std::pow(b, p);
			p--;
		}
	);

	return sum;
}

}