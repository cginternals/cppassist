
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
    std::string str = "char";

    auto val = string::fromString<char>(str);

    ASSERT_EQ(typeid(char), typeid(val));

    auto test = static_cast<char>(0);

    ASSERT_EQ(test, val);

    str = "65";

    val = string::fromString<char>(str);

    test = 'A';

    ASSERT_EQ(test, val);
}

TEST_F(conversion_test, fromString_uchar)
{

    std::string str = "uchar";

    auto val = string::fromString<unsigned char>(str);

    ASSERT_EQ(typeid(unsigned char), typeid(val));

    auto test = static_cast<unsigned char>(0);

    ASSERT_EQ(test, val);

    str = "66";

    val = string::fromString<char>(str);

    test = static_cast<unsigned char>('B');

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
    std::string str = "6.23";

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

TEST_F(conversion_test, toString_charPtr)
{
    const char * val = "char *";

    auto str = string::toString(val);

    ASSERT_EQ(typeid(std::string), typeid(str));
    ASSERT_EQ("char *", str);
}

TEST_F(conversion_test, toString_char)
{
    const char val = 'A';

    auto str = string::toString(val);

    ASSERT_EQ(typeid(std::string), typeid(str));
    ASSERT_EQ("65", str);
}

TEST_F(conversion_test, toString_uchar)
{
    const unsigned char val = 'B';

    auto str = string::toString(val);

    ASSERT_EQ(typeid(std::string), typeid(str));
    ASSERT_EQ("66", str);
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

TEST_F(conversion_test, toLower)
{
    const std::string input = "toLower";

    const auto output = string::toLower(input);

    ASSERT_EQ("tolower", output);
}

TEST_F(conversion_test, toLower_uniRef)
{
    const auto output = string::toLower("toLower");

    ASSERT_EQ("tolower", output);
}

TEST_F(conversion_test, toUpper)
{
    const std::string input = "toUpper";

    const auto output = string::toUpper(input);

    ASSERT_EQ("TOUPPER", output);
}

TEST_F(conversion_test, toUpper_uniRef)
{
    const auto output = string::toUpper("toUpper");

    ASSERT_EQ("TOUPPER", output);
}
