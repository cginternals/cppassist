
#include <cstdint>
#include <thread>

#include <gmock/gmock.h>

#include <cppassist/threading/parallelfor.h>


using namespace cppassist;


class parallelFor_test : public testing::Test
{
public:
    parallelFor_test()
    {
    }
};


TEST_F(parallelFor_test, ParellelIncrementVector)
{
    const auto start = 3u;
    const auto end = 27u;
    auto vec = std::vector<int>(27, 0);

    parallelFor(start, end, [&vec] (int i) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1000000});
        vec[i] = 1;
    });

    for (auto i = start; i < end; ++i)
    {
        ASSERT_EQ(vec[i], 1);
    }
}

TEST_F(parallelFor_test, SequentialIncrementVector)
{
    const auto start = 3u;
    const auto end = 27u;
    auto vec = std::vector<int>(27, 0);

    sequentialFor(start, end, [&vec] (int i) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1000000});
        vec[i] = 1;
    });

    for (auto i = start; i < end; ++i)
    {
        ASSERT_EQ(vec[i], 1);
    }
}

TEST_F(parallelFor_test, ParellelSequentialEquality)
{
    const auto start = 3u;
    const auto end = 27u;
    auto vec1 = std::vector<int>(27, 0);
    auto vec2 = std::vector<int>(27, 0);

    parallelFor(start, end, [&vec1] (int i) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1000000});
        vec1[i] = 1;
    });

    sequentialFor(start, end, [&vec2] (int i) {
        std::this_thread::sleep_for(std::chrono::nanoseconds{1000000});
        vec2[i] = 1;
    });

    for (auto i = start; i < end; ++i)
    {
        ASSERT_EQ(vec1[i], vec2[i]);
    }
}

TEST_F(parallelFor_test, SizeTCompilation)
{
    size_t start = 0;
    size_t end = 1;

    parallelFor(start, end, [] (size_t /*i*/) {
        SUCCEED();
    });
}

/*
TEST_F(parallelFor_test, Uint8Compilation)
{
    std::uint8_t start = 0;
    std::uint8_t end = 1;

    parallelFor(start, end, [] (int i) {
        SUCCEED();
    });
}

TEST_F(parallelFor_test, Uint16Compilation)
{
    std::uint16_t start = 0;
    std::uint16_t end = 1;

    parallelFor(start, end, [] (int i) {
        SUCCEED();
    });
}
*/

TEST_F(parallelFor_test, Uint32Compilation)
{
    std::uint32_t start = 0;
    std::uint32_t end = 1;

    parallelFor(start, end, [] (std::uint32_t /*i*/) {
        SUCCEED();
    });
}

TEST_F(parallelFor_test, Uint64Compilation)
{
    std::uint64_t start = 0;
    std::uint64_t end = 1;

    parallelFor(start, end, [] (std::uint64_t /*i*/) {
        SUCCEED();
    });
}

TEST_F(parallelFor_test, UintCompilation)
{
    unsigned int start = 0;
    unsigned int end = 1;

    parallelFor(start, end, [] (unsigned int /*i*/) {
        SUCCEED();
    });
}

/*
TEST_F(parallelFor_test, Int8Compilation)
{
    std::int8_t start = 0;
    std::int8_t end = 1;

    parallelFor(start, end, [] (int i) {
        SUCCEED();
    });
}


TEST_F(parallelFor_test, Int16Compilation)
{
    std::int16_t start = 0;
    std::int16_t end = 1;

    parallelFor(start, end, [] (int i) {
        SUCCEED();
    });
}


TEST_F(parallelFor_test, Int32Compilation)
{
    std::int32_t start = 0;
    std::int32_t end = 1;

    parallelFor(start, end, [] (int i) {
        SUCCEED();
    });
}

TEST_F(parallelFor_test, Int64Compilation)
{
    std::int64_t start = 0;
    std::int64_t end = 1;

    parallelFor(start, end, [] (int i) {
        SUCCEED();
    });
}

TEST_F(parallelFor_test, IntCompilation)
{
    int start = 0;
    int end = 1;

    parallelFor(start, end, [] (int i) {
        SUCCEED();
    });
}
*/
