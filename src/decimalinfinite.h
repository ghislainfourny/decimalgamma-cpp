#include <vector>
#include <sstream>
#include <iomanip>

//#define DEBUG_APPEND
//#define DEBUG_BUILD

class DecimalInfinite
{
public:
	DecimalInfinite()
	{
        _next = 0;
	}

	DecimalInfinite(const DecimalInfinite &other)
	{
		for(int i = 0; i < other._raw_bits.size(); ++i)
		{
		  _raw_bits.push_back(other._raw_bits[i]);
		}
	}

	DecimalInfinite(int i)
	{
      _next = 0;
	}

	DecimalInfinite(std::string literal)
	{
      _next = 0;
      bool hasSign = false;
      bool sign = true;
      if(literal.at(0) == '-')
      {
    	  sign = false;
    	  writeBits(0b00, 2);
    	  hasSign = true;
      } else if(literal.at(0) == '+'){
    	  sign = true;
    	  writeBits(0b10, 2);
    	  hasSign = true;
      } else {
    	  sign = true;
    	  writeBits(0b10, 2);
      }
      unsigned int exponent = literal.find('.');
      if(exponent == -1)
      {
    	  exponent = literal.length();
      }
      if(hasSign)
      {
    	  exponent -= 1;
      }
#ifdef DEBUG_BUILD
      std::cout << "Exponent " << exponent << std::endl;
#endif
      exponent += 2;
#ifdef DEBUG_BUILD
      std::cout << "Exponent " << exponent << std::endl;
#endif
      unsigned int le = log2(exponent);
#ifdef DEBUG_BUILD
      std::cout << "Log2 exponent: " << le << std::endl;
#endif
	  writeBits((1 << le) - 2, le);
	  writeBits(exponent - (1 << le), le);
	  int first = literal.at(0) - '0';
	  int next = 1;
	  if(hasSign) {
		  first = literal.at(1) - '0';
		  int next = 2;
	  }
	  if(!sign)
	  {
        first = 9 - first;
	  }
	  writeBits(first, 4);
	  while(next < literal.length())
	  {
		  int a = 0, b = 0, c = 0;
		  if(literal.at(next) == '.')
		  {
			  ++next;
		  }
		  a = literal.at(next++) - '0';
		  if(next < literal.length()) {
		    b = literal.at(next++) - '0';
		  }
		  if(next < literal.length()) {
  		    c = literal.at(next++) - '0';
		  }
		  int towrite = 100 * a + 10 * b + c;
		  if(!sign)
		  {
            towrite = 999 - towrite;
		  }
		  writeBits(towrite, 10);
	  }
	}

	int toInteger() const {
		if(_raw_bits.size() == 1 && _raw_bits[0] == 0X80000000)
		{
			return 0;
		} else {
			std::cout << "error" << std::endl;
			exit(0);
		}
	}

