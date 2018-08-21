
#pragma once


#include <string>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


/**
*  @brief
*    Class to provide platform specific information like prefix or extension of shared libraries
*/
class CPPASSIST_API SystemInfo
{
public:
    /**
    *  @brief
    *    Get platform specific path seperator
    *
    *  @return
    *    Path seperator (e.g., '`/`' or '`\`')
    */
    static const std::string & pathSeperator();

    /**
    *  @brief
    *    Get platform specific shared library prefix
    *
    *  @return
    *    Library prefix (e.g., 'lib' on UNIX systems, '' on Windows)
    */
    static const std::string & libPrefix();

    /**
    *  @brief
    *    Get platform specific shared library extension
    *
    *  @return
    *    Library prefix (e.g., 'dll', or 'so')
    */
    static const std::string & libExtension();

    /**
    *  @brief
    *    Get home directory of the current user
    *
    *  @return
    *    Home directory (native path)
    */
    static std::string homeDir();

    /**
    *  @brief
    *    Get config directory for the named application
    *
    *  @param[in] application
    *    Application name
    *
    *  @return
    *    Config directory (native path)
    */
    static std::string configDir(const std::string & application);
};


} // namespace cppassist
