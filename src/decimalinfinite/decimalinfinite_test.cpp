#include "decimalinfinite_test.h"

#include <iostream>
using namespace std;

void DecimalInfiniteTest::run() {
	test("-123456789", "0000011001001101111110101101100000001101110");
	test("-1000", "00001011001");
	test("-100", "00001101001");
	test("-10", "00001111001");
	test("-9", "000100001");
	test("-8", "000100010");
	test("-7", "000100011");
	test("-6", "000100100");
	test("-5", "000100101");
	test("-4", "000100110");
	test("-3", "000100111");
	test("-2", "000101000");
	test("-1", "000101001");
	test("0", "10");
	test("0.02", "10001110010");
	test("0.2", "100100010");
	test("1", "101010001");
	test("2", "101010010");
	test("3", "101010011");
	test("4", "101010100");
	test("5", "101010101");
	test("6", "101010110");
	test("7", "101010111");
	test("8", "101011000");
	test("9", "101011001");
	test("10", "10110000001");
	test("11", "101100000010001100100");
	test("20", "10110000010");
	test("200", "10110010010");
	test("2000", "10110100010");
	test("20000", "10110110010");
	test("200000", "1011100000010");
	test("2000000", "1011100010010");
	test("20000000", "1011100100010");
	test("123456789", "1011100110001001110101010001101111101111010");
}


bool DecimalInfiniteTest::assertEqual(std::string expected, std::string actual) {
	if (actual == expected) {
		std::cout << "[PASSED]" << std::endl;
		return true;
	} else {
		std::cout << "[FAIL]" << std::endl;
		std::cout << "Actual:" << actual << std::endl;
		std::cout << "Expected: " << expected << std::endl;
		return false;
	}
}

