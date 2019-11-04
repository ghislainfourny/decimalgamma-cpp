cmake_minimum_required (VERSION 3.1)

# Set up build type, Release as default
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "No build type set, defaulting to Release")
endif()
set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}"
    CACHE STRING
    "Choose the type of build. Options are: <empty>, Debug, Release, RelWithDebInfo, MinSizeRel.")
message(STATUS "Using build type: ${CMAKE_BUILD_TYPE}")

# Set up project, cmake, and default options
project (DecimalGammaCpp)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")

include_directories("${PROJECT_SOURCE_DIR}")

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_C_STANDARD 11)

# Setup google test suite
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../3rdparty/gtest" gtest)
set(GTEST_LIBRARIES gtest gtest_main)

# Target for static library
add_library (decimal_infinite
    decimalgamma/util/decimal_decomposition.cpp
    decimalgamma/util/bit_sequence.cpp
    decimalgamma/decimalgamma.cpp
    )

# Target for test executable
add_executable(decimalgamma_tests
    decimalgamma/util/bit_sequence_test.cpp
    decimalgamma/util/decimal_decomposition_test.cpp
    decimalgamma/decimalgamma_test.cpp
    )
target_link_libraries(decimalgamma_tests ${GTEST_LIBRARIES} decimal_infinite)


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
add_test (decimalgamma_tests decimalgamma_tests)
