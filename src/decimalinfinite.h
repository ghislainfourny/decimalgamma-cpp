#include "bit_sequence.h"

//#define DEBUG_APPEND
//#define DEBUG_BUILD

class DecimalInfinite {
public:
	DecimalInfinite() {
		_bits.appendBits(0b10, 2);
	}

	DecimalInfinite(const DecimalInfinite &other) {
		_bits = other._bits;
	}

	DecimalInfinite(int i) {
	}

	DecimalInfinite(std::string literal);

	std::string dumpBits();

private:
	BitSequence _bits;

	static const char LogTable256[256];

	static unsigned int log2(unsigned int v) {
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

};
