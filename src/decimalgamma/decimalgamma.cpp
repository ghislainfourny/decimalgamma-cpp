#include "decimalgamma.h"

#include "util/decimal_decomposition.h"

#include <assert.h>
#include <stdint.h>
#include <bitset>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n

const char di::decimal::LogTable256[256] = {
        -1,    0,     1,     1,     2,     2,     2,     2,
        3,     3,     3,     3,     3,     3,     3,     3,
        LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6), LT(7),
        LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)};

//#define DEBUG_BUILD

di::decimal::decimal() { _bits.appendBits(0b10, 2); }
di::decimal::decimal(const char* const literal)
{
    DecimalDecomposition decomposition(literal);
    init(decomposition);
}

di::decimal::decimal(const DecimalDecomposition& decomposition)
{
    init(decomposition);
}

void di::decimal::init(const DecimalDecomposition& decomposition)
{
    int abs_offset_exponent = decomposition.getAbsoluteExponent() + 2;
    bool invert_exponent_encoding = (decomposition.isPositive() !=
                                     decomposition.isExponentNonNegative());
#ifdef DEBUG_BUILD
    std::cout << "Exponent sign "
              << (decomposition.isExponentNonNegative() ? "+" : "-")
              << std::endl;
    std::cout << "Absolute offset exponent " << abs_offset_exponent
              << std::endl;
    std::cout << "Invert exponent encoding "
              << (invert_exponent_encoding ? "yes" : "no") << std::endl;
#endif
    unsigned int le = log2(abs_offset_exponent) + 1;
#ifdef DEBUG_BUILD
    std::cout << "Log2 exponent: " << le << std::endl;
#endif

    if (decomposition.isPositive() or decomposition.isZero())
    {
        _bits.appendBits(0b10, 2);
    }
    else
    {
        _bits.appendBits(0b00, 2);
    }
    if (decomposition.isZero())
    {
        return;
    }

    unsigned int xor_ones = (1 << le) - 1;
    if (invert_exponent_encoding)
    {
#ifdef DEBUG_BUILD
        std::cout << "Append: " << (1 << le) - 2 << std::endl;
#endif
        _bits.appendBits(((1 << le) - 2) xor xor_ones, le);
        xor_ones = (1 << (le - 1)) - 1;
#ifdef DEBUG_BUILD
        std::cout << "Append: " << abs_offset_exponent - (1 << (le - 1))
                  << std::endl;
#endif
        _bits.appendBits((abs_offset_exponent - (1 << (le - 1))) xor xor_ones,
                         le - 1);
    }
    else
    {
#ifdef DEBUG_BUILD
        std::cout << "Append: " << (1 << le) - 2 << std::endl;
#endif
        _bits.appendBits((1 << le) - 2, le);
#ifdef DEBUG_BUILD
        std::cout << "Append: " << abs_offset_exponent - (1 << (le - 1))
                  << std::endl;
#endif
        _bits.appendBits(abs_offset_exponent - (1 << (le - 1)), le - 1);
    }

    std::vector<DigitType> digits;
    decomposition.getDigits(&digits);
    int first = digits[0];
    if (!decomposition.isPositive())
    {
        first = 10 - first;
    }
#ifdef DEBUG_BUILD
    std::cout << "Write first: " << first << std::endl;
#endif
    _bits.appendBits(first, 4);

    int next = 1;
    while (next < digits.size())
    {
        int a = 0, b = 0, c = 0;
        a = digits[next++];
        bool isLast = (next + 3 >= digits.size());
        if (next < digits.size())
        {
            b = digits[next++];
        }
        if (next < digits.size())
        {
            c = digits[next++];
        }
        unsigned int towrite = 100 * a + 10 * b + c;
        if (!decomposition.isPositive())
        {
            if (isLast)
            {
                towrite = 1000 - towrite;
            }
            else
            {
                towrite = 999 - towrite;
            }
        }
#ifdef DEBUG_BUILD
        std::cout << "Write declet: " << towrite << std::endl;
#endif
        _bits.appendBits(towrite, 10);
    }
}

std::string di::decimal::dumpBits() { return _bits.str(); }
unsigned int di::decimal::log2(unsigned int v)
{
    unsigned int tt = v >> 24;

    if (tt)
    {
        return 24 + LogTable256[tt];
    }
    tt = v >> 16;
    if (tt)
    {
        return 16 + LogTable256[tt];
    }
    tt = v >> 8;
    if (tt)
    {
        return 8 + LogTable256[tt];
    }
    return LogTable256[v];
}

std::string di::decimal::str() const
{
    DecimalDecomposition result;
    getDecomposition(&result);
    return result.str();
}

