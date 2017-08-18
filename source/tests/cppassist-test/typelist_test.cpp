
#include <gmock/gmock.h>

#include <cppassist/typelist/TypeList.h>


class typelist_test : public testing::Test
{
public:
    typelist_test()
    : intCallcount(0)
    , floatCallcount(0)
    , boolCallcount(0)
    {
    }

    template <typename T>
    void apply()
    {
        if (typeid(T) == typeid(int))
        {
            ++intCallcount;
        }

        if (typeid(T) == typeid(float))
        {
            ++floatCallcount;
        }

        if (typeid(T) == typeid(bool))
        {
            ++boolCallcount;
        }
    }
protected:
    int intCallcount;
    int floatCallcount;
    int boolCallcount;
};


TEST_F(typelist_test, ListApply)
{
    using list = cppassist::TypeList<int, float, bool>;

    list::apply(*this);

    ASSERT_EQ(intCallcount, 1);
    ASSERT_EQ(floatCallcount, 1);
    ASSERT_EQ(boolCallcount, 1);
}
