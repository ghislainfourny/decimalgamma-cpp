#include "bit_sequence.h"

#include <bitset>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

//#define DEBUG_APPEND
//#define DEBUG_BUILD

void BitSequence::appendBits(uint i, int n) {
	if(n > 32)
	{
		std::cout << "Error: cannot write more than 32 bits at a time (" << n << " bits written." << std::endl;
	}
	if ((i & ((-1) << n)) > 0) {
		std::cout << "Invalid parameters (" << n << " bits expected) :"
				<< std::bitset<BUFFER_SIZE>(i) << std::endl;
		exit(0);
	}
#ifdef DEBUG_APPEND
	std::cout << "Before : " << str() << std::endl;
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
		std::cout << "After : " << _next << " - " << str() << std::endl;
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
			std::cout << "After : " << _next << " - " << str() << std::endl;
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
		std::cout << "After : " << _next << " - " << str() << std::endl;
#endif
	}
}

std::string BitSequence::str() {
	std::stringstream output;
	for (int i = 0; i < _raw_bits.size(); ++i) {
		output << std::bitset<BUFFER_SIZE>(_raw_bits[i]);
	}
	return output.str().substr(0, _next);
}

unsigned int BitSequence::getBits(int i, int n) const
{
	if(n > 32)
	{
		std::cout << "Error: cannot read more than 32 bits at a time (" << n << " bits requested." << std::endl;
	}
#ifdef DEBUG_APPEND
	std::cout << "Get bits " << i << " " << n << std::endl;
#endif
	int buffer = i / BUFFER_SIZE;
	int position_in_buffer = i % BUFFER_SIZE;
  bool two_buffers = (position_in_buffer + n) > BUFFER_SIZE;
	int offset = - position_in_buffer + BUFFER_SIZE - n;
#ifdef DEBUG_APPEND
	std::cout << "Buffer: " << buffer << std::endl;
	std::cout << "position_in_buffer: " << position_in_buffer << std::endl;
	std::cout << "two_buffers: " << two_buffers << std::endl;
	std::cout << "offset: " << offset << std::endl;
#endif
	if(!two_buffers)
	{
		uint raw_bits = 0;
		if(buffer < _raw_bits.size())
		{
  		raw_bits = _raw_bits.at(buffer);
		}
		uint mask = (1 << (BUFFER_SIZE - position_in_buffer)) - 1;
		if(position_in_buffer == 0)
		{
			mask = -1;
		}
		uint raw_bits_masked = raw_bits & mask;
		uint raw_bits_offset = raw_bits_masked >> offset;
	#ifdef DEBUG_APPEND
		std::cout << "Raw bits: " << std::bitset<BUFFER_SIZE>(raw_bits) << std::endl;
		std::cout << "Mask: " << std::bitset<BUFFER_SIZE>(mask) << std::endl;
		std::cout << "Raw bits, masked " << std::bitset<BUFFER_SIZE>(raw_bits_masked) << std::endl;
		std::cout << "Raw bits, offset: " << std::bitset<BUFFER_SIZE>(raw_bits_offset) << std::endl;
	#endif
		return raw_bits_offset;
	} else {
		int buffer2 = buffer + 1;
		uint raw_bits = 0;
		if(buffer < _raw_bits.size())
		{
  		raw_bits = _raw_bits.at(buffer);
		}
		uint mask = (1 << (BUFFER_SIZE - position_in_buffer)) - 1;
		if(position_in_buffer == 0)
		{
			mask = -1;
		}
		uint raw_bits_masked = raw_bits & mask;
		uint raw_bits_offset = raw_bits_masked << -offset;
	#ifdef DEBUG_APPEND
		std::cout << "Raw bits: " << std::bitset<BUFFER_SIZE>(raw_bits) << std::endl;
		std::cout << "Mask: " << std::bitset<BUFFER_SIZE>(mask) << std::endl;
		std::cout << "Raw bits, masked " << std::bitset<BUFFER_SIZE>(raw_bits_masked) << std::endl;
		std::cout << "Raw bits, offset: " << std::bitset<BUFFER_SIZE>(raw_bits_offset) << std::endl;
		std::cout << "Raw bits, size: " << _raw_bits.size() << std::endl;
	#endif
		uint raw_bits2 = 0;
		if(buffer2 < _raw_bits.size())
		{
  		raw_bits2 = _raw_bits.at(buffer2);
		}
		int length2 = n - (BUFFER_SIZE - position_in_buffer);
		uint mask2 = (-1) - ((1 << (BUFFER_SIZE - length2)) - 1);
		uint raw_bits_masked2 = raw_bits2 & mask2;
		int offset2 = BUFFER_SIZE - length2;
		uint raw_bits_offset2 = raw_bits_masked2 >> offset2;
#ifdef DEBUG_APPEND
	std::cout << "Raw bits2: " << std::bitset<BUFFER_SIZE>(raw_bits2) << std::endl;
	std::cout << "Mask2: " << std::bitset<BUFFER_SIZE>(mask2) << std::endl;
	std::cout << "Raw bits, masked2: " << std::bitset<BUFFER_SIZE>(raw_bits_masked2) << std::endl;
	std::cout << "Raw bits, offset2: " << std::bitset<BUFFER_SIZE>(raw_bits_offset2) << std::endl;
#endif
		return raw_bits_offset | raw_bits_offset2;
	}
};

int BitSequence::length() const
{
	return _next;
}
