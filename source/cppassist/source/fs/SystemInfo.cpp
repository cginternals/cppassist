
#include <stdlib.h>

#include <cppassist/fs/SystemInfo.h>


namespace
{


#if defined(SYSTEM_WINDOWS)
    const std::string pathSeperatorString = "\\";
    const std::string libPrefixString = "";
    const std::string libExtensionString = "dll";
#elif defined(SYSTEM_DARWIN)
    const std::string pathSeperatorString = "/";
    const std::string libPrefixString = "";
    const std::string libExtensionString = "dylib";
#else
    const std::string pathSeperatorString = "/";
    const std::string libPrefixString = "lib";
    const std::string libExtensionString = "so";
#endif


} // namespace


namespace cppassist
{


const std::string & SystemInfo::pathSeperator()
{
    return pathSeperatorString;
}

const std::string & SystemInfo::libPrefix()
{
    return libPrefixString;
}

const std::string & SystemInfo::libExtension()
{
    return libExtensionString;
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
