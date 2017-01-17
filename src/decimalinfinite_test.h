#include "decimalinfinite.h"

class DecimalInfiniteTest {
public:
	DecimalInfiniteTest() {}
  void run();
private:
  void test(std::string literal, std::string expected) {
  	DecimalInfinite d(literal);
  	std::string actual = d.dumpBits();
  	if(actual == expected) {
  		std::cout << literal << " : " << "[PASSED]" << std::endl;
  	} else {
  		std::cout << literal << " : " << "[FAIL]" << std::endl;
  		std::cout << "Actual:"  << actual << std::endl;
  		std::cout << "Expected: " << expected << std::endl;
  	}
  };
};
