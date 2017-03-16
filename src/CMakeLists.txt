cmake_minimum_required (VERSION 3.1)
project (DecimalInfiniteCpp)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_C_STANDARD 11)

add_executable (decimal_infinite
    main.cpp
    decimalinfinite/util/test.cpp
    decimalinfinite/util/decimal_decomposition.cpp
    decimalinfinite/util/decimal_decomposition_test.cpp
    decimalinfinite/util/bit_sequence.cpp
    decimalinfinite/util/bit_sequence_test.cpp
    decimalinfinite/decimalinfinite.cpp
    decimalinfinite/decimalinfinite_test.cpp
    )

enable_testing()
add_test (decimal_infinite decimal_infinite)