	void writeBits(uint i, int n)
	{
      if((i & ((-1) << n)) > 0) {
    	  std::cout << "Invalid parameters (" << n << " bits expected) :" << std::bitset<BUFFER_SIZE>(i) << std::endl;
    	  exit(0);
      }
#ifdef DEBUG_APPEND
	  std::cout << "Before : " << dumpBits() << std::endl;
	  std::cout << "Writing " << n << " - " << std::bitset<BUFFER_SIZE>(i) << std::endl;
#endif
      int buffer0 = (_next - 1) / BUFFER_SIZE;
      int offset = _next % BUFFER_SIZE;
      int buffer1 = buffer0 + 1;
      bool needs_buffer_1 = (_next + n - 1) / BUFFER_SIZE > (_next - 1)/ BUFFER_SIZE;
#ifdef DEBUG_APPEND
	  std::cout << "Next: " << _next << std::endl;
	  std::cout << "Buffer0: " << buffer0 << std::endl;
	  std::cout << "Buffer1: " << buffer1 << std::endl;
	  std::cout << "Offset: " << offset << std::endl;
	  std::cout << "Needs second buffer: " << needs_buffer_1 << std::endl;
#endif

      int size = _raw_bits.size();
#ifdef DEBUG_APPEND
	  std::cout << "Size: " << size << std::endl;
#endif
      while(_next + n > size * BUFFER_SIZE)
      {
    	  _raw_bits.push_back(0);
    	  size = _raw_bits.size();
      }

	  int shift = BUFFER_SIZE - n - offset;
#ifdef DEBUG_APPEND
	  std::cout << "Shift: " << shift << std::endl;
#endif
      if(!needs_buffer_1)
      {
		  if(shift < 0) {
			  std::cout << "Error: negative shift!" << std::endl;
			  exit(0);
		  }
#ifdef DEBUG_APPEND
		  std::cout << "shift " << shift << std::endl;
		  std::cout << "OR-ing " << std::bitset<BUFFER_SIZE>((i << shift)) << std::endl;
#endif
		  _raw_bits[buffer0] |= i << shift;
		  _next += n;
#ifdef DEBUG_APPEND
		  std::cout << "After : " << _next << " - " << dumpBits() << std::endl;
#endif
      } else {
		  shift = 0 - shift;
    	  if(offset > 0) {
#ifdef DEBUG_APPEND
    		  std::cout << "Shift: " << shift << std::endl;
#endif
    		  if(shift < 0) {
    			  std::cout << "Error: negative shift! " << shift << std::endl;
    			  exit(0);
    		  }
#ifdef DEBUG_APPEND
    		  std::cout << "shift " << shift << std::endl;
    		  std::cout << "OR-ing " << std::bitset<BUFFER_SIZE>((i >> shift)) << std::endl;
#endif
    		  _raw_bits[buffer0] |= i >> shift;
#ifdef DEBUG_APPEND
    		  std::cout << "After : " << _next << " - " << dumpBits() << std::endl;
#endif
    	  }
		  shift = BUFFER_SIZE - shift;
#ifdef DEBUG_APPEND
		  std::cout << "shift " << shift << std::endl;
		  std::cout << "OR-ing " << std::bitset<BUFFER_SIZE>((i << shift)) << std::endl;
#endif
		  _raw_bits[buffer1] |= i << shift;
		  _next += n;
#ifdef DEBUG_APPEND
		  std::cout << "After : " << _next << " - " << dumpBits() << std::endl;
#endif
      }
	}

	std::string dumpBits()
	{
		std::stringstream output;
		for(int i = 0; i < _raw_bits.size(); ++i)
		{
          output << std::bitset<BUFFER_SIZE>(_raw_bits[i]);
		}
		return output.str();
	}

	void test()
	{
		writeBits(0b10, 2);
		std::cout << dumpBits() << std::endl;
		writeBits(0b1111111111110, 13);
		std::cout << dumpBits() << std::endl;
		writeBits(0b1111111111110, 13);
		std::cout << dumpBits() << std::endl;
		writeBits(0b1111111111110, 13);
		std::cout << dumpBits() << std::endl;
		writeBits(0b1111111111110, 13);
		std::cout << dumpBits() << std::endl;
		writeBits(0b1111111111110, 13);
		std::cout << dumpBits() << std::endl;
		writeBits(0b1111111111110, 13);
		std::cout << dumpBits() << std::endl;
		writeBits(0b1111111111110, 13);
		std::cout << dumpBits() << std::endl;
		writeBits(0b110, 3);
		std::cout << dumpBits() << std::endl;
		writeBits(0b1111111111111111111111111111110, 31);
		std::cout << dumpBits() << std::endl;
		writeBits(0b0, 1);
		std::cout << dumpBits() << std::endl;
		writeBits(0b1, 1);
		std::cout << dumpBits() << std::endl;
	}

private:
	std::vector<int> _raw_bits;
	int _next;
	static const int BUFFER_SIZE = sizeof(int) * 8;

	static const char LogTable256[256];

	static unsigned int log2(unsigned int v)
	{
		register unsigned int tt;
		if (tt = v >> 24)
		{
		  return 24 + LogTable256[tt];
		}
		else if (tt = v >> 16)
		{
			return 16 + LogTable256[tt];
		}
		else if (tt = v >> 8)
		{
			return 8 + LogTable256[tt];
		}
		else
		{
			return LogTable256[v];
		}
	}


};
