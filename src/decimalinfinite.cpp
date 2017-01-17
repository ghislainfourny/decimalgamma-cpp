#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "decimalinfinite.h"

#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n

const char DecimalInfinite::LogTable256[256] = { -1, 0, 1, 1, 2, 2, 2, 2, 3, 3,
		3, 3, 3, 3, 3, 3, LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6), LT(7),
		LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7) };

//#define DEBUG_BUILD

DecimalInfinite::DecimalInfinite(std::string literal) {
	bool hasSign = false;
	bool sign = true;
	bool period = false;
	bool digit = false;
	std::vector<int> digits;
	int exponent = 0;
	for (int p = 0; p < literal.length(); ++p) {
		char c = literal.at(p);

		if (c == '0') {
			if (digit) {
				digits.push_back(c - '0');
				if (!period) {
					++exponent;
				}
				continue;
			} else {
				if (period) {
					--exponent;
				}
				continue;
			}
		}

		if (c >= '1' && c <= '9') {
			digits.push_back(c - '0');
			if (!period) {
				++exponent;
			}
			digit = true;
			continue;
		}

		if (c == '-') {
			if (p != 0) {
				std::cout << "Error: illegal literal." << std::endl;
				exit(0);
			}
			sign = false;
			hasSign = true;
		}

		if (c == '.') {
			if (period) {
				std::cout << "Error: illegal literal." << std::endl;
				exit(0);
			}
			if(digits.size() == 0)
			{
				--exponent;
			}
			period = true;
		}
	}

	int i = digits.size() - 1;
	while(i != -1 && digits.at(i) == 0)
	{
		digits.pop_back();
		--i;
	}

#ifdef DEBUG_BUILD
	std::cout << "Sign:" << (sign?"+":"-") << std::endl;
	std::cout << "Literal:" << literal << std::endl;
	std::cout << "Digits:" << std::endl;
	for (int i = 0; i < digits.size(); ++i) {
		std::cout << digits[i] << std::endl;
	}
	std::cout << "Exponent " << exponent << std::endl;
#endif
	int abs_offset_exponent = abs(exponent) + 2;
  int exponent_sign = (exponent >= 0);
	bool invert_exponent_encoding = (sign != exponent_sign);
#ifdef DEBUG_BUILD
	std::cout << "Exponent sign " << (exponent_sign?"+":"-") << std::endl;
	std::cout << "Absolute offset exponent " << abs_offset_exponent << std::endl;
	std::cout << "Invert exponent encoding " << (invert_exponent_encoding?"yes":"no") << std::endl;
#endif
	unsigned int le = log2(abs_offset_exponent) + 1;
#ifdef DEBUG_BUILD
	std::cout << "Log2 exponent: " << le << std::endl;
#endif

	if (sign) {
		_bits.appendBits(0b10, 2);
	} else {
		_bits.appendBits(0b00, 2);
	}
	if(digits.size() == 0)
	{
		return;
	}

unsigned int xor_ones = (1 << le) - 1;
	if(invert_exponent_encoding)
	{
#ifdef DEBUG_BUILD
	std::cout << "Append: " << (1 << le) - 2 << std::endl;
#endif
		_bits.appendBits(((1 << le) - 2) xor xor_ones, le);
		xor_ones = (1 << (le - 1)) - 1;
#ifdef DEBUG_BUILD
	std::cout << "Append: " << abs_offset_exponent - (1 << (le - 1)) << std::endl;
#endif
		_bits.appendBits((abs_offset_exponent - (1 << (le - 1))) xor xor_ones, le - 1);
	}
	else {
#ifdef DEBUG_BUILD
	std::cout << "Append: " << (1 << le) - 2 << std::endl;
#endif
		_bits.appendBits((1 << le) - 2, le);
#ifdef DEBUG_BUILD
	std::cout << "Append: " << abs_offset_exponent - (1 << (le - 1)) << std::endl;
#endif
		_bits.appendBits(abs_offset_exponent - (1 << (le - 1)), le - 1);
	}

	int first = digits.at(0);
	if (hasSign) {
		first = literal.at(1) - '0';
	}
	if (!sign) {
		first = 10 - first;
	}
#ifdef DEBUG_BUILD
	std::cout << "Write first: " << first << std::endl;
#endif
	_bits.appendBits(first, 4);

	int next = 1;
	while (next < digits.size()) {
		int a = 0, b = 0, c = 0;
		a = digits.at(next++);
		if (next < digits.size()) {
			b = digits.at(next++);
		}
		if (next < digits.size()) {
			c = digits.at(next++);
		}
		unsigned int towrite = 100 * a + 10 * b + c;
		if (!sign) {
			towrite = 999 - towrite;
		}
#ifdef DEBUG_BUILD
	std::cout << "Write declet: " << towrite << std::endl;
#endif
		_bits.appendBits(towrite, 10);
	}
}

std::string DecimalInfinite::dumpBits() {
	return _bits.toString();
}
