#include <gtest/gtest.h>
#include <stdint.h>

#include "decimal_decomposition.h"

TEST(DecimalDecomposition, BasicOperations)
{
    {
        const char* s = "-123456789";
        std::cout << "Testing " << s << std::endl;
        DecimalDecomposition d(s);
        ASSERT_FALSE(d.isZero());
        ASSERT_FALSE(d.isPositive());
        ASSERT_TRUE(d.isExponentNonNegative());
        ASSERT_EQ(8, d.getAbsoluteExponent());
        ASSERT_EQ(8, d.getExponent());
        ASSERT_TRUE(d.isNormalized());
        ASSERT_EQ(s, d.str());
    }

    {
        const char* s = "-1000";
        std::cout << "Testing " << s << std::endl;
        DecimalDecomposition d(s);
        ASSERT_FALSE(d.isZero());
        ASSERT_FALSE(d.isPositive());
        ASSERT_TRUE(d.isExponentNonNegative());
        ASSERT_EQ(3, d.getAbsoluteExponent());
        ASSERT_EQ(3, d.getExponent());
        ASSERT_TRUE(d.isNormalized());
        ASSERT_EQ(s, d.str());
    }

    {
        const char* s = "-1";
        std::cout << "Testing " << s << std::endl;
        DecimalDecomposition d(s);
        ASSERT_FALSE(d.isZero());
        ASSERT_FALSE(d.isPositive());
        ASSERT_TRUE(d.isExponentNonNegative());
        ASSERT_EQ(0, d.getAbsoluteExponent());
        ASSERT_EQ(0, d.getExponent());
        ASSERT_TRUE(d.isNormalized());
        ASSERT_EQ(s, d.str());
    }

    {
        const char* s = "0";
        std::cout << "Testing " << s << std::endl;
        DecimalDecomposition d(s);
        ASSERT_TRUE(d.isZero());
        ASSERT_EQ(s, d.str());
    }

    {
        const char* s = "-0.1";
        std::cout << "Testing " << s << std::endl;
        DecimalDecomposition d(s);
        ASSERT_FALSE(d.isZero());
        ASSERT_FALSE(d.isPositive());
        ASSERT_FALSE(d.isExponentNonNegative());
        ASSERT_EQ(1, d.getAbsoluteExponent());
        ASSERT_EQ(-1, d.getExponent());
        ASSERT_TRUE(d.isNormalized());
        ASSERT_EQ(s, d.str());
    }

    {
        const char* s = "0.1";
        std::cout << "Testing " << s << std::endl;
        DecimalDecomposition d(s);
        ASSERT_FALSE(d.isZero());
        ASSERT_TRUE(d.isPositive());
        ASSERT_FALSE(d.isExponentNonNegative());
        ASSERT_EQ(1, d.getAbsoluteExponent());
        ASSERT_EQ(-1, d.getExponent());
        ASSERT_TRUE(d.isNormalized());
        ASSERT_EQ(s, d.str());
    }

    {
        const char* s = "1123.12345234";
        std::cout << "Testing " << s << std::endl;
        DecimalDecomposition d(s);
        ASSERT_FALSE(d.isZero());
        ASSERT_TRUE(d.isPositive());
        ASSERT_TRUE(d.isExponentNonNegative());
        ASSERT_EQ(3, d.getAbsoluteExponent());
        ASSERT_EQ(3, d.getExponent());
        ASSERT_TRUE(d.isNormalized());
        ASSERT_EQ(s, d.str());
    }

    {
        const char* s = "-1123.12345234";
        std::cout << "Testing " << s << std::endl;
        DecimalDecomposition d(s);
        ASSERT_FALSE(d.isZero());
        ASSERT_FALSE(d.isPositive());
        ASSERT_TRUE(d.isExponentNonNegative());
        ASSERT_EQ(3, d.getAbsoluteExponent());
        ASSERT_EQ(3, d.getExponent());
        ASSERT_TRUE(d.isNormalized());
        ASSERT_EQ(s, d.str());
    }

    {
        const char* s = "-0.0000000112312345234";
        std::cout << "Testing " << s << std::endl;
        DecimalDecomposition d(s);
        ASSERT_FALSE(d.isZero());
        ASSERT_FALSE(d.isPositive());
        ASSERT_FALSE(d.isExponentNonNegative());
        ASSERT_EQ(8, d.getAbsoluteExponent());
        ASSERT_EQ(-8, d.getExponent());
        ASSERT_TRUE(d.isNormalized());
        ASSERT_EQ(s, d.str());
    }

    {
        const char* s = "0.0000000112312345234";
        std::cout << "Testing " << s << std::endl;
        DecimalDecomposition d(s);
        ASSERT_FALSE(d.isZero());
        ASSERT_TRUE(d.isPositive());
        ASSERT_FALSE(d.isExponentNonNegative());
        ASSERT_EQ(8, d.getAbsoluteExponent());
        ASSERT_EQ(-8, d.getExponent());
        ASSERT_TRUE(d.isNormalized());
        ASSERT_EQ(s, d.str());
    }

    {
        std::cout << "Testing renormalization." << std::endl;
        DecimalDecomposition d;
        d.setExponent(3);
        d.setPositive(true);
        std::vector<DigitType> digits;
        digits.push_back(1);
        digits.push_back(12);
        d.setDigits(digits);
        ASSERT_FALSE(d.isNormalized());

        d.renormalize();
        ASSERT_TRUE(d.isNormalized());
        ASSERT_FALSE(d.isZero());
        ASSERT_TRUE(d.isPositive());
        ASSERT_TRUE(d.isExponentNonNegative());
        ASSERT_EQ(3, d.getAbsoluteExponent());
        ASSERT_EQ(3, d.getExponent());
        ASSERT_EQ("2200", d.str());
    }

    {
        std::cout << "Testing renormalization (positive)." << std::endl;
        DecimalDecomposition d;
        d.setExponent(3);
        d.setPositive(true);
        std::vector<DigitType> digits;
        digits.push_back(1);
        digits.push_back(123);
        d.setDigits(digits);
        ASSERT_FALSE(d.isNormalized());

        d.renormalize();
        ASSERT_TRUE(d.isNormalized());
        ASSERT_FALSE(d.isZero());
        ASSERT_TRUE(d.isPositive());
        ASSERT_TRUE(d.isExponentNonNegative());
        ASSERT_EQ(4, d.getAbsoluteExponent());
        ASSERT_EQ(4, d.getExponent());
        ASSERT_EQ("13300", d.str());
    }

    {
        std::cout << "Testing renormalization (negative)." << std::endl;
        DecimalDecomposition d;
        d.setExponent(-3);
        d.setPositive(true);
        std::vector<DigitType> digits;
        digits.push_back(1);
        digits.push_back(123);
        d.setDigits(digits);
        ASSERT_FALSE(d.isNormalized());

        d.renormalize();
        ASSERT_TRUE(d.isNormalized());
        ASSERT_FALSE(d.isZero());
        ASSERT_TRUE(d.isPositive());
        ASSERT_FALSE(d.isExponentNonNegative());
        ASSERT_EQ(2, d.getAbsoluteExponent());
        ASSERT_EQ(-2, d.getExponent());
        ASSERT_EQ("0.0133", d.str());
    }

    {
        std::cout << "Testing renormalization (negative to positive)."
                  << std::endl;
        DecimalDecomposition d;
        d.setExponent(-1);
        d.setPositive(true);
        std::vector<DigitType> digits;
        digits.push_back(1);
        digits.push_back(123);
        d.setDigits(digits);
        ASSERT_FALSE(d.isNormalized());

        d.renormalize();
        ASSERT_TRUE(d.isNormalized());
        ASSERT_FALSE(d.isZero());
        ASSERT_TRUE(d.isPositive());
        ASSERT_TRUE(d.isExponentNonNegative());
        ASSERT_EQ(0, d.getAbsoluteExponent());
        ASSERT_EQ(0, d.getExponent());
        ASSERT_EQ("1.33", d.str());
    }
}
