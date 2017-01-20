
#include <gmock/gmock.h>

#include <cppassist/string/conversion.h>


using namespace cppassist;


class conversion_test : public testing::Test
{
public:
    conversion_test()
    {
    }
};


TEST_F(conversion_test, fromString_char)
{
    const std::string str = "char";

    auto val = string::fromString<char>(str);

    ASSERT_EQ(typeid(char), typeid(val));

    auto test = static_cast<char>(0);

    ASSERT_EQ(test, val);
}

TEST_F(conversion_test, fromString_uchar)
{

    const std::string str = "uchar";

    auto val = string::fromString<unsigned char>(str);

    ASSERT_EQ(typeid(unsigned char), typeid(val));

    auto test = static_cast<unsigned char>(0);

    ASSERT_EQ(test, val);
}

TEST_F(conversion_test, fromString_int)
{
    std::string str = "-6";

    auto val = string::fromString<int>(str);

    ASSERT_EQ(typeid(int), typeid(val));
    ASSERT_EQ(-6, val);

    str = "asd";

    val = string::fromString<int>(str);

    ASSERT_EQ(typeid(int), typeid(val));
    ASSERT_EQ(0, val);
}

TEST_F(conversion_test, fromString_uint)
{
    std::string str = "6";

    auto val = string::fromString<unsigned int>(str);

    ASSERT_EQ(typeid(unsigned int), typeid(val));
    ASSERT_EQ(6u, val);

    str = "asd";

    val = string::fromString<unsigned int>(str);

    ASSERT_EQ(typeid(unsigned int), typeid(val));
    ASSERT_EQ(0u, val);
}

TEST_F(conversion_test, fromString_float)
{
    std::string str = "6.23f";

    auto val = string::fromString<float>(str);

    ASSERT_EQ(typeid(float), typeid(val));
    ASSERT_EQ(6.23f, val);

    str = "asd";

    val = string::fromString<float>(str);

    ASSERT_EQ(typeid(float), typeid(val));
    ASSERT_EQ(0, val);
}

TEST_F(conversion_test, fromString_double)
{
    std::string str = "6.23";

    auto val = string::fromString<double>(str);

    ASSERT_EQ(typeid(double), typeid(val));
    ASSERT_EQ(6.23, val);

    str = "asd";

    val = string::fromString<double>(str);

    ASSERT_EQ(typeid(double), typeid(val));
    ASSERT_EQ(0, val);
}

TEST_F(conversion_test, fromString_bool)
{
    std::string str = "0";

    auto val = string::fromString<bool>(str);

    ASSERT_EQ(typeid(bool), typeid(val));
    ASSERT_FALSE(val);

    str = "1";

    val = string::fromString<bool>(str);

    ASSERT_EQ(typeid(bool), typeid(val));
    ASSERT_TRUE(val);

    str = "true";

    val = string::fromString<bool>(str);

    ASSERT_EQ(typeid(bool), typeid(val));
    ASSERT_TRUE(val);

    str = "false";

    val = string::fromString<bool>(str);

    ASSERT_EQ(typeid(bool), typeid(val));
    ASSERT_FALSE(val);

    str = "asd";

    val = string::fromString<bool>(str);

    ASSERT_EQ(typeid(bool), typeid(val));
    ASSERT_TRUE(val);
}

TEST_F(conversion_test, toString_char)
{
    const char * val = "character";

    auto str = string::toString(val);

    ASSERT_EQ(typeid(std::string), typeid(str));
    ASSERT_EQ("character", str);
}

TEST_F(conversion_test, toString_uchar)
{
    const unsigned char * val = (unsigned char *) "unsigned character";

    auto str = string::toString(val);

    ASSERT_EQ(typeid(std::string), typeid(str));
    ASSERT_EQ("unsigned character", str);
}

TEST_F(conversion_test, toString_int)
{
    const int val = 5;

    auto str = string::toString(val);

    ASSERT_EQ(typeid(std::string), typeid(str));
    ASSERT_EQ("5", str);
}

TEST_F(conversion_test, toString_uint)
{
    const unsigned int val = 5;

    auto str = string::toString(val);

    ASSERT_EQ(typeid(std::string), typeid(str));
    ASSERT_EQ("5", str);
}

TEST_F(conversion_test, toString_float)
{
    const float val = 0.32f;

    auto str = string::toString(val);

    ASSERT_EQ(typeid(std::string), typeid(str));
    ASSERT_EQ("0.32", str);
}

TEST_F(conversion_test, toString_double)
{
    const double val = 0.32;

    auto str = string::toString(val);

    ASSERT_EQ(typeid(std::string), typeid(str));
    ASSERT_EQ("0.32", str);
}

TEST_F(conversion_test, toString_bool)
{
    const bool val = true;

    auto str = string::toString(val);

    ASSERT_EQ(typeid(std::string), typeid(str));
    ASSERT_EQ("true", str);
}
