#include "bit_sequence.h"

//#define DEBUG_APPEND
//#define DEBUG_BUILD

class DecimalInfinite {
public:
	DecimalInfinite();
	DecimalInfinite(const DecimalInfinite &other);
	DecimalInfinite(std::string literal);

	std::string str();

	std::string dumpBits();
private:
	BitSequence _bits;

	static const char LogTable256[256];
	static inline unsigned int log2(unsigned int v);
};
