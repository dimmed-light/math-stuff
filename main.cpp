#include <iostream>

#include "math_stuff.h"

int main() {
	std::cout << "Is 4 a happy number?: " << 
		(mst::is_happy(4) ? "Yes.\n" : "No.\n");
	std::cout << "Is 19 a happy number?: " << 
		(mst::is_happy(19) ? "Yes.\n" : "No.\n");

	

	return 0;
}


