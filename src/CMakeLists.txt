cmake_minimum_required (VERSION 3.1)
project (DecimalInfiniteCpp)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")

include_directories("${PROJECT_SOURCE_DIR}")

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_C_STANDARD 11)

# Setup google test suite
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../3rdparty/gtest" gtest)
set(GTEST_LIBRARIES gtest gtest_main)

# Target for static library
add_library (decimal_infinite
    decimalinfinite/util/decimal_decomposition.cpp
    decimalinfinite/util/bit_sequence.cpp
    decimalinfinite/decimalinfinite.cpp
    )

# Target for test executable
add_executable(decimalinfinite_tests
    decimalinfinite/util/bit_sequence_test.cpp
    decimalinfinite/util/decimal_decomposition_test.cpp
    decimalinfinite/decimalinfinite_test.cpp
    )
target_link_libraries(decimalinfinite_tests ${GTEST_LIBRARIES} decimal_infinite)


# Targets for microbenchmarks
add_executable (accumulate_bench
    benchmarks/accumulate_benchmark.cpp
    )
target_link_libraries (accumulate_bench decimal_infinite)

# Setup clang-format
find_package (ClangFormat 4.0)
if(ClangFormat_FOUND)
    enable_clang_format_targets()
endif()

# Setup unit tests
enable_testing()
add_test (decimalinfinite_tests decimalinfinite_tests)
