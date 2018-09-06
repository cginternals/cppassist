
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

// from https://unicode-table.com/
// U+1D11E - Musical Symbol G Clef
// Encoding      Hex         Dec Bytes
// UTF-8     F0 9D 84 9E  240 157 132 158
// UTF-16BE  D8 34 DD 1E  216  52 221  30
// UTF-16LE  34 D8 1E DD   52 216  30 221
// UTF-32BE  00 01 D1 1E    0   1 209  30
// UTF-32LE  1E D1 01 00   30 209   1   0

// Big endian as we use a big endian converter
const unsigned char utf8Val[5] = {0xF0, 0x9D, 0x84, 0x9E, 0x0};
const char16_t     utf16Val[3] = {0xD834,     0xDD1E,     0x0};
const char32_t     utf32Val[2] = {0x0001D11E,             0x0};

TEST_F(conversion_test, utf_encode_string)
{
    std::string input((char*)utf8Val);
    std::u32string expected(utf32Val);

    auto output = string::encode(input, Encoding::UTF8);

    EXPECT_EQ(expected, output);
}

TEST_F(conversion_test, utf_encode_u16string)
{
    std::u16string input(utf16Val);
    std::u32string expected(utf32Val);

    auto output = string::encode(input, Encoding::UTF16);

    EXPECT_EQ(expected, output);
}

TEST_F(conversion_test, utf_encode_cstr)
{
    const char* input = (char*)utf8Val;
    const size_t inSize = 4;
    std::u32string expected(utf32Val);

    auto output = string::encode(input, inSize, Encoding::UTF8);

    EXPECT_EQ(expected, output);
}

TEST_F(conversion_test, utf_decode_string)
{
    std::u32string input(utf32Val);
    std::string expected((char*)utf8Val);
    std::string output;

    string::decode(input, output, Encoding::UTF8);

    EXPECT_EQ(expected, output);
}

TEST_F(conversion_test, utf_decode_u16string)
{
    std::u32string input(utf32Val);
    std::u16string expected(utf16Val);
    std::u16string output;

    string::decode(input, output, Encoding::UTF16);

    EXPECT_EQ(expected, output);
}

TEST_F(conversion_test, utf_decode_cstr)
{
    std::u32string input(utf32Val);
    const char* expected = (char*)utf8Val;
    char* output = nullptr;
    size_t outSize = 0;

    string::decode(input, output, outSize, Encoding::UTF8);

    ASSERT_NE(nullptr, output);
    EXPECT_EQ(4, outSize);
    EXPECT_STREQ(expected, output);
}
