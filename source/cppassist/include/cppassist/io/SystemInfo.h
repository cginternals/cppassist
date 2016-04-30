
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
    *    Path seperator (e.g., '/' or '\')
    */
    static std::string pathSeperator();

    /**
    *  @brief
    *    Get platform specific shared library prefix
    *
    *  @return
    *    Library prefix (e.g., 'lib' on UNIX systems, '' on Windows)
    */
    static std::string libPrefix();

    /**
    *  @brief
    *    Get platform specific shared library extension
    *
    *  @return
    *    Library prefix (e.g., 'dll', or '.so')
    */
    static std::string libExtension();
};


} // namespace cppassist
