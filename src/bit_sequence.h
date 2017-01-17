#include <vector>
#include <iomanip>

//#define DEBUG_APPEND
//#define DEBUG_BUILD

class BitSequence {
public:
	BitSequence() {
		_next = 0;
	}

	BitSequence(const BitSequence &other) {
		_next = other._next;
		_raw_bits = other._raw_bits;
	}

	void appendBits(uint i, int n);

	std::string toString();

private:
	std::vector<int> _raw_bits;
	int _next;
	static const int BUFFER_SIZE = sizeof(int) * 8;

};
