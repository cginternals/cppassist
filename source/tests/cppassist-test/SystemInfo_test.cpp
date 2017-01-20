
#include <gmock/gmock.h>

#include <cppassist/fs/SystemInfo.h>


using namespace cppassist;


class SystemInfo_test : public testing::Test
{
public:
    SystemInfo_test()
    {
    }
};


TEST_F(SystemInfo_test, pathSeperator)
{
    #ifdef WIN32
        ASSERT_EQ("\\", SystemInfo::pathSeperator());
    #elif __APPLE__
        ASSERT_EQ("/", SystemInfo::pathSeperator());
    #else
        ASSERT_EQ("/", SystemInfo::pathSeperator());
    #endif
}

TEST_F(SystemInfo_test, libPrefix)
{
    #ifdef WIN32
        ASSERT_EQ("", SystemInfo::libPrefix());
    #elif __APPLE__
        ASSERT_EQ("", SystemInfo::libPrefix());
    #else
        ASSERT_EQ("lib", SystemInfo::libPrefix());
    #endif
}

TEST_F(SystemInfo_test, libExtension)
{
    #ifdef WIN32
        ASSERT_EQ("dll", SystemInfo::libExtension());
    #elif __APPLE__
        ASSERT_EQ("dylib", SystemInfo::libExtension());
    #else
        ASSERT_EQ("so", SystemInfo::libExtension());
    #endif
}
