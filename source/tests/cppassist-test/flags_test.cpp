
#include <gmock/gmock.h>

#include <cppassist/flags/Flags.h>

// This is really more a compilation test


class flags_test : public testing::Test
{
public:
    flags_test()
    {
    }
};

enum class MyEnum : unsigned int {
    Value1 = 1,
    Value2 = 2,
    Value3 = 4
};


TEST_F(flags_test, EmptyFlags)
{
    auto f = cppassist::Flags<MyEnum>();

    ASSERT_FALSE(f);
}

TEST_F(flags_test, SingleFlags)
{
    auto f = cppassist::Flags<MyEnum>(MyEnum::Value1);

    ASSERT_TRUE(f);
}

TEST_F(flags_test, MultipleFlags)
{
    auto f = cppassist::Flags<MyEnum>({ MyEnum::Value1, MyEnum::Value2 });

    ASSERT_TRUE(f);
}

TEST_F(flags_test, FlagsOr)
{
    auto f = MyEnum::Value1 | MyEnum::Value2;

    ASSERT_TRUE(f);
}

TEST_F(flags_test, MultipleFlagsOr)
{
    auto f = MyEnum::Value1 | MyEnum::Value2 | MyEnum::Value3;

    ASSERT_TRUE(f);
}

TEST_F(flags_test, FlagsAnd)
{
    auto f = MyEnum::Value1 & MyEnum::Value2;

    ASSERT_FALSE(f);
}

TEST_F(flags_test, MultipleFlagsAnd)
{
    auto f = MyEnum::Value1 & MyEnum::Value2 & MyEnum::Value3;

    ASSERT_FALSE(f);
}

TEST_F(flags_test, FlagsXor)
{
    auto f = MyEnum::Value1 ^ MyEnum::Value2;

    ASSERT_TRUE(f);
}

TEST_F(flags_test, MultipleFlagsXor)
{
    auto f = MyEnum::Value1 ^ MyEnum::Value2 ^ MyEnum::Value3;

    ASSERT_TRUE(f);
}

TEST_F(flags_test, BooleanContext)
{
    auto f = MyEnum::Value1 | MyEnum::Value2;

    if (f & MyEnum::Value1)
    {
        SUCCEED();
    }
}
