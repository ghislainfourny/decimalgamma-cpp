#include "test.h"

#include <iostream>

bool Test::assertBoolEqual(bool expected, bool actual) {
	if (actual == expected) {
		std::cout << "[PASSED]" << std::endl;
		return true;
	} else {
		std::cout << "[FAIL]" << std::endl;
		std::cout << "Actual:   " << actual << std::endl;
		std::cout << "Expected: " << expected << std::endl;
		return false;
	}
}

bool Test::assertIntEqual(int expected, int actual) {
	if (actual == expected) {
		std::cout << "[PASSED]" << std::endl;
		return true;
	} else {
		std::cout << "[FAIL]" << std::endl;
		std::cout << "Actual:   " << actual << std::endl;
		std::cout << "Expected: " << expected << std::endl;
		return false;
	}
}

bool Test::assertStringEqual(std::string expected, std::string actual) {
	if (actual == expected) {
		std::cout << "[PASSED]" << std::endl;
		return true;
	} else {
		std::cout << "[FAIL]" << std::endl;
		std::cout << "Actual:   " << actual << std::endl;
		std::cout << "Expected: " << expected << std::endl;
		return false;
	}
}
