#include <iostream>
#include <sstream>
#include "decimal_decomposition.h"

//#define DEBUG_BUILD

DecimalDecomposition::DecimalDecomposition() {
	encode("0");
}
DecimalDecomposition::DecimalDecomposition(std::string literal) {
	encode(literal);
}

void DecimalDecomposition::encode(std::string literal) {
	_sign = true;
	bool period = false;
	bool digit = false;
	int exponent = 0;
	for (int p = 0; p < literal.length(); ++p) {
		char c = literal.at(p);

		if (c == '0') {
			if (digit) {
				_digits.push_back(c - '0');
				if (!period) {
					++exponent;
				}
				continue;
			} else {
				if (period) {
					--exponent;
				}
				continue;
			}
		}

		if (c >= '1' && c <= '9') {
			_digits.push_back(c - '0');
			if (!period) {
				++exponent;
			}
			digit = true;
			continue;
		}

		if (c == '-') {
			if (p != 0) {
				std::cout << "Error: illegal literal." << std::endl;
				exit(0);
			}
			_sign = false;
		}

		if (c == '.') {
			if (period) {
				std::cout << "Error: illegal literal." << std::endl;
				exit(0);
			}
			if (_digits.size() == 0) {
				--exponent;
			}
			period = true;
		}
	}

	int i = _digits.size() - 1;
	while (i != -1 && _digits.at(i) == 0) {
		_digits.pop_back();
		--i;
	}

#ifdef DEBUG_BUILD
	std::cout << "Sign:" << (sign?"+":"-") << std::endl;
	std::cout << "Literal:" << literal << std::endl;
	std::cout << "Digits:" << std::endl;
	for (int i = 0; i < digits.size(); ++i) {
		std::cout << digits[i] << std::endl;
	}
	std::cout << "Exponent " << exponent << std::endl;
#endif
	_absolute_exponent = abs(exponent);
	_exponent_sign = (exponent >= 0);
#ifdef DEBUG_BUILD
	std::cout << "Exponent sign " << (exponent_sign?"+":"-") << std::endl;
	std::cout << "Absolute offset exponent " << abs_offset_exponent << std::endl;
	std::cout << "Invert exponent encoding " << (invert_exponent_encoding?"yes":"no") << std::endl;
#endif

}

bool DecimalDecomposition::isZero() const { return _digits.size() == 0; }
bool DecimalDecomposition::isPositive() const { return _sign; }
bool DecimalDecomposition::isExponentNonNegative() const { return _exponent_sign; }
uint DecimalDecomposition::getAbsoluteExponent() const { return _absolute_exponent; }
void DecimalDecomposition::getDigits(std::vector<int> *digits) const { *digits = _digits; }

void DecimalDecomposition::setZero()
{
	_digits.clear();
}

void DecimalDecomposition::setPositive(bool sign)
{
	_sign = sign;
}

void DecimalDecomposition::setExponentNonNegative(bool exponent_sign)
{
	_exponent_sign = exponent_sign;
}

void DecimalDecomposition::setAbsoluteExponent(uint e) {
  _absolute_exponent = e;
}

void DecimalDecomposition::set(const std::vector<int> &digits)
{
	_digits = digits;
}

std::string DecimalDecomposition::str()
{
	if(isZero())
	{
		return "0";
	}
	std::stringstream ss;
	if(!isPositive())
	{
		ss.put('-');
	}
	if(isExponentNonNegative())
	{
		uint exponent = getAbsoluteExponent();
		bool period = false;
		for(int i = 0; i < _digits.size(); ++i)
		{
			ss.put('0' + _digits.at(i));
			if(!period) {
				--exponent;
			}
			if(exponent == 0 && !period && i != _digits.size() - 1)
			{
				ss.put('.');
				period = true;
			}
		}
		while(exponent > 0)
		{
			ss.put('0');
			--exponent;
		}
	} else {
		uint exponent = getAbsoluteExponent();
		ss.put('0');
		ss.put('.');
		while(exponent > 1)
		{
			ss.put('0');
			--exponent;
		}
		for(int i = 0; i < _digits.size(); ++i)
		{
			ss.put('0' + _digits.at(i));
		}
	}
	return ss.str();
}
