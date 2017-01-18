//============================================================================
// Name        : helloworldcpp.cpp
// Author      : somebody
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "decimal_decomposition_test.h"
#include "decimal_decomposition.h"
using namespace std;

void DecimalDecompositionTest::run() {
	{
		std::string s = "-123456789";
		DecimalDecomposition d(s);
		assertEqual(false, d.isZero());
		assertEqual(false, d.isPositive());
		assertEqual(true, d.isExponentNonNegative());
		assertEqual(s, d.str());
	}

	{
		std::string s = "-1000";
		DecimalDecomposition d(s);
		assertEqual(false, d.isZero());
		assertEqual(false, d.isPositive());
		assertEqual(true, d.isExponentNonNegative());
		assertEqual(s, d.str());
	}

	{
		std::string s = "-1";
		DecimalDecomposition d(s);
		assertEqual(false, d.isZero());
		assertEqual(false, d.isPositive());
		assertEqual(true, d.isExponentNonNegative());
		assertEqual(s, d.str());
	}

	{
		std::string s = "0";
		DecimalDecomposition d(s);
		assertEqual(true, d.isZero());
		assertEqual(true, d.isPositive());
		assertEqual(true, d.isExponentNonNegative());
		assertEqual(s, d.str());
	}

	{
		std::string s = "-0.1";
		DecimalDecomposition d(s);
		assertEqual(false, d.isZero());
		assertEqual(false, d.isPositive());
		assertEqual(false, d.isExponentNonNegative());
		assertEqual(s, d.str());
	}

	{
		std::string s = "0.1";
		DecimalDecomposition d(s);
		assertEqual(false, d.isZero());
		assertEqual(true, d.isPositive());
		assertEqual(false, d.isExponentNonNegative());
		assertEqual(s, d.str());
	}

	{
		std::string s = "1123.12345234";
		DecimalDecomposition d(s);
		assertEqual(false, d.isZero());
		assertEqual(true, d.isPositive());
		assertEqual(true, d.isExponentNonNegative());
		assertEqual(s, d.str());
	}

	{
		std::string s = "-1123.12345234";
		DecimalDecomposition d(s);
		assertEqual(false, d.isZero());
		assertEqual(false, d.isPositive());
		assertEqual(true, d.isExponentNonNegative());
		assertEqual(s, d.str());
	}

	{
		std::string s = "-0.0000000112312345234";
		DecimalDecomposition d(s);
		assertEqual(false, d.isZero());
		assertEqual(false, d.isPositive());
		assertEqual(false, d.isExponentNonNegative());
		assertEqual(s, d.str());
	}

	{
		std::string s = "0.0000000112312345234";
		DecimalDecomposition d(s);
		assertEqual(false, d.isZero());
		assertEqual(true, d.isPositive());
		assertEqual(false, d.isExponentNonNegative());
		assertEqual(s, d.str());
	}


}

bool DecimalDecompositionTest::assertEqual(bool expected, bool actual) {
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

bool DecimalDecompositionTest::assertEqual(std::string expected, std::string actual) {
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
