
#include <iostream>
#include <chrono>

#include <cppassist/threading/parallelfor.h>

#include <cppassist/simd/simd.h>
#include <cppassist/simd/vector.h>
#include <cppassist/simd/value.h>


int main(int /*argc*/, char* /*argv*/[])
{
    static const auto valueSize = 512ull * 512ull * 512ull * 8ull;

    cppassist::vector<float> values1(valueSize);
    cppassist::vector<float> values2(valueSize);
    std::fill(values1.valueBegin(), values1.valueEnd(), 2.0f);
    std::fill(values2.valueBegin(), values2.valueEnd(), 4.0f);

    std::cout << "Start measuring" << std::endl;

    const auto start = std::chrono::high_resolution_clock::now();

    cppassist::traverse_mt([](const cppassist::vector<float>::value_type & chunk1, cppassist::vector<float>::value_type & chunk2)
    {
        chunk2 = sqrt((sqrt(chunk1) * sqrt(chunk2) + 12.0f) * 0.125f + 5.0f);
    }, values1, values2);

    const auto end = std::chrono::high_resolution_clock::now();

    std::cout << "  End measuring: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    return 0;
}
