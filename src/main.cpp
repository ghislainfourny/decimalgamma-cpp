#include "decimalinfinite/decimalinfinite_test.h"
#include "decimalinfinite/util/decimal_decomposition_test.h"
#include "decimalinfinite/util/bit_sequence_test.h"

#include <iostream>
using namespace std;

int main() {
	{
		BitSequenceTest t;
		t.run();
	}
	{
		DecimalDecompositionTest t;
		t.run();
	}
	{
		DecimalInfiniteTest t;
		t.run();
	}
	return 0;
}
