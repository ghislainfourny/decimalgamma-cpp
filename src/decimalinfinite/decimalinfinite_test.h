#include "decimalinfinite.h"

#include <iostream>

#include "util/test.h"

class DecimalInfiniteTest {
public:
	DecimalInfiniteTest() {}
  void run();
private:
  void test(std::string literal, std::string expected) {
  	decimalinfinite::Decimal d(literal);
  	// Tests that the expected encoding is calculated.
  	Test::assertStringEqual(expected, d.dumpBits());
  	// Tests that decoding against leads to the original literal.
  	Test::assertStringEqual(literal, d.str());
  };
};
