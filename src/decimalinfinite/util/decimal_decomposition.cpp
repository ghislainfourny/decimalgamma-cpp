#include "decimal_decomposition.h"

#include <iostream>
#include <sstream>

//#define DEBUG_BUILD

DecimalDecomposition::DecimalDecomposition() {
	encode("0");
}

DecimalDecomposition::DecimalDecomposition(const char* const literal) {
	encode(literal);
}

DecimalDecomposition::DecimalDecomposition(const DecimalDecomposition& other)
{
	copy(other);
}

void DecimalDecomposition::encode(const char* const literal) {
	_sign = true;
	bool period = false;
	bool digit = false;
	int exponent = -1;
	for (const char* p = literal; *p != '\0'; ++p) {
		char c = *p;

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
			if (p != literal) {
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
unsigned int DecimalDecomposition::getAbsoluteExponent() const { return _absolute_exponent; }

int DecimalDecomposition::getExponent() const {
	if(isExponentNonNegative())
		return _absolute_exponent;
	else
		return - _absolute_exponent;
}

void DecimalDecomposition::getDigits(std::vector<int> *digits) const { *digits = _digits; }

void DecimalDecomposition::setZero()
{
	_digits.clear();
}

unsigned int DecimalDecomposition::getNumberOfDigits() const
{
	return _digits.size();
}

void DecimalDecomposition::setPositive(bool sign)
{
	_sign = sign;
}

void DecimalDecomposition::setExponentNonNegative(bool exponent_sign)
{
	_exponent_sign = exponent_sign;
}

void DecimalDecomposition::setAbsoluteExponent(unsigned int e) {
  _absolute_exponent = e;
}

void DecimalDecomposition::setExponent(int e) {
	if(e >= 0)
	{
    _absolute_exponent = e;
		setExponentNonNegative(true);
	} else
	{
		_absolute_exponent = -e;
		setExponentNonNegative(false);
	}
}

void DecimalDecomposition::setDigits(const std::vector<int> &digits)
{
	_digits = digits;
	int i = _digits.size() - 1;
	while (i != -1 && _digits.at(i) == 0) {
		_digits.pop_back();
		--i;
	}
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
		int exponent = getAbsoluteExponent();
		bool period = false;
		for(int i = 0; i < _digits.size(); ++i)
		{
			ss.put('0' + _digits.at(i));
			if(!period) {
				--exponent;
			}
			if(exponent == -1 && !period && i != _digits.size() - 1)
			{
				ss.put('.');
				period = true;
			}
		}
		while(exponent > -1)
		{
			ss.put('0');
			--exponent;
		}
	} else {
		unsigned int exponent = getAbsoluteExponent();
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

void DecimalDecomposition::copy(const DecimalDecomposition& other)
{
	if(other.isZero())
	{
		setZero();
		return;
	};
	setAbsoluteExponent(other.getAbsoluteExponent());
	setPositive(other.isPositive());
	setExponentNonNegative(other.isExponentNonNegative());
	std::vector<int> digits;
	other.getDigits(&digits);
	setDigits(digits);
}

void DecimalDecomposition::shiftExponent(int newExponent)
{
	int exponent = getExponent();
  if(newExponent < exponent)
  {
  	std::cerr << "Cannot shift to lower exponent." << std::endl;
  }
  int shift = newExponent - exponent;
  for(int i = 0; i < shift; ++i)
  {
  	_digits.insert(_digits.begin(), 0);
  }
  setExponent(newExponent);
}

void DecimalDecomposition::add(const DecimalDecomposition& left, const DecimalDecomposition& right, DecimalDecomposition* result)
{
	if(left.isZero()) {
		 result = new DecimalDecomposition(right);
		 return;
	}
	if(right.isZero()) {
		 result = new DecimalDecomposition(left);
		 return;
	}
  int exponent_left = left.getExponent();
  int exponent_right = right.getExponent();
  DecimalDecomposition* other;
  if(exponent_left > exponent_right) {
    result = new DecimalDecomposition(left);
    other = new DecimalDecomposition(right);
    other->shiftExponent(exponent_left);
  } else
  {
    result = new DecimalDecomposition(right);
    other = new DecimalDecomposition(left);
    other->shiftExponent(exponent_right);
  }
  std::vector<int> digits;
  result->getDigits(&digits);
  std::vector<int> digitsOther;
  other->getDigits(&digitsOther);
  if(digits.size() < digitsOther.size())
  {
  	digits.resize(digitsOther.size());
  }
  for(int i = 0; i < digits.size(); ++i)
  {
  	digits[i] += digitsOther[i];
  }
  result->setDigits(digits);
  result->renormalize();
  delete other;
}

bool DecimalDecomposition::isNormalized()
{
	for(std::vector<int>::iterator it = _digits.begin(); it != _digits.end(); ++it)
	{
		if(*it < 0 || *it > 9)
			return false;
	}
	return true;
}


void DecimalDecomposition::renormalize()
{
	int carry = 0;
	for(std::vector<int>::reverse_iterator it = _digits.rbegin(); it != _digits.rend(); ++it)
	{
		*it += carry;
		carry = *it / 10;
		*it = *it % 10;
	}
	if(_exponent_sign)
	{
		while (carry != 0) {
			++_absolute_exponent;
			_digits.insert(_digits.begin(), carry % 10);
			carry /= 10;
		}
	}
	else
	{
		while (carry != 0) {
			if(_absolute_exponent == 0)
			{
				_absolute_exponent = 1;
				_exponent_sign = true;
			}
			else {
				--_absolute_exponent;
			}
			_digits.insert(_digits.begin(), carry % 10);
			carry /= 10;
		}
	}
}
