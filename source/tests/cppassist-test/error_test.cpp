
#include <gmock/gmock.h>

#include <cppassist/error/Error.h>
#include <cppassist/error/Result.h>


using namespace cppassist;


// This is really more a compilation test


class error_test : public testing::Test
{
public:
    error_test()
    {
    }

    cppassist::Result<void> checkForValidity(bool check)
    {
        if (check)
        {
            return cppassist::ok();
        }
        else
        {
            return cppassist::error<void>("Invalid");
        }
    }

    cppassist::Result<std::int64_t> faculty(int n)
    {
        if (n < 0 || n > 20)
        {
            return cppassist::error<std::int64_t>("n out of range");
        }

        if (n < 2)
        {
            return n;
        }

        std::int64_t result = 1;
        while (n > 1)
        {
            result *= n;
            --n;
        }

        return result;
    }
};


TEST_F(error_test, Success)
{
    const auto result = checkForValidity(true);

    ASSERT_TRUE(result.isValid());
}

TEST_F(error_test, Result)
{
    const auto result = faculty(4);

    ASSERT_TRUE(result.isValid());
    ASSERT_EQ(24, result.value());
}


TEST_F(error_test, Failure)
{
    const auto result = checkForValidity(false);

    ASSERT_FALSE(result.isValid());
    ASSERT_NE("", result.error().message());
}

TEST_F(error_test, Error)
{
    const auto result = faculty(30);

    ASSERT_FALSE(result.isValid());
    ASSERT_NE("", result.error().message());
}
