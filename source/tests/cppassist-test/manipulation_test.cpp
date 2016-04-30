
#include <gmock/gmock.h>

#include <cppassist/strings/manipulation.h>


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
    std::string res = join(vec, "-");

    ASSERT_EQ("string-to-concatenate", res);
}

TEST_F(manipulation_test, trim)
{
    std::string stringWithWhitespaces = "   This is a string.     ";
    std::string trim1 = trim(stringWithWhitespaces);
    std::string trim2 = trim(stringWithWhitespaces, true);

    ASSERT_EQ("This is a string.", trim1);
    ASSERT_EQ("Thisisastring.", trim2);
}

TEST_F(manipulation_test, parseArray)
{
    std::string stringArray = "(element1, element2   ,element3,element4)";
    std::vector<std::string> vec = parseArray(stringArray, 4);
    std::vector<std::string> vecComp {"element1", "element2", "element3", "element4"};

    ASSERT_EQ(vecComp, vec);
}

TEST_F(manipulation_test, split)
{
    std::string inputString = "seperate this - by-minus-  sign.-?";
    std::vector<std::string> vec = split(inputString, '-');
    std::vector<std::string> vecComp {"seperate this ", " by", "minus", "  sign.", "?"};

    ASSERT_EQ(vecComp, vec);
}

TEST_F(manipulation_test, contains)
{
    std::string str = "this string contains several words.";

    ASSERT_TRUE(contains(str, "string"));
    ASSERT_TRUE(contains(str, " "));
    ASSERT_TRUE(contains(str, "this string contains several words."));
    ASSERT_TRUE(contains(str, "."));

    ASSERT_FALSE(contains(str, "not"));
    ASSERT_FALSE(contains(str, "  "));
    ASSERT_FALSE(contains(str, ","));
}

TEST_F(manipulation_test, hasPrefix)
{
    std::string str = "abc";

    ASSERT_TRUE(hasPrefix(str, "a"));
    ASSERT_TRUE(hasPrefix(str, "ab"));
    ASSERT_TRUE(hasPrefix(str, "abc"));

    ASSERT_FALSE(hasPrefix(str, "abcd"));
    ASSERT_FALSE(hasPrefix(str, "b"));
    ASSERT_FALSE(hasPrefix(str, "c"));
}

TEST_F(manipulation_test, hasSuffix)
{
    std::string str = "abc";

    ASSERT_TRUE(hasSuffix(str, "c"));
    ASSERT_TRUE(hasSuffix(str, "bc"));
    ASSERT_TRUE(hasSuffix(str, "abc"));

    ASSERT_FALSE(hasSuffix(str, "a"));
    ASSERT_FALSE(hasSuffix(str, "b"));
    ASSERT_FALSE(hasSuffix(str, "ab"));
    ASSERT_FALSE(hasSuffix(str, "d"));
}
