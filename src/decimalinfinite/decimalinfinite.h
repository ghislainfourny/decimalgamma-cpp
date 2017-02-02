#include "util/bit_sequence.h"

//#define DEBUG_APPEND
//#define DEBUG_BUILD

class DecimalDecomposition;

/*
 * Implements the DecimalInfinite encoding.
 */

namespace decimalinfinite
{
class Decimal {
public:
	/*
	 * Constructs zero.
	 */
	Decimal();
	/*
	 * Copies a decimal.
	 */
	Decimal(const Decimal &other);
	/*
	 * Creates (encodes) a decimal from a literal of the form dddddd.dddddd or -dddddd.dddddd.
	 */
	Decimal(std::string literal);
	/*
	 * Creates (encodes) a decimal from a decomposition.
	 */
	Decimal(const DecimalDecomposition& decomposition);

	/*
	 * Outputs (decodes) the decimal as a literal.
	 */
	std::string str();

	/*
	 * Outputs (decodes) the decimal as a literal.
	 */
	void getDecomposition(DecimalDecomposition *decomposition);

	/*
	 * For curious people: outputs the actual encoding as a string of 0s and 1s.
	 */
	std::string dumpBits();
private:
	// The internal encoding
	BitSequence _bits;

	void init(const DecimalDecomposition& decomposition);

	// This is used for speed-up (computation of log2 in constant time).
	static const char LogTable256[256];
	static inline unsigned int log2(unsigned int v);
};
}
