cmake_minimum_required (VERSION 3.1)
project (DecimalInfiniteCpp)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_C_STANDARD 11)

# Target for static library
add_library (decimal_infinite
    decimalinfinite/util/decimal_decomposition.cpp
    decimalinfinite/util/bit_sequence.cpp
    decimalinfinite/decimalinfinite.cpp
    )

# Target for main test executable
add_executable (decimal_infinite_test
    main.cpp
    decimalinfinite/util/test.cpp
    decimalinfinite/util/decimal_decomposition_test.cpp
    decimalinfinite/util/bit_sequence_test.cpp
    decimalinfinite/decimalinfinite_test.cpp
    )
target_link_libraries (decimal_infinite_test decimal_infinite)

# Setup clang-format
find_package (ClangFormat)
if(ClangFormat_FOUND)
    enable_clang_format_targets()
endif()

# Setup unit tests
enable_testing()
add_test (decimal_infinite_test decimal_infinite_test)
