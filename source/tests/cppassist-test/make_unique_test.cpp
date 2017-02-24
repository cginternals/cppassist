
#include <gmock/gmock.h>

#include <cppassist/memory/make_unique.h>


using namespace cppassist;


// This is really more a compilation test


class make_unique_test : public testing::Test
{
public:
    make_unique_test()
    {
    }
};


TEST_F(make_unique_test, Single)
{
    auto i = make_unique<int>(6);
    auto s = make_unique<std::string>(5, 'x');

    ASSERT_NE(nullptr, i);
    ASSERT_NE(nullptr, s);
    EXPECT_EQ(6, *i);
    EXPECT_EQ("xxxxx", *s);
}


TEST_F(make_unique_test, Array)
{
    auto i = make_unique<int[]>(6);

    ASSERT_NE(nullptr, i);
}
