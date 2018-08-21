
#pragma once


#include <string>
#include <vector>

#include <cppassist/cppassist_api.h>


namespace cppassist
{
namespace string
{


/**
*  @brief
*    Check if a regex matches a given string
*
*  @param[in] string
*    Input string
*  @param[in] regex
*    Regular expression
*
*  @return
*    `true` if regex matches the string, else `false`
*/
CPPASSIST_API bool matchesRegex(const std::string & string, const std::string & regex);

/**
*  @brief
*    Extract substrings matched by a regex
*
*  @param[in] string
*    Input string
*  @param[in] regex
*    Regular expression
*
*  @return
*    List of results that match the regex
*/
CPPASSIST_API std::vector<std::string> extract(const std::string & string, const std::string & regex);

/**
*  @brief
*    Extract next string matched by a regex
*
*  @param[in] begin
*    Begin iterator of string range
*  @param[in] end
*    End iterator of string range
*  @param[in] regex
*    Regular expression
*  @param[out] match
*    The resulting match
*
*  @return
*    The iterator to the character after the match or `begin` if regex does not match
*/
CPPASSIST_API std::string::const_iterator extractNext(std::string::const_iterator begin, std::string::const_iterator end, const std::string & regex, std::string & match);

/**
*  @brief
*    Extract next string matched by a regex
*
*  @param[in] begin
*    Begin pointer of string range
*  @param[in] end
*    End pointer of string range
*  @param[in] regex
*    Regular expression
*  @param[out] match
*    The resulting match
*
*  @return
*    The pointer to the character after the match or `begin` if regex does not match
*/
CPPASSIST_API const char * extractNext(const char * begin, const char * end, const std::string & regex, std::string & match);


} // namespace string
} // namespace cppassist
