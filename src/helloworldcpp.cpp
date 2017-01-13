//============================================================================
// Name        : helloworldcpp.cpp
// Author      : somebody
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "decimalinfinite.h"
using namespace std;

#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n

const char DecimalInfinite::LogTable256[256] =
{
    -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
    LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	{
  	  DecimalInfinite d1("2");
	  cout << d1.dumpBits() << endl;
	}
	{
  	  DecimalInfinite d1("20");
	  cout << d1.dumpBits() << endl;
	}
	{
  	  DecimalInfinite d1("200");
	  cout << d1.dumpBits() << endl;
	}
	{
  	  DecimalInfinite d1("2000");
	  cout << d1.dumpBits() << endl;
	}
	{
  	  DecimalInfinite d1("20000");
	  cout << d1.dumpBits() << endl;
	}
	{
  	  DecimalInfinite d1("200000");
	  cout << d1.dumpBits() << endl;
	}
	{
  	  DecimalInfinite d1("2000000");
	  cout << d1.dumpBits() << endl;
	}
	{
  	  DecimalInfinite d1("20000000");
	  cout << d1.dumpBits() << endl;
	}
	{
  	  DecimalInfinite d1("-123456789");
	  cout << d1.dumpBits() << endl;
	}
	{
  	  DecimalInfinite d1("123456789");
	  cout << d1.dumpBits() << endl;
	}
	//d.test();
	//cout << d.toInteger() << endl;
	return 0;
}
