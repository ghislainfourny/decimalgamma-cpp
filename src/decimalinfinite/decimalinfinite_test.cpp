#include "decimalinfinite_test.h"

#include <iostream>
using namespace std;
using namespace di;

void DecimalInfiniteTest::run() {
    decimal d;
    Test::assertStringEqual("0", d.str());

	test("-123456789", "0000011011001101111110101101100000001101110");
	test("-1000", "00001101001");
	test("-100", "00001111001");
	test("-10", "000101001");
	test("-9", "000110001");
	test("-8", "000110010");
	test("-7", "000110011");
	test("-6", "000110100");
	test("-5", "000110101");
	test("-4", "000110110");
	test("-3", "000110111");
	test("-2", "000111000");
	test("-1", "000111001");
	test("0", "10");
	test("0.02", "10001110010");
	test("0.2", "100100010");
	test("1", "101000001");
	test("2", "101000010");
	test("3", "101000011");
	test("4", "101000100");
	test("5", "101000101");
	test("6", "101000110");
	test("7", "101000111");
	test("8", "101001000");
	test("9", "101001001");
	test("10", "101010001");
	test("11", "1010100010001100100");
	test("20", "101010010");
	test("200", "10110000010");
	test("2000", "10110010010");
	test("20000", "10110100010");
	test("200000", "10110110010");
	test("2000000", "1011100000010");
	test("20000000", "1011100010010");
	test("123456789", "1011100100001001110101010001101111101111010");

	testComparison();
}

void DecimalInfiniteTest::test(std::string literal, std::string expected) {
  decimal d(literal);
  // Tests that the expected encoding is calculated.
  Test::assertStringEqual(expected, d.dumpBits());
  // Tests that decoding against leads to the original literal.
  Test::assertStringEqual(literal, d.str());

  float f1 = float(d);
  float f2 = std::stof(d.str());
  Test::assertFloatEqual(f1, f2);

  double d1 = double(d);
  double d2 = std::stod(d.str());
  Test::assertDoubleEqual(d1, d2);

  d += 2.f;
  float f3 = float(d);
  Test::assertFloatEqual(f1 + 2.f, f3);

  d += 2.;
  double d3 = double(d);
  Test::assertDoubleEqual(d1 + 4., d3);

  d = decimal("1");
  Test::assertDoubleEqual(double(d), 1.);
  d = "2";
  Test::assertDoubleEqual(double(d), 2.);
  d = 3.f;
  Test::assertDoubleEqual(double(d), 3.);
  d = 4.;
  Test::assertDoubleEqual(double(d), 4.);
  d = std::string("5");
  Test::assertDoubleEqual(double(d), 5.);
};

void DecimalInfiniteTest::testComparison()
{
    Test::assertBoolEqual(true, decimal("0") == decimal("0"));
    Test::assertBoolEqual(true, decimal("1") == decimal("1"));
    Test::assertBoolEqual(true, decimal("11234") == decimal("11234"));
    Test::assertBoolEqual(true, decimal("-12341") == decimal("-12341"));
    Test::assertBoolEqual(true, decimal("-12341.09237450928374509823745") == decimal("-12341.09237450928374509823745"));
    Test::assertBoolEqual(true, decimal("-123412340598234089234509237450928374509823745123412340598234089234509237450928374509823745") == decimal("-123412340598234089234509237450928374509823745123412340598234089234509237450928374509823745"));
    Test::assertBoolEqual(false, decimal("1") == decimal("0"));
    Test::assertBoolEqual(false, decimal("1") == decimal("-1"));

    Test::assertBoolEqual(true, decimal("0") < decimal("1"));
    Test::assertBoolEqual(true, decimal("0") < decimal("0.1"));
    Test::assertBoolEqual(true, decimal("0") < decimal("12345"));
    Test::assertBoolEqual(true, decimal("-1") < decimal("0"));
    Test::assertBoolEqual(true, decimal("-123452") < decimal("0"));
    Test::assertBoolEqual(true, decimal("-0.023451") < decimal("0"));

    Test::assertBoolEqual(true, decimal("0.12345") < decimal("0.123456"));
    Test::assertBoolEqual(true, decimal("0.12345") <= decimal("0.123456"));
    Test::assertBoolEqual(false, decimal("0.12345") > decimal("0.123456"));
    Test::assertBoolEqual(false, decimal("0.12345") >= decimal("0.123456"));
    Test::assertBoolEqual(true, decimal("-0.12345") < decimal("0.123420379485702394857023948572034958720349587234"));
    Test::assertBoolEqual(true, decimal("-0.12345") <= decimal("0.123420379485702394857023948572034958720349587234"));
    Test::assertBoolEqual(false, decimal("-0.12345") > decimal("0.123420379485702394857023948572034958720349587234"));
    Test::assertBoolEqual(false, decimal("-0.12345") >= decimal("0.123420379485702394857023948572034958720349587234"));
    Test::assertBoolEqual(false, decimal("-0.12345") < decimal("-0.12345"));
    Test::assertBoolEqual(false, decimal("-0.12345") > decimal("-0.12345"));
    Test::assertBoolEqual(true, decimal("-0.12345") <= decimal("-0.12345"));
    Test::assertBoolEqual(true, decimal("-0.12345") >= decimal("-0.12345"));
}
