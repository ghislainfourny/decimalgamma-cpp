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
	// Default constructors;
	Decimal();
	Decimal(const Decimal &other) = default;

	// Conversion constructors
	explicit Decimal(const char* const literal);
	explicit Decimal(const std::string& literal) : Decimal(literal.c_str()) {}
	explicit Decimal(const float& literal); // TODO
	explicit Decimal(const double& literal); // TODO

	operator float() const; // TODO
	operator double() const; // TODO

	// Assignment operators
	Decimal& operator=(const Decimal& other) = default;
	Decimal& operator=(const char * const other) { return *this = Decimal(other); }
	Decimal& operator=(const std::string& other) { return *this = Decimal(other); }
	Decimal& operator=(const float other) { return *this = Decimal(other); }
	Decimal& operator=(const double other) { return *this = Decimal(other); }

	// Increment operators
	Decimal& operator+=(Decimal other); // TODO
	Decimal& operator+=(const char * const other); // TODO
	Decimal& operator+=(const std::string& other); // TODO
	Decimal& operator+=(const float other); // TODO
	Decimal& operator+=(const double other); // TODO

	// To/from decimal composition
	Decimal(const DecimalDecomposition& decomposition);
	void getDecomposition(DecimalDecomposition *decomposition);

	/*
	 * Outputs (decodes) the decimal as a literal.
	 */
	std::string str();


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
