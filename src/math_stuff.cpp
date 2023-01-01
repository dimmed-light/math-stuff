#include "../lib/math_stuff.h"

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

unsigned int calculate_base_sum(
	std::vector<uint8_t> const& digits, 
	unsigned int b
) {
	unsigned int sum = 0; // number in base 10
	unsigned int p = 0; // power to which each digit is raised
	std::for_each(digits.begin(), digits.end(), 
		[&sum, &p, &b] (uint8_t d) {
			sum += d * std::pow(b, p);
			p++;
		}
	);
	return sum;
}

unsigned int tobase10(unsigned int n, unsigned int b) {
	if (b > 10) {
		return 0;
	} else if (b == 10) {
		return n;
	}

	std::vector<uint8_t> digits = split_into_digits(n);
	return calculate_base_sum(digits, b);
}

unsigned int tobase10(std::string_view n, unsigned int b) {
	std::vector<uint8_t> digits;
	std::transform(n.rbegin(), n.rend(), std::back_inserter(digits), 
		[] (char c) {
			if (c <= '9') {
				return (uint8_t) c - '0';
			}
			return (uint8_t) c - 'A' + 10;
		}
	);

	return calculate_base_sum(digits, b);
}

std::string tobase(unsigned int n, unsigned int b) {
	std::vector<uint8_t> digits = split_into_digits(n, b);
	std::string number;
	std::transform(
		digits.rbegin(), 
		digits.rend(), 
		std::back_inserter(number), 
		[] (uint8_t d) {
			if (d <= 9) {
				return (char) d + '0';
			}
			return (char) d + 'A' - 10;
		}
	);
	return number;
}

std::list<unsigned int> sieve_of_eratosthenes(unsigned int l) {
	std::list<unsigned int> numbers(l - 1);
	std::iota(numbers.begin(), numbers.end(), 2);

	for (auto it = numbers.begin(); it != numbers.end(); it++) {
		numbers.erase(
			std::remove_if(
				std::next(it), 
				numbers.end(), 
				[&it] (unsigned int n) {
					return n % *it == 0;
				}
			), 
			numbers.end()
		);
	}

	return numbers;
}

std::list<unsigned int> lucky_numbers(unsigned int l) {
	std::list<unsigned int> numbers(l);
	std::iota(numbers.begin(), numbers.end(), 1);

	// get rid of all even numbers
	numbers.erase(
		std::remove_if(
			numbers.begin(),
			numbers.end(),
			[] (unsigned int n) {
				return n % 2 == 0;
			}
		),
		numbers.end()
	);

	// remove every n-th number
	for (auto it = numbers.begin(); it != numbers.end(); it++) {
		unsigned int c = 0;
		numbers.erase(
			std::remove_if(
				numbers.begin(), 
				numbers.end(), 
				[&it, &c] (unsigned int n) {
					if (*it != 1 && c == *it - 1) {
						c = 0;
						return true;
					}
					c++;
					return false;
				}
			), 
			numbers.end()
		);
	}

	return numbers;
}

std::vector<unsigned int> trial_division(unsigned int n) {
	std::vector<unsigned int> factors;
	unsigned int factor = 2;
	while (n > 1) {
		if (n % factor == 0) {
			n /= factor;
			factors.push_back(factor);
		} else {
			factor++;
		}
	}
	return factors;
}

bool is_prime(unsigned int n) {
	return trial_division(n).size() == 1;
}

bool is_harshad(unsigned int n, unsigned int b) {
	std::vector<uint8_t> digits = split_into_digits(n, b);
	return n % std::accumulate(digits.begin(), digits.end(), 0) == 0; 
}

bool is_perfect(unsigned int n) {
	unsigned int sum = 0;
	unsigned int d = 1;
	while (d < n) {
		if (n % d == 0) {
			sum += d;
		}
		d++;
	}
	return sum == n;
}

unsigned int gcd(unsigned int a, unsigned int b) {
	while (a != 0 && b != 0) {
		if (a > b) {
			a %= b;
		} else if (b > a) {
			b %= a; 
		} else {
			return a;
		}
	}

	if (a) {
		return a;
	}
	return b;
}

unsigned int count_primes(unsigned int a, unsigned int b) {
	if (a == 1) {
		return b / std::log(b);
	}
	return (b / std::log(b)) - (a / std::log(a));
}

}
