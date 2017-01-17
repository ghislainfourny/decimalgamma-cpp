#include "bit_sequence.h"
#include <iostream>

bool bit_sequence_test() {
	BitSequence s;
	s.appendBits(0b10, 2);
	std::cout << s.toString() << std::endl;
	s.appendBits(0b1111111111110, 13);
	std::cout << s.toString() << std::endl;
	s.appendBits(0b1111111111110, 13);
	std::cout << s.toString() << std::endl;
	s.appendBits(0b1111111111110, 13);
	std::cout << s.toString() << std::endl;
	s.appendBits(0b1111111111110, 13);
	std::cout << s.toString() << std::endl;
	s.appendBits(0b1111111111110, 13);
	std::cout << s.toString() << std::endl;
	s.appendBits(0b1111111111110, 13);
	std::cout << s.toString() << std::endl;
	s.appendBits(0b1111111111110, 13);
	std::cout << s.toString() << std::endl;
	s.appendBits(0b110, 3);
	std::cout << s.toString() << std::endl;
	s.appendBits(0b1111111111111111111111111111110, 31);
	std::cout << s.toString() << std::endl;
	s.appendBits(0b0, 1);
	std::cout << s.toString() << std::endl;
	s.appendBits(0b1, 1);
	std::cout << s.toString() << std::endl;
	return true;
}
