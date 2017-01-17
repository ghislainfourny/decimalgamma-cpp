#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "bit_sequence.h"

//#define DEBUG_APPEND
//#define DEBUG_BUILD

void BitSequence::appendBits(uint i, int n) {
	if ((i & ((-1) << n)) > 0) {
		std::cout << "Invalid parameters (" << n << " bits expected) :"
				<< std::bitset<BUFFER_SIZE>(i) << std::endl;
		exit(0);
	}
#ifdef DEBUG_APPEND
	std::cout << "Before : " << dumpBits() << std::endl;
	std::cout << "Writing " << n << " - " << std::bitset<BUFFER_SIZE>(i) << std::endl;
#endif
	int buffer0 = (_next - 1) / BUFFER_SIZE;
	int offset = _next % BUFFER_SIZE;
	int buffer1 = buffer0 + 1;
	bool needs_buffer_1 = (_next + n - 1) / BUFFER_SIZE
			> (_next - 1) / BUFFER_SIZE;
#ifdef DEBUG_APPEND
	std::cout << "Next: " << _next << std::endl;
	std::cout << "Buffer0: " << buffer0 << std::endl;
	std::cout << "Buffer1: " << buffer1 << std::endl;
	std::cout << "Offset: " << offset << std::endl;
	std::cout << "Needs second buffer: " << needs_buffer_1 << std::endl;
#endif

	int size = _raw_bits.size();
#ifdef DEBUG_APPEND
	std::cout << "Size: " << size << std::endl;
#endif
	while (_next + n > size * BUFFER_SIZE) {
		_raw_bits.push_back(0);
		size = _raw_bits.size();
	}

	int shift = BUFFER_SIZE - n - offset;
#ifdef DEBUG_APPEND
	std::cout << "Shift: " << shift << std::endl;
#endif
	if (!needs_buffer_1) {
		if (shift < 0) {
			std::cout << "Error: negative shift!" << std::endl;
			exit(0);
		}
#ifdef DEBUG_APPEND
		std::cout << "shift " << shift << std::endl;
		std::cout << "OR-ing " << std::bitset<BUFFER_SIZE>((i << shift)) << std::endl;
#endif
		_raw_bits[buffer0] |= i << shift;
		_next += n;
#ifdef DEBUG_APPEND
		std::cout << "After : " << _next << " - " << dumpBits() << std::endl;
#endif
	} else {
		shift = 0 - shift;
		if (offset > 0) {
#ifdef DEBUG_APPEND
			std::cout << "Shift: " << shift << std::endl;
#endif
			if (shift < 0) {
				std::cout << "Error: negative shift! " << shift << std::endl;
				exit(0);
			}
#ifdef DEBUG_APPEND
			std::cout << "shift " << shift << std::endl;
			std::cout << "OR-ing " << std::bitset<BUFFER_SIZE>((i >> shift)) << std::endl;
#endif
			_raw_bits[buffer0] |= i >> shift;
#ifdef DEBUG_APPEND
			std::cout << "After : " << _next << " - " << dumpBits() << std::endl;
#endif
		}
		shift = BUFFER_SIZE - shift;
#ifdef DEBUG_APPEND
		std::cout << "shift " << shift << std::endl;
		std::cout << "OR-ing " << std::bitset<BUFFER_SIZE>((i << shift)) << std::endl;
#endif
		_raw_bits[buffer1] |= i << shift;
		_next += n;
#ifdef DEBUG_APPEND
		std::cout << "After : " << _next << " - " << dumpBits() << std::endl;
#endif
	}
}

std::string BitSequence::toString() {
	std::stringstream output;
	for (int i = 0; i < _raw_bits.size(); ++i) {
		output << std::bitset<BUFFER_SIZE>(_raw_bits[i]);
	}
	return output.str();
}
