#include <iostream>
#include <stack>
#include <cstdint>
#include <set>
#include <cmath>

std::stack<uint8_t> split_into_digits(unsigned int, unsigned int = 10);
unsigned int pdif(unsigned int, unsigned int = 2, unsigned int = 10);
bool is_happy(unsigned int, unsigned int = 10);

int main() {
	std::cout << (is_happy(19) ? "Yes.\n" : "No.\n");
	return 0;
}

std::stack<uint8_t> split_into_digits(unsigned int n, unsigned int b) {
	std::stack<uint8_t> digits;
	while (n > 0) {
		digits.push(n % b);
		n /= b;
	}
	return digits;
} 

unsigned int pdif(unsigned int n, unsigned int p, unsigned int b) {
	unsigned int sum = 0;
	std::stack<uint8_t> digits = split_into_digits(n, b);
	while (!digits.empty()) {
		sum += std::pow(digits.top(), p);
		digits.pop();
	}
	return sum;
}

bool is_happy(unsigned int n, unsigned int b) {
	std::set<unsigned int> checked_numbers;
	std::stack<uint8_t> digits;
	while (n > 1 && !checked_numbers.contains(n)) {
		checked_numbers.insert(n);
		n = pdif(n, 2, b);
	}
	return n == 1;
}
