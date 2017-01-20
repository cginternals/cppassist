
#include <gmock/gmock.h>

#include <cppassist/string/manipulation.h>


using namespace cppassist;


class manipulation_test : public testing::Test
{
public:
    manipulation_test()
    {
    }
};


TEST_F(manipulation_test, join)
{
    std::vector<std::string> vec {"string", "to", "concatenate"};
    std::string res = string::join(vec, "-");

    ASSERT_EQ("string-to-concatenate", res);
}

TEST_F(manipulation_test, trim)
{
    std::string stringWithWhitespaces = "   This is a string.     ";
    std::string trim1 = string::trim(stringWithWhitespaces);
    std::string trim2 = string::trim(stringWithWhitespaces, true);

    ASSERT_EQ("This is a string.", trim1);
    ASSERT_EQ("Thisisastring.", trim2);
}

TEST_F(manipulation_test, parseArray)
{
    std::string stringArray = "(element1, element2   ,element3,element4)";
    std::vector<std::string> vec = string::parseArray(stringArray, 4);
    std::vector<std::string> vecComp {"element1", "element2", "element3", "element4"};

    ASSERT_EQ(vecComp, vec);
}

TEST_F(manipulation_test, split)
{
    std::string inputString = "seperate this - by-minus-  sign.-?";
    std::vector<std::string> vec = string::split(inputString, '-');
    std::vector<std::string> vecComp {"seperate this ", " by", "minus", "  sign.", "?"};

    ASSERT_EQ(vecComp, vec);
}

TEST_F(manipulation_test, contains)
{
    std::string str = "this string contains several words.";

    ASSERT_TRUE(string::contains(str, "string"));
    ASSERT_TRUE(string::contains(str, " "));
    ASSERT_TRUE(string::contains(str, "this string contains several words."));
    ASSERT_TRUE(string::contains(str, "."));

    ASSERT_FALSE(string::contains(str, "not"));
    ASSERT_FALSE(string::contains(str, "  "));
    ASSERT_FALSE(string::contains(str, ","));
}

TEST_F(manipulation_test, hasPrefix)
{
    std::string str = "abc";

    ASSERT_TRUE(string::hasPrefix(str, "a"));
    ASSERT_TRUE(string::hasPrefix(str, "ab"));
    ASSERT_TRUE(string::hasPrefix(str, "abc"));

    ASSERT_FALSE(string::hasPrefix(str, "abcd"));
    ASSERT_FALSE(string::hasPrefix(str, "b"));
    ASSERT_FALSE(string::hasPrefix(str, "c"));
}

TEST_F(manipulation_test, hasSuffix)
{
    std::string str = "abc";

    ASSERT_TRUE(string::hasSuffix(str, "c"));
    ASSERT_TRUE(string::hasSuffix(str, "bc"));
    ASSERT_TRUE(string::hasSuffix(str, "abc"));

    ASSERT_FALSE(string::hasSuffix(str, "a"));
    ASSERT_FALSE(string::hasSuffix(str, "b"));
    ASSERT_FALSE(string::hasSuffix(str, "ab"));
    ASSERT_FALSE(string::hasSuffix(str, "d"));
}
