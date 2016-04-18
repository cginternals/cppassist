
#pragma once


#include <string>

#include <cppassist/cppassist_api.h>


namespace iozeug
{


/**
*  @brief
*    Class to provide platform specific information like prefix or extension of shared libraries.
*/
class CPPASSIST_API SystemInfo
{
public:

    /**
    *  @brief
    *    Get platform specific path seperator
    */
    static std::string pathSeperator();

    /**
    *  @brief
    *    Get platform specific shared library prefix
    */
    static std::string libPrefix();

    /**
    *  @brief
    *    Get platform specific shared library extension
    */
    static std::string libExtension();
};


} // namespace reflectionzeug
