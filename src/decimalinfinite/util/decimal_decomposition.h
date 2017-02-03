#include <vector>

class DecimalDecomposition {
public:
	DecimalDecomposition();
	DecimalDecomposition(std::string literal);
	DecimalDecomposition(const DecimalDecomposition& other);

	std::string str();

	bool isZero() const;
	bool isPositive() const;
	bool isExponentNonNegative() const;
	unsigned int getAbsoluteExponent() const;
	int getExponent() const;
	void getDigits(std::vector<int> *digits) const;
	unsigned int getNumberOfDigits() const;
	bool isNormalized();

	void setZero();
	void setPositive(bool);
	void setExponentNonNegative(bool);
	void setExponent(int);
	void setAbsoluteExponent(unsigned int e);
	void shiftExponent(int newExponent);
	void setDigits(const std::vector<int> &digits);
	void copy(const DecimalDecomposition& other);
	void renormalize();

	void add(const DecimalDecomposition& left, const DecimalDecomposition& right, DecimalDecomposition* result);
private:
	bool _sign;
	bool _exponent_sign;
	unsigned int _absolute_exponent;
	std::vector<int> _digits;

	void encode(std::string literal);
};

