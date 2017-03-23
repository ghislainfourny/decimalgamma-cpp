#include "decimal_decomposition_test.h"

#include "decimal_decomposition.h"
#include "test.h"

#include <iostream>
using namespace std;

void DecimalDecompositionTest::run()
{
    {
        const char* s = "-123456789";
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
        const char* s = "-1000";
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
        const char* s = "-1";
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
        const char* s = "0";
        std::cout << "Testing " << s << std::endl;
        DecimalDecomposition d(s);
        Test::assertBoolEqual(true, d.isZero());
        Test::assertStringEqual(s, d.str());
    }

    {
        const char* s = "-0.1";
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
        const char* s = "0.1";
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
        const char* s = "1123.12345234";
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
        const char* s = "-1123.12345234";
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
        const char* s = "-0.0000000112312345234";
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
        const char* s = "0.0000000112312345234";
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

    {
        std::cout << "Testing renormalization." << std::endl;
        DecimalDecomposition d;
        d.setExponent(3);
        d.setPositive(true);
        std::vector<int> digits;
        digits.push_back(1);
        digits.push_back(12);
        d.setDigits(digits);
        Test::assertBoolEqual(false, d.isNormalized());
        d.renormalize();
        Test::assertBoolEqual(true, d.isNormalized());
        Test::assertBoolEqual(false, d.isZero());
        Test::assertBoolEqual(true, d.isPositive());
        Test::assertBoolEqual(true, d.isExponentNonNegative());
        Test::assertIntEqual(3, d.getAbsoluteExponent());
        Test::assertIntEqual(3, d.getExponent());
        Test::assertStringEqual("2200", d.str());
    }

    {
        std::cout << "Testing renormalization (positive)." << std::endl;
        DecimalDecomposition d;
        d.setExponent(3);
        d.setPositive(true);
        std::vector<int> digits;
        digits.push_back(1);
        digits.push_back(123);
        d.setDigits(digits);
        Test::assertBoolEqual(false, d.isNormalized());
        d.renormalize();
        Test::assertBoolEqual(true, d.isNormalized());
        Test::assertBoolEqual(false, d.isZero());
        Test::assertBoolEqual(true, d.isPositive());
        Test::assertBoolEqual(true, d.isExponentNonNegative());
        Test::assertIntEqual(4, d.getAbsoluteExponent());
        Test::assertIntEqual(4, d.getExponent());
        Test::assertStringEqual("13300", d.str());
    }

    {
        std::cout << "Testing renormalization (negative)." << std::endl;
        DecimalDecomposition d;
        d.setExponent(-3);
        d.setPositive(true);
        std::vector<int> digits;
        digits.push_back(1);
        digits.push_back(123);
        d.setDigits(digits);
        Test::assertBoolEqual(false, d.isNormalized());
        d.renormalize();
        Test::assertBoolEqual(true, d.isNormalized());
        Test::assertBoolEqual(false, d.isZero());
        Test::assertBoolEqual(true, d.isPositive());
        Test::assertBoolEqual(false, d.isExponentNonNegative());
        Test::assertIntEqual(2, d.getAbsoluteExponent());
        Test::assertIntEqual(-2, d.getExponent());
        Test::assertStringEqual("0.0133", d.str());
    }

    {
        std::cout << "Testing renormalization (negative to positive)."
                  << std::endl;
        DecimalDecomposition d;
        d.setExponent(-2);
        d.setPositive(true);
        std::vector<int> digits;
        digits.push_back(1);
        digits.push_back(12344);
        d.setDigits(digits);
        Test::assertBoolEqual(false, d.isNormalized());
        d.renormalize();
        Test::assertBoolEqual(true, d.isNormalized());
        Test::assertBoolEqual(false, d.isZero());
        Test::assertBoolEqual(true, d.isPositive());
        Test::assertBoolEqual(true, d.isExponentNonNegative());
        Test::assertIntEqual(1, d.getAbsoluteExponent());
        Test::assertIntEqual(1, d.getExponent());
        Test::assertStringEqual("12.354", d.str());
    }
}
