#include "decimal_decomposition.h"
#include "exceptions.h"

#include <assert.h>
#include <stdint.h>
#include <iostream>
#include <sstream>

//#define DEBUG_BUILD

DecimalDecomposition::DecimalDecomposition() { encode("0"); }
DecimalDecomposition::DecimalDecomposition(const char* const literal)
{
    encode(literal);
}

DecimalDecomposition::DecimalDecomposition(const DecimalDecomposition& other)
{
    copy(other);
}

void DecimalDecomposition::encode(const char* const literal)
{
    _sign = true;
    bool period = false;
    bool digit = false;
    int exponent = -1;
    for (const char* p = literal; *p != '\0'; ++p)
    {
        char c = *p;

        if (c == '0')
        {
            if (digit)
            {
                _digits.push_back(c - '0');
                if (!period)
                {
                    ++exponent;
                }
                continue;
            }
            else
            {
                if (period)
                {
                    --exponent;
                }
                continue;
            }
        }

        if (c >= '1' && c <= '9')
        {
            _digits.push_back(c - '0');
            if (!period)
            {
                ++exponent;
            }
            digit = true;
            continue;
        }

        if (c == '-')
        {
            if (p != literal)
            {
                std::ostringstream b;
                b << "Error: illegal literal (" << literal
                  << "). Minus sign can only appear as first character."
                  << std::endl;
                throw decimal_decomposition_exception(b.str());
            }
            _sign = false;
        }

        if (c == '.')
        {
            if (period)
            {
                std::ostringstream b;
                b << "Error: illegal literal (" << literal
                  << "). Period can only appear once." << std::endl;
                throw decimal_decomposition_exception(b.str());
            }
            period = true;
        }
    }

    int i = _digits.size() - 1;
    while (i != -1 && _digits[i] == 0)
    {
        _digits.pop_back();
        --i;
    }

#ifdef DEBUG_BUILD
    std::cout << "Sign:" << (sign ? "+" : "-") << std::endl;
    std::cout << "Literal:" << literal << std::endl;
    std::cout << "Digits:" << std::endl;
    for (int i = 0; i < digits.size(); ++i)
    {
        std::cout << digits[i] << std::endl;
    }
    std::cout << "Exponent " << exponent << std::endl;
#endif
    _absolute_exponent = abs(exponent);
    _exponent_sign = (exponent >= 0);
#ifdef DEBUG_BUILD
    std::cout << "Exponent sign " << (exponent_sign ? "+" : "-") << std::endl;
    std::cout << "Absolute offset exponent " << abs_offset_exponent
              << std::endl;
    std::cout << "Invert exponent encoding "
              << (invert_exponent_encoding ? "yes" : "no") << std::endl;
#endif
}

bool DecimalDecomposition::isZero() const { return _digits.size() == 0; }
bool DecimalDecomposition::isPositive() const { return _sign; }
bool DecimalDecomposition::isExponentNonNegative() const
{
    return _exponent_sign;
}
unsigned int DecimalDecomposition::getAbsoluteExponent() const
{
    return _absolute_exponent;
}

int DecimalDecomposition::getExponent() const
{
    if (isExponentNonNegative())
        return _absolute_exponent;
    else
        return -_absolute_exponent;
}

void DecimalDecomposition::getDigits(std::vector<DigitType>* digits) const
{
    *digits = _digits;
}

void DecimalDecomposition::setZero() { _digits.clear(); }
unsigned int DecimalDecomposition::getNumberOfDigits() const
{
    return _digits.size();
}

void DecimalDecomposition::setPositive(bool sign) { _sign = sign; }
void DecimalDecomposition::setExponentNonNegative(bool exponent_sign)
{
    _exponent_sign = exponent_sign;
}

void DecimalDecomposition::setAbsoluteExponent(unsigned int e)
{
    _absolute_exponent = e;
}

