
#include <gmock/gmock.h>

#include <cppassist/string/processing.h>


using namespace cppassist;


class processing_test : public testing::Test
{
public:
    processing_test()
    {
    }
};


TEST_F(processing_test, parseLine)
{
    const auto s = std::string("This;is;a;semi-colon;separated;string");
    auto callCount = std::uint16_t(0);

    cppassist::string::parseLine(s, 0, ';', '"', [& callCount](std::string && part, std::uint32_t index) {
        callCount++;

        ASSERT_GT(6, index);
        ASSERT_NE(std::string(""), part);
    });

    ASSERT_EQ(callCount, 6);
}

TEST_F(processing_test, parseLine_startPos)
{
    const auto s = std::string("This;is;a;semi-colon;separated;string");
    auto callCount = std::uint16_t(0);

    cppassist::string::parseLine(s, 12, ';', '"', [& callCount](std::string && part, std::uint32_t index) {
        callCount++;

        ASSERT_GT(3, index);
        ASSERT_NE(std::string(""), part);
    });

    ASSERT_EQ(callCount, 3);
}

TEST_F(processing_test, parseLine_escaped)
{
    const auto s = std::string("This;is;a;\"semi-colon;separated\";string");
    auto callCount = std::uint16_t(0);
    auto anyWithSemicolon = false;

    cppassist::string::parseLine(s, 0, ';', '"', [& callCount, & anyWithSemicolon](std::string && part, std::uint32_t index) {
        callCount++;

        ASSERT_GT(5, index);
        ASSERT_NE(std::string(""), part);

        anyWithSemicolon |= part.find(';') != std::string::npos;
    });

    ASSERT_EQ(callCount, 5);
    ASSERT_TRUE(anyWithSemicolon);
}
