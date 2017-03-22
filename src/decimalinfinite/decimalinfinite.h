#include "util/bit_sequence.h"

#include <string>

//#define DEBUG_APPEND
//#define DEBUG_BUILD

class DecimalDecomposition;

/*
 * Implements the DecimalInfinite encoding.
 */

namespace di
{
class decimal {
public:
	// Default constructors;
	decimal();
	decimal(const decimal &other) = default;

	// Conversion constructors
	explicit decimal(const char* const literal);
	explicit decimal(const std::string& literal) : decimal(literal.c_str()) {}
	// TODO: make faster by looking at bits directly.
	explicit decimal(const float& literal) : decimal(std::to_string(literal)) {}
	// TODO: make faster by looking at bits directly.
	explicit decimal(const double& literal) : decimal(std::to_string(literal)) {}

	operator float() const { return std::stof(str()); }; // TODO: make faster by looking at bits directly.
	operator double() const { return std::stod(str()); }; // TODO: make faster by looking at bits directly.
    std::string str() const;

	// Assignment operators
	decimal& operator=(const decimal& other) = default;
	decimal& operator=(const char * const other) { return *this = decimal(other); }
	decimal& operator=(const std::string& other) { return *this = decimal(other); }
	decimal& operator=(const float other) { return *this = decimal(other); }
	decimal& operator=(const double other) { return *this = decimal(other); }

	// Increment operators
	// TODO: make correct and precise.
	decimal& operator+=(decimal other) { return *this = decimal(double(*this) + double(other)); };
	// TODO: make faster.
	decimal& operator+=(const char * const other) { return *this += decimal(other); };
	// TODO: make faster.
	decimal& operator+=(const std::string& other) { return *this += decimal(other); };
	// TODO: make faster.
	decimal& operator+=(const float other) { return *this += decimal(other); };
	// TODO: make faster.
	decimal& operator+=(const double other) { return *this += decimal(other); };

	// To/from decimal composition
	decimal(const DecimalDecomposition& decomposition);
	void getDecomposition(DecimalDecomposition *decomposition) const;


	// TODO: equality, comparison operators

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
