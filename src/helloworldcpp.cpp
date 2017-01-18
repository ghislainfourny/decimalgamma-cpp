//============================================================================
// Name        : helloworldcpp.cpp
// Author      : somebody
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "decimalinfinite_test.h"
#include "decimal_decomposition_test.h"
using namespace std;

int main () {
	DecimalInfiniteTest t;
	t.run();
	DecimalDecompositionTest u;
	u.run();
	return 0;
}
