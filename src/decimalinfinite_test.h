#include "decimalinfinite.h"

#include <iostream>

class DecimalInfiniteTest {
public:
	DecimalInfiniteTest() {}
  void run();
private:
  static bool assertEqual(std::string, std::string);
  void test(std::string literal, std::string expected) {
  	DecimalInfinite d(literal);
  	assertEqual(d.dumpBits(), expected);
  	assertEqual(literal, d.str());
  };
};
