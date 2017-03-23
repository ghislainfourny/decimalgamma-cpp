#include "decimalinfinite/decimalinfinite_test.h"
#include "decimalinfinite/util/bit_sequence_test.h"
#include "decimalinfinite/util/decimal_decomposition_test.h"

#include <iostream>
using namespace std;

int main()
{
    std::cout << "Bit sequence tests." << std::endl;
    {
        BitSequenceTest t;
        t.run();
    }
    std::cout << "Decomposition tests." << std::endl;
    {
        DecimalDecompositionTest t;
        t.run();
    }
    std::cout << "Encoding tests." << std::endl;
    {
        DecimalInfiniteTest t;
        t.run();
    }
    return 0;
}
