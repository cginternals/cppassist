
#pragma once


#include <string>

#include <cppassist/cppassist_api.h>


namespace cppassist
{

/**
*  @brief
*    Get the base name of the file path parameter
*
*  @param[in] filename
*    Full file name including path and extension (e.g., /path/to/file.extension)
*  @return
*    The base name without path and extension (e.g., file)
*/
CPPASSIST_API std::string getBaseName(const std::string & filename);

/**
*  @brief
*    Get the base name of the file path parameter
*
*  @param[in] filename
*    Full file name including path and extension (e.g., /path/to/file.extension)
*  @return
*    The base name without path and extension (e.g., file)
*/
CPPASSIST_API std::string getPath(const std::string & filename);

/**
*  @brief
*    Get filename extension
*
*  @param[in] filename
*    File name including extension (e.g., 'myfile.txt')
*  @return
*    File extension without dot (e.g., 'txt')
*
*  @remarks
*    This function searches for the last occurence of '.' and returns
*    the remaining string, so 'myarchive.tar.gz' will return 'gz'
*    rather than 'tar.gz'. If the filename is empty or has no extension,
*    an empty string is returned.
*/
CPPASSIST_API std::string getExtension(const std::string & filename);

/**
*  @brief
*    Makes sure given path does not end with (platform specific) separator
*
*  @param[in] path
*    Path to directory or file
*
*  @return
*    Path to directory or file with ensured missing separator ending
*/
CPPASSIST_API std::string removeTrailingPathSeparator(const std::string & path);

/**
*  @brief
*    Makes sure given path ends with (platform specific) separator
*
*  @param[in] path
*    Path to directory or file
*
*  @return
*    Path to directory or file with ensured separator ending
*/
CPPASSIST_API std::string ensurePathSeparatorEnding(const std::string & path);

} // namespace cppassist
