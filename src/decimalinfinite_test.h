#include "decimalinfinite.h"

#include <iostream>

class DecimalInfiniteTest {
public:
	DecimalInfiniteTest() {}
  void run();
private:
  static bool assertEqual(std::string, std::string);
  void test(std::string literal, std::string expected) {
  	decimalinfinite::Decimal d(literal);
  	// Tests that the expected encoding is calculated.
  	assertEqual(d.dumpBits(), expected);
  	// Tests that decoding against leads to the original literal.
  	assertEqual(literal, d.str());
  };
};
