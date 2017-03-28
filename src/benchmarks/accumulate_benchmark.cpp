#include <algorithm>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

#include "decimalinfinite/decimalinfinite.h"

/**
 * Generate vector of random numbers following the given distribution.
 */
template <typename T, typename DistrT>
std::vector<T> generate(int N, DistrT distr)
{
    std::mt19937 engine;
    std::vector<T> data(N);
    for (auto &v : data) v = distr(engine);
    return data;
}

/**
 * Reimplementation of std::accumulate where T.operator+= is used instead of
 * operator+(T, T).
 */
template <class InputIt, class T>
T inplace_accumulate(InputIt first, InputIt last, T init)
{
    for (; first != last; ++first)
    {
        init += *first;
    }
    return init;
}

template <typename InputType, class AccumulatorType>
void accumulate_benchmark(const size_t Nmax, const char *const type_name)
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::nanoseconds;

    for (size_t N = 1; N <= Nmax; N *= 2)
    {
        // Generate data
        auto data = generate<InputType>(
                N, std::uniform_real_distribution<InputType>(1., 2.));

        // Run accumulate
        auto const start = high_resolution_clock::now();
        AccumulatorType a = inplace_accumulate(data.begin(), data.end(),
                                               AccumulatorType(InputType(0)));
        auto const end = high_resolution_clock::now();

        // Print result
        auto const diff = duration_cast<nanoseconds>(end - start).count();
        std::printf("{ \"type\": \"%s\", \"N\": %zi, \"runtime\": %zi }\n",
                    type_name, N, diff);
    }
}

int main()
{
    const int Nmax = 1 * 1024 * 1024;
    accumulate_benchmark<float, float>(Nmax, "float");
    accumulate_benchmark<float, di::decimal>(Nmax, "decimalinfinite");
}
