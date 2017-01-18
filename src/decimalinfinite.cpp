#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "decimalinfinite.h"
#include "decimal_decomposition.h"

#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n

const char DecimalInfinite::LogTable256[256] = { -1, 0, 1, 1, 2, 2, 2, 2, 3, 3,
		3, 3, 3, 3, 3, 3, LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6), LT(7),
		LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7) };

//#define DEBUG_BUILD

DecimalInfinite::DecimalInfinite() {
	_bits.appendBits(0b10, 2);
}

DecimalInfinite::DecimalInfinite(const DecimalInfinite &other) {
	_bits = other._bits;
}

DecimalInfinite::DecimalInfinite(std::string literal) {
	DecimalDecomposition decomposition(literal);

	int abs_offset_exponent = decomposition.getAbsoluteExponent() + 2;
	bool invert_exponent_encoding = (decomposition.isPositive() != decomposition.isExponentNonNegative());
#ifdef DEBUG_BUILD
	std::cout << "Exponent sign " << (exponent_sign?"+":"-") << std::endl;
	std::cout << "Absolute offset exponent " << abs_offset_exponent << std::endl;
	std::cout << "Invert exponent encoding " << (invert_exponent_encoding?"yes":"no") << std::endl;
#endif
	unsigned int le = log2(abs_offset_exponent) + 1;
#ifdef DEBUG_BUILD
	std::cout << "Log2 exponent: " << le << std::endl;
#endif

	if (decomposition.isPositive() or decomposition.isZero()) {
		_bits.appendBits(0b10, 2);
	} else {
		_bits.appendBits(0b00, 2);
	}
	if (decomposition.isZero()) {
		return;
	}

	unsigned int xor_ones = (1 << le) - 1;
	if (invert_exponent_encoding) {
#ifdef DEBUG_BUILD
		std::cout << "Append: " << (1 << le) - 2 << std::endl;
#endif
		_bits.appendBits(((1 << le) - 2) xor xor_ones, le);
		xor_ones = (1 << (le - 1)) - 1;
#ifdef DEBUG_BUILD
		std::cout << "Append: " << abs_offset_exponent - (1 << (le - 1)) << std::endl;
#endif
		_bits.appendBits((abs_offset_exponent - (1 << (le - 1))) xor xor_ones,
				le - 1);
	} else {
#ifdef DEBUG_BUILD
		std::cout << "Append: " << (1 << le) - 2 << std::endl;
#endif
		_bits.appendBits((1 << le) - 2, le);
#ifdef DEBUG_BUILD
		std::cout << "Append: " << abs_offset_exponent - (1 << (le - 1)) << std::endl;
#endif
		_bits.appendBits(abs_offset_exponent - (1 << (le - 1)), le - 1);
	}

	std::vector<int> digits;
	decomposition.getDigits(&digits);
	int first = digits.at(0);
	if (!decomposition.isPositive()) {
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
		if (!decomposition.isPositive()) {
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

unsigned int DecimalInfinite::log2(unsigned int v) {
	register unsigned int tt = v >> 24;

	if (tt) {
		return 24 + LogTable256[tt];
	}
	tt = v >> 16;
	if (tt) {
		return 16 + LogTable256[tt];
	}
	tt = v >> 8;
	if (tt) {
		return 8 + LogTable256[tt];
	}
	return LogTable256[v];
}