void DecimalDecomposition::setExponent(int e)
{
    if (e >= 0)
    {
        _absolute_exponent = e;
        setExponentNonNegative(true);
    }
    else
    {
        _absolute_exponent = -e;
        setExponentNonNegative(false);
    }
}

void DecimalDecomposition::setDigits(std::vector<DigitType>&& digits)
{
    _digits = digits;
    int i = _digits.size() - 1;
    while (i != -1 && _digits[i] == 0)
    {
        _digits.pop_back();
        --i;
    }
}

std::string DecimalDecomposition::str()
{
    if (isZero())
    {
        return "0";
    }
    std::stringstream ss;
    if (!isPositive())
    {
        ss.put('-');
    }
    if (isExponentNonNegative())
    {
        int exponent = getAbsoluteExponent();
        bool period = false;
        for (int i = 0; i < _digits.size(); ++i)
        {
            ss.put('0' + _digits[i]);
            if (!period)
            {
                --exponent;
            }
            if (exponent == -1 && !period && i != _digits.size() - 1)
            {
                ss.put('.');
                period = true;
            }
        }
        while (exponent > -1)
        {
            ss.put('0');
            --exponent;
        }
    }
    else
    {
        unsigned int exponent = getAbsoluteExponent();
        ss.put('0');
        ss.put('.');
        while (exponent > 1)
        {
            ss.put('0');
            --exponent;
        }
        for (int i = 0; i < _digits.size(); ++i)
        {
            ss.put('0' + _digits[i]);
        }
    }
    return ss.str();
}

void DecimalDecomposition::copy(const DecimalDecomposition& other)
{
    if (other.isZero())
    {
        setZero();
        return;
    };
    _sign = other._sign;
    _absolute_exponent = other._absolute_exponent;
    _exponent_sign = other._exponent_sign;
    _digits = other._digits;
}

void DecimalDecomposition::shiftExponent(int newExponent)
{
    int exponent = getExponent();
    if (newExponent < exponent)
    {
        std::cerr << "Cannot shift to lower exponent." << std::endl;
    }
    int shift = newExponent - exponent;
    for (int i = 0; i < shift; ++i)
    {
        _digits.insert(_digits.begin(), 0);
    }
    setExponent(newExponent);
}

DecimalDecomposition DecimalDecomposition::operator+=(
        const DecimalDecomposition& right)
{
    if (this->isZero())
    {
        *this = right;
        return *this;
    }
    if (right.isZero())
    {
        return *this;
    }

    int exponent_this = this->getExponent();
    int exponent_other = right.getExponent();
    int this_offset = 0;
    int other_offset = 0;
    if (exponent_other > exponent_this)
    {
        this->setExponent(exponent_other);
        this_offset = exponent_other - exponent_this;
    }
    else
    {
        other_offset = exponent_this - exponent_other;
    }

    int i = _digits.size() + this_offset - 1;
    if (right._digits.size() + other_offset > _digits.size() + this_offset)
    {
        i = right._digits.size() + other_offset - 1;
    }
    _digits.resize(i + 1);

    if (this->isPositive() == right.isPositive())
    {
        for (; i >= 0; --i)
        {
            if (i - other_offset < 0 ||
                i - other_offset >= right._digits.size())
            {
                if (i - this_offset < 0)
                {
                    _digits[i] = 0;
                }
                else
                {
                    _digits[i] = _digits[i - this_offset];
                }
            }
            else if (i - this_offset < 0)
            {
                _digits[i] = right._digits[i - other_offset];
            }
            else
            {
                _digits[i] = _digits[i - this_offset] +
                             right._digits[i - other_offset];
            }
        }
    }
    else
    {
        for (; i >= 0; --i)
        {
            if (i - other_offset < 0 ||
                i - other_offset >= right._digits.size())
            {
                if (i - this_offset < 0)
                {
                    _digits[i] = 0;
                }
                else
                {
                    _digits[i] = _digits[i - this_offset];
                }
            }
            else if (i - this_offset < 0)
            {
                _digits[i] = -right._digits[i - other_offset];
            }
            else
            {
                _digits[i] = _digits[i - this_offset] -
                             right._digits[i - other_offset];
            }
        }
    }
    if (!this->isNormalized())
    {
        this->renormalize();
    }
    if (!this->isNormalized())
    {
        std::ostringstream b;
        b << "Error: result is not normalized: " << dump() << std::endl;
        throw decimal_decomposition_exception(b.str());
    }
    return *this;
}

