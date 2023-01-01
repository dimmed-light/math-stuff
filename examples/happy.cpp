#include <iostream>

#include "../lib/math_stuff.h"

char const* yes_or_no(bool);

int main() {
    std::cout << "Is 4 a happy number?: " << yes_or_no(mst::is_happy(4));
	std::cout << "Is 19 a happy number?: " << yes_or_no(mst::is_happy(19));
	std::cout << "Is (347, 6) a happy number?: " << 
		yes_or_no(mst::is_happy(347, 6));

    return 0;
}

char const* yes_or_no(bool result) {
	return (result ? "Yes.\n" : "No.\n"); 
}
