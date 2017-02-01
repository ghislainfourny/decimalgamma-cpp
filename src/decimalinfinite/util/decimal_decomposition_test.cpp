#include "decimal_decomposition_test.h"

#include "decimal_decomposition.h"
#include "test.h"

#include <iostream>
using namespace std;

void DecimalDecompositionTest::run() {
	{
		std::string s = "-123456789";
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(false, d.isPositive());
		Test::assertBoolEqual(true, d.isExponentNonNegative());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "-1000";
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(false, d.isPositive());
		Test::assertBoolEqual(true, d.isExponentNonNegative());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "-1";
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(false, d.isPositive());
		Test::assertBoolEqual(true, d.isExponentNonNegative());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "0";
		DecimalDecomposition d(s);
		Test::assertBoolEqual(true, d.isZero());
		Test::assertBoolEqual(true, d.isPositive());
		Test::assertBoolEqual(true, d.isExponentNonNegative());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "-0.1";
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(false, d.isPositive());
		Test::assertBoolEqual(false, d.isExponentNonNegative());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "0.1";
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(true, d.isPositive());
		Test::assertBoolEqual(false, d.isExponentNonNegative());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "1123.12345234";
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(true, d.isPositive());
		Test::assertBoolEqual(true, d.isExponentNonNegative());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "-1123.12345234";
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(false, d.isPositive());
		Test::assertBoolEqual(true, d.isExponentNonNegative());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "-0.0000000112312345234";
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(false, d.isPositive());
		Test::assertBoolEqual(false, d.isExponentNonNegative());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "0.0000000112312345234";
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(true, d.isPositive());
		Test::assertBoolEqual(false, d.isExponentNonNegative());
		Test::assertStringEqual(s, d.str());
	}


}
