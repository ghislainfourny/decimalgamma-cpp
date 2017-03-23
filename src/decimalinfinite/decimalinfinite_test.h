#include "decimalinfinite.h"

#include <iostream>

#include "util/test.h"

class DecimalInfiniteTest
{
  public:
    DecimalInfiniteTest() {}
    void run();

  private:
    void test(std::string literal, std::string expected);
    void testComparison();
    void testAddition();
};