void di::decimal::getDecomposition(::DecimalDecomposition* result) const
{
    if (_bits.getBits(0, 32) == (1 << 31))
    {
        result->setZero();
        return;
    }
    unsigned int sign_bits = _bits.getBits(0, 2);
    if (sign_bits == 0b00)
    {
        result->setPositive(false);
    }
    else if (sign_bits == 0b10)
    {
        result->setPositive(true);
    }
    else
    {
        std::cerr << "Decoding error: invalid first two bits: "
                  << std::bitset<2>(sign_bits) << std::endl;
    }
    uint exponent_bits = _bits.getBits(2, 30);
    bool exponent_inverted =
            (exponent_bits & 0b00100000000000000000000000000000) == 0;
    uint le = 0;
    if (exponent_inverted)
    {
        le = log2(exponent_bits);
    }
    else
    {
#ifdef DEBUG_BUILD
        std::cout << "Exponent bits1: " << std::bitset<31>(exponent_bits)
                  << std::endl;
        std::cout << "Exponent bits2: " << std::bitset<31>((uint)-1)
                  << std::endl;
        std::cout << "Exponent bits3: "
                  << std::bitset<31>(exponent_bits xor ((uint)-1) >> 1)
                  << std::endl;
        std::cout << "Exponent bits4: "
                  << log2(exponent_bits xor ((uint)-1 >> 1)) << std::endl;
#endif
        le = log2(exponent_bits xor ((uint)-1) >> 2);
    }
    le = 29 - le;
    uint absolute_exponent =
            (exponent_bits >> (29 - 2 * le)) & ((uint)-1 >> (32 - le));
    if (exponent_inverted)
    {
        absolute_exponent = absolute_exponent xor ((1 << le) - 1);
    }
    absolute_exponent = (1 << le) + absolute_exponent - 2;
    result->setAbsoluteExponent(absolute_exponent);
    if (exponent_inverted xor result->isPositive())
    {
        result->setExponentNonNegative(true);
    }
    else
    {
        result->setExponentNonNegative(false);
    }
    int start = 3 + 2 * le;

    size_t neededCapacity = 1 + 3 * (_bits.length() - start - 4) / 10;
    result->reserveDigits(neededCapacity);

    uint tetrade = _bits.getBits(start, 4);
    if (!result->isPositive())
    {
        tetrade = 10 - tetrade;
    }
    result->appendDigits(tetrade, 1);
#ifdef DEBUG_BUILD
    std::cout << "Exponent bits: " << std::bitset<31>(exponent_bits)
              << std::endl;
    std::cout << "Exponent inverted: " << exponent_inverted << std::endl;
    std::cout << "Number: " << le << std::endl;
    std::cout << "Absolute exponent: " << std::bitset<32>(absolute_exponent)
              << std::endl;
    std::cout << "Tetrade: " << std::bitset<4>(tetrade) << std::endl;
#endif
    start += 4;
    while (start < _bits.length())
    {
        int declet = _bits.getBits(start, 10);
        int isLast = (start + 10 >= _bits.length());
        if (!result->isPositive())
        {
            if (isLast)
            {
                declet = 1000 - declet;
            }
            else
            {
                declet = 999 - declet;
            }
        }
        result->appendDigits(declet, 3);
        start += 10;
    }
    assert(result->capacityOfDigits() == neededCapacity);
    result->finalizeDigits();
}

bool di::decimal::operator==(const decimal& other) const
{
    int lengthl = _bits.length();
    int lengthr = other._bits.length();

    int maxlength = std::max(lengthl, lengthr);

    for (int i = 0; i < maxlength; i += 32)
    {
        unsigned int bitsl = _bits.getBits(i, 32);
        unsigned int bitsr = other._bits.getBits(i, 32);

        if (bitsl != bitsr)
        {
            return false;
        }
    }
    return true;
};

bool di::decimal::operator<(const decimal& other) const
{
    int lengthl = _bits.length();
    int lengthr = other._bits.length();

    int maxlength = std::max(lengthl, lengthr);

    for (int i = 0; i < maxlength; i += 32)
    {
        unsigned int bitsl = _bits.getBits(i, 32);
        unsigned int bitsr = other._bits.getBits(i, 32);

        if (bitsl < bitsr)
        {
            return true;
        }
        if (bitsl > bitsr)
        {
            return false;
        }
    }
    return false;
};

di::decimal di::decimal::operator+(const decimal& other) const
{
    if (other == decimal())
    {
        return *this;
    }
    if (*this == decimal())
    {
        return other;
    }
    DecimalDecomposition left;
    DecimalDecomposition right;
    this->getDecomposition(&left);
    other.getDecomposition(&right);
    left += right;
    return di::decimal(left);
}

di::decimal& di::decimal::operator+=(const decimal& other)
{
    if (other == decimal())
    {
        return *this;
    }
    if (*this == decimal())
    {
        *this = other;
        return *this;
    }
    DecimalDecomposition left;
    DecimalDecomposition right;
    this->getDecomposition(&left);
    other.getDecomposition(&right);
    left += right;
    this->_bits.reset();
    this->init(left);
    return *this;
}
