
#include <stdlib.h>

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

std::string SystemInfo::homeDir()
{
    return std::string(getenv("HOME"));
}

std::string SystemInfo::configDir(const std::string & application)
{
    #ifdef WIN32
        return std::string(getenv("APPDATA")) + "\\" + application;
    #elif __APPLE__
        return std::string(getenv("HOME")) + "/Library/Preferences/" + application;
    #else
        return std::string(getenv("HOME")) + "/.config/" + application;
    #endif
}


} // namespace cppassist
