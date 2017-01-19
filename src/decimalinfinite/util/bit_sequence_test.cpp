#include "bit_sequence_test.h"

#include "bit_sequence.h"

#include <iostream>

void BitSequenceTest::run() {
	BitSequence s;
	s.appendBits(0b10, 2);
	assertEqual("10000000000000000000000000000000", s.toString());
	assertIntEqual(1, s.getBits(0, 1));
	assertIntEqual(0b10, s.getBits(0, 2));
	assertIntEqual(0b100, s.getBits(0, 3));
	assertIntEqual(0, s.getBits(1, 1));
	assertIntEqual(0, s.getBits(1, 2));
	assertIntEqual(0, s.getBits(1, 3));
	assertIntEqual(0, s.getBits(1, 32));
	s.appendBits(0b1111111111110, 13);
	assertEqual("10111111111111000000000000000000", s.toString());
	assertIntEqual(0b101111111111110, s.getBits(0, 15));
	assertIntEqual(0b011111111111100, s.getBits(1, 15));
	s.appendBits(0b1111111111110, 13);
	assertEqual("10111111111111011111111111100000", s.toString());
	assertIntEqual(0b1011111111111101111111111110, s.getBits(0, 28));
	assertIntEqual(0b10111111111111011111111111100000, s.getBits(0, 32));
	s.appendBits(0b1111111111110, 13);
	assertEqual("1011111111111101111111111110111111111111000000000000000000000000", s.toString());
	assertIntEqual(0b1011111111111101111111111110, s.getBits(0, 28));
	assertIntEqual(0b10111111111111011111111111101111, s.getBits(0, 32));
	assertIntEqual(0b1111, s.getBits(28, 4));
	assertIntEqual(0b1111, s.getBits(29, 4));
	s.appendBits(0b1111111111110, 13);
	assertEqual("1011111111111101111111111110111111111111011111111111100000000000", s.toString());
	s.appendBits(0b1111111111110, 13);
	assertEqual("101111111111110111111111111011111111111101111111111110111111111111000000000000000000000000000000", s.toString());
	s.appendBits(0b1111111111110, 13);
	assertEqual("101111111111110111111111111011111111111101111111111110111111111111011111111111100000000000000000", s.toString());
	s.appendBits(0b1111111111110, 13);
	assertEqual("101111111111110111111111111011111111111101111111111110111111111111011111111111101111111111110000", s.toString());
	s.appendBits(0b110, 3);
	assertEqual("101111111111110111111111111011111111111101111111111110111111111111011111111111101111111111110110", s.toString());
	s.appendBits(0b1111111111111111111111111111110, 31);
	assertEqual("10111111111111011111111111101111111111110111111111111011111111111101111111111110111111111111011011111111111111111111111111111100", s.toString());
	s.appendBits(0b0, 1);
	assertEqual("10111111111111011111111111101111111111110111111111111011111111111101111111111110111111111111011011111111111111111111111111111100", s.toString());
	s.appendBits(0b1, 1);
	assertEqual("1011111111111101111111111110111111111111011111111111101111111111110111111111111011111111111101101111111111111111111111111111110010000000000000000000000000000000", s.toString());
}



bool BitSequenceTest::assertEqual(bool expected, bool actual) {
	if (actual == expected) {
		std::cout << "[PASSED]" << std::endl;
		return true;
	} else {
		std::cout << "[FAIL]" << std::endl;
		std::cout << "Actual:" << actual << std::endl;
		std::cout << "Expected: " << expected << std::endl;
		return false;
	}
}

bool BitSequenceTest::assertIntEqual(int expected, int actual) {
	if (actual == expected) {
		std::cout << "[PASSED]" << std::endl;
		return true;
	} else {
		std::cout << "[FAIL]" << std::endl;
		std::cout << "Actual:" << actual << std::endl;
		std::cout << "Expected: " << expected << std::endl;
		return false;
	}
}

bool BitSequenceTest::assertEqual(std::string expected, std::string actual) {
	if (actual == expected) {
		std::cout << "[PASSED]" << std::endl;
		return true;
	} else {
		std::cout << "[FAIL]" << std::endl;
		std::cout << "Actual:" << actual << std::endl;
		std::cout << "Expected: " << expected << std::endl;
		return false;
	}
}
