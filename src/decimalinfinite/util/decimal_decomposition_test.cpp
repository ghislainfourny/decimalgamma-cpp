#include "decimal_decomposition_test.h"

#include "decimal_decomposition.h"
#include "test.h"

#include <iostream>
using namespace std;

void DecimalDecompositionTest::run() {
	{
		std::string s = "-123456789";
		std::cout << "Testing " << s << std::endl;
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(false, d.isPositive());
		Test::assertBoolEqual(true, d.isExponentNonNegative());
		Test::assertIntEqual(8, d.getAbsoluteExponent());
		Test::assertIntEqual(8, d.getExponent());
		Test::assertBoolEqual(true, d.isNormalized());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "-1000";
		std::cout << "Testing " << s << std::endl;
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(false, d.isPositive());
		Test::assertBoolEqual(true, d.isExponentNonNegative());
		Test::assertIntEqual(3, d.getAbsoluteExponent());
		Test::assertIntEqual(3, d.getExponent());
		Test::assertBoolEqual(true, d.isNormalized());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "-1";
		std::cout << "Testing " << s << std::endl;
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(false, d.isPositive());
		Test::assertBoolEqual(true, d.isExponentNonNegative());
		Test::assertIntEqual(0, d.getAbsoluteExponent());
		Test::assertIntEqual(0, d.getExponent());
		Test::assertBoolEqual(true, d.isNormalized());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "0";
		std::cout << "Testing " << s << std::endl;
		DecimalDecomposition d(s);
		Test::assertBoolEqual(true, d.isZero());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "-0.1";
		std::cout << "Testing " << s << std::endl;
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(false, d.isPositive());
		Test::assertBoolEqual(false, d.isExponentNonNegative());
		Test::assertIntEqual(1, d.getAbsoluteExponent());
		Test::assertIntEqual(-1, d.getExponent());
		Test::assertBoolEqual(true, d.isNormalized());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "0.1";
		std::cout << "Testing " << s << std::endl;
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(true, d.isPositive());
		Test::assertBoolEqual(false, d.isExponentNonNegative());
		Test::assertIntEqual(1, d.getAbsoluteExponent());
		Test::assertIntEqual(-1, d.getExponent());
		Test::assertBoolEqual(true, d.isNormalized());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "1123.12345234";
		std::cout << "Testing " << s << std::endl;
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(true, d.isPositive());
		Test::assertBoolEqual(true, d.isExponentNonNegative());
		Test::assertIntEqual(3, d.getAbsoluteExponent());
		Test::assertIntEqual(3, d.getExponent());
		Test::assertBoolEqual(true, d.isNormalized());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "-1123.12345234";
		std::cout << "Testing " << s << std::endl;
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(false, d.isPositive());
		Test::assertBoolEqual(true, d.isExponentNonNegative());
		Test::assertIntEqual(3, d.getAbsoluteExponent());
		Test::assertIntEqual(3, d.getExponent());
		Test::assertBoolEqual(true, d.isNormalized());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "-0.0000000112312345234";
		std::cout << "Testing " << s << std::endl;
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(false, d.isPositive());
		Test::assertBoolEqual(false, d.isExponentNonNegative());
		Test::assertIntEqual(8, d.getAbsoluteExponent());
		Test::assertIntEqual(-8, d.getExponent());
		Test::assertBoolEqual(true, d.isNormalized());
		Test::assertStringEqual(s, d.str());
	}

	{
		std::string s = "0.0000000112312345234";
		std::cout << "Testing " << s << std::endl;
		DecimalDecomposition d(s);
		Test::assertBoolEqual(false, d.isZero());
		Test::assertBoolEqual(true, d.isPositive());
		Test::assertBoolEqual(false, d.isExponentNonNegative());
		Test::assertIntEqual(8, d.getAbsoluteExponent());
		Test::assertIntEqual(-8, d.getExponent());
		Test::assertBoolEqual(true, d.isNormalized());
		Test::assertStringEqual(s, d.str());
	}


}