bool DecimalDecomposition::isNormalized()
{
    for (auto it = _digits.begin(); it != _digits.end(); ++it)
    {
        if (*it < 0 || *it > 9) return false;
    }
    if (_digits.size() > 0 && _digits[0] == 0) return false;
    return true;
}

void DecimalDecomposition::renormalize()
{
    int carry = 0;
    for (auto it = _digits.rbegin(); it != _digits.rend(); ++it)
    {
        if (carry != 0 || *it < 0 || *it > 9)
        {
            *it += carry;
            if (*it < 0)
            {
                carry = 0;
                while (*it < 0)
                {
                    *it += 10;
                }
                --carry;
            }
            else
            {
                carry = *it / 10;
            }
            *it = *it % 10;
        }
    }
    if (carry != 0)
    {
        if (_exponent_sign)
        {
            while (carry != 0)
            {
                ++_absolute_exponent;
                _digits.insert(_digits.begin(), carry % 10);
                carry /= 10;
            }
        }
        else
        {
            while (carry != 0)
            {
                if (_absolute_exponent == 0)
                {
                    _absolute_exponent = 1;
                }
                else
                {
                    --_absolute_exponent;
                    if (_absolute_exponent == 0)
                    {
                        _exponent_sign = true;
                    }
                }
                _digits.insert(_digits.begin(), carry % 10);
                carry /= 10;
            }
        }
    }
    if (_digits.size() > 0)
    {
        while (!_digits.empty() && _digits[0] == 0)
        {
            _digits.erase(_digits.begin());
            if (!_exponent_sign)
                ++_absolute_exponent;
            else if (_absolute_exponent == 0)
            {
                _exponent_sign = false;
                _absolute_exponent = 1;
            }
            else
            {
                --_absolute_exponent;
            }
        }
        if (!_digits.empty() && _digits[0] < 0)
        {
            _sign = !_sign;
            for (int i = 0; i < _digits.size(); ++i)
            {
                _digits[i] = -_digits[i];
            }
            renormalize();
            return;
        }
    }
}

std::string DecimalDecomposition::dump() const
{
    if (isZero())
    {
        return "Zero";
    }
    std::stringbuf buffer;
    std::ostream os(&buffer);
    os << "Sign: " << (_sign ? "+" : "-") << "|";
    os << "Exponent sign: " << (_exponent_sign ? "+" : "-") << "|";
    os << "Absolute exponent: " << _absolute_exponent << "|";
    for (int i = 0; i < _digits.size(); ++i)
    {
        os << _digits[i] << "|";
    }
    return buffer.str();
}

void DecimalDecomposition::appendDigits(unsigned int newDigits,
                                        unsigned int numberOfDigits)
{
    assert(numberOfDigits < 10);
    int dividend = 1;
    for (int j = 0; j < numberOfDigits - 1; ++j)
    {
        dividend *= 10;
    }
    for (int j = numberOfDigits; j > 0; --j)
    {
        unsigned int digit = (newDigits / dividend) % 10;
        _digits.push_back(digit);
        dividend /= 10;
    }
}

void DecimalDecomposition::finalizeDigits()
{
    int i = _digits.size() - 1;
    while (i != -1 && _digits[i] == 0)
    {
        _digits.pop_back();
        --i;
    }
}

void DecimalDecomposition::reserveDigits(size_t size) { _digits.reserve(size); }

size_t DecimalDecomposition::capacityOfDigits() const
{
    return _digits.capacity();
}

void DecimalDecomposition::clearDigits() { _digits.clear(); }
