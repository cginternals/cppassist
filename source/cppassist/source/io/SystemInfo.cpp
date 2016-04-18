
#include <cppassist/io/SystemInfo.h>


namespace cppassist
{


std::string SystemInfo::pathSeperator()
{
    #ifdef WIN32
        return "\\";
    #elif __APPLE__
        return "/";
    #else
        return "/";
    #endif
}

std::string SystemInfo::libPrefix()
{
    #ifdef WIN32
        return "";
    #elif __APPLE__
        return "";
    #else
        return "lib";
    #endif   
}

std::string SystemInfo::libExtension()
{
    #ifdef WIN32
        return "dll";
    #elif __APPLE__
        return "dylib";
    #else
        return "so";
    #endif
}


} // namespace cppassist
