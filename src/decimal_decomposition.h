#include <vector>

class DecimalDecomposition {
public:
	DecimalDecomposition();
	DecimalDecomposition(std::string literal);

	std::string str();

	bool isZero() const;
	bool isPositive() const;
	bool isExponentNonNegative() const;
	uint getAbsoluteExponent() const;
	void getDigits(std::vector<int> *digits) const;

	void setZero();
	void setPositive(bool);
	void setExponentNonNegative(bool);
	void setAbsoluteExponent(uint e);
	void set(const std::vector<int> &digits);
private:
	bool _sign;
	bool _exponent_sign;
	uint _absolute_exponent;
	std::vector<int> _digits;

	void encode(std::string literal);
};

