#include <gtest/gtest.h>

#include <string>

#include "decimalinfinite.h"

using namespace di;

void EncodeDecodeTest(std::string literal, std::string expected)
{
    decimal d(literal);
    // Tests that the expected encoding is calculated.
    ASSERT_EQ(expected, d.dumpBits());
    // Tests that decoding against leads to the original literal.
    ASSERT_EQ(literal, d.str());

    float f1 = float(d);
    float f2 = std::stof(d.str());
    ASSERT_EQ(f1, f2);

    double d1 = double(d);
    double d2 = std::stod(d.str());
    ASSERT_EQ(d1, d2);

    d += 2.f;
    if (d.str().length() < 10)
    {
        float f3 = float(d);
        ASSERT_EQ(f1 + 2.f, f3);
    }

    d += 2.;
    double d3 = double(d);
    ASSERT_EQ(d1 + 4., d3);

    d = decimal("1");
    ASSERT_EQ(double(d), 1.);
    d = "2";
    ASSERT_EQ(double(d), 2.);
    d = 3.f;
    ASSERT_EQ(double(d), 3.);
    d = 4.;
    ASSERT_EQ(double(d), 4.);
    d = std::string("5");
    ASSERT_EQ(double(d), 5.);
};

TEST(DecimalInfinite, EncodeDecode)
{
    EncodeDecodeTest("-123456789",
                     "0000011011001101111110101101100000001101110");
    EncodeDecodeTest("-1000", "00001101001");
    EncodeDecodeTest("-100", "00001111001");
    EncodeDecodeTest("-10", "000101001");
    EncodeDecodeTest("-9", "000110001");
    EncodeDecodeTest("-8", "000110010");
    EncodeDecodeTest("-7", "000110011");
    EncodeDecodeTest("-6", "000110100");
    EncodeDecodeTest("-5", "000110101");
    EncodeDecodeTest("-4", "000110110");
    EncodeDecodeTest("-3", "000110111");
    EncodeDecodeTest("-2", "000111000");
    EncodeDecodeTest("-1", "000111001");
    EncodeDecodeTest("0", "10");
    EncodeDecodeTest("0.02", "10001110010");
    EncodeDecodeTest("0.2", "100100010");
    EncodeDecodeTest("1", "101000001");
    EncodeDecodeTest("2", "101000010");
    EncodeDecodeTest("3", "101000011");
    EncodeDecodeTest("4", "101000100");
    EncodeDecodeTest("5", "101000101");
    EncodeDecodeTest("6", "101000110");
    EncodeDecodeTest("7", "101000111");
    EncodeDecodeTest("8", "101001000");
    EncodeDecodeTest("9", "101001001");
    EncodeDecodeTest("10", "101010001");
    EncodeDecodeTest("11", "1010100010001100100");
    EncodeDecodeTest("20", "101010010");
    EncodeDecodeTest("200", "10110000010");
    EncodeDecodeTest("2000", "10110010010");
    EncodeDecodeTest("20000", "10110100010");
    EncodeDecodeTest("200000", "10110110010");
    EncodeDecodeTest("2000000", "1011100000010");
    EncodeDecodeTest("20000000", "1011100010010");
    EncodeDecodeTest("123456789",
                     "1011100100001001110101010001101111101111010");
}

TEST(DecimalInfinite, Comparison)
{
    ASSERT_TRUE(decimal("0") == decimal("0"));
    ASSERT_TRUE(decimal("1") == decimal("1"));
    ASSERT_TRUE(decimal("11234") == decimal("11234"));
    ASSERT_TRUE(decimal("-12341") == decimal("-12341"));
    ASSERT_TRUE(decimal("-12341.09237450928374509823745") ==
                decimal("-12341.09237450928374509823745"));
    ASSERT_TRUE(
            decimal("-123412340598234089234509237450928374509823745123412340598"
                    "234089234509237450928374509823745") ==
            decimal("-1234123405982340892345092374509283745098237451234"
                    "12340598234089234509237450928374509823745"));
    ASSERT_FALSE(decimal("1") == decimal("0"));
    ASSERT_FALSE(decimal("1") == decimal("-1"));

    ASSERT_TRUE(decimal("0") < decimal("1"));
    ASSERT_TRUE(decimal("0") < decimal("0.1"));
    ASSERT_TRUE(decimal("0") < decimal("12345"));
    ASSERT_TRUE(decimal("-1") < decimal("0"));
    ASSERT_TRUE(decimal("-123452") < decimal("0"));
    ASSERT_TRUE(decimal("-0.023451") < decimal("0"));

    ASSERT_TRUE(decimal("0.12345") < decimal("0.123456"));
    ASSERT_TRUE(decimal("0.12345") <= decimal("0.123456"));
    ASSERT_FALSE(decimal("0.12345") > decimal("0.123456"));
    ASSERT_FALSE(decimal("0.12345") >= decimal("0.123456"));
    ASSERT_TRUE(decimal("-0.12345") < decimal("0."
                                              "123420379485702394857023948572"
                                              "034958720349587234"));
    ASSERT_TRUE(decimal("-0.12345") <= decimal("0."
                                               "12342037948570239485702394857"
                                               "2034958720349587234"));
    ASSERT_FALSE(decimal("-0.12345") > decimal("0."
                                               "12342037948570239485702394857"
                                               "2034958720349587234"));
    ASSERT_FALSE(decimal("-0.12345") >= decimal("0."
                                                "1234203794857023948570239485"
                                                "72034958720349587234"));
    ASSERT_FALSE(decimal("-0.12345") < decimal("-0.12345"));
    ASSERT_FALSE(decimal("-0.12345") > decimal("-0.12345"));
    ASSERT_TRUE(decimal("-0.12345") <= decimal("-0.12345"));
    ASSERT_TRUE(decimal("-0.12345") >= decimal("-0.12345"));
}

TEST(DecimalInfinite, Addition)
{
    ASSERT_TRUE(decimal("0") == decimal("0") + decimal("0"));
    ASSERT_TRUE(decimal("1") == decimal("1") + decimal("0"));
    ASSERT_TRUE(decimal("1") == decimal("0") + decimal("1"));
    ASSERT_TRUE(decimal("2") == decimal("1") + decimal("1"));
    ASSERT_TRUE(decimal("4") == decimal("2") + decimal("2"));
    ASSERT_TRUE(decimal("8") == decimal("4") + decimal("4"));
    ASSERT_TRUE(decimal("16") == decimal("8") + decimal("8"));
}
