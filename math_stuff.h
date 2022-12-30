#pragma once

#include <stack>
#include <cstdint>
#include <set>
#include <cmath>

namespace mst {

std::stack<uint8_t> split_into_digits(unsigned int, unsigned int = 10);
unsigned int pdif(unsigned int, unsigned int = 2, unsigned int = 10);
bool is_happy(unsigned int, unsigned int = 10);

}