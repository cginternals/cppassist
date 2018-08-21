
#pragma once


#include <string>
#include <vector>
#include <set>

#include <cppassist/cppassist_api.h>


namespace cppassist
{
namespace string
{


/**
*  @brief
*    Join all values of a container in a single string
*
*  @param[in] iterable
*    Container
*  @param[in] separator
*    String separator
*
*  @return
*    Joined string
*/
template <class Iterable>
std::string join(const Iterable & iterable, const std::string & separator);

/**
*  @brief
*    Trim string by removing whitespace
*
*  @param[in] string
*    String
*  @param[in] removeAllWhitespace
*    `true`: remove whitespace everywhere in the string, `false`: remove whitespace at the beginning and the end of the string
*
*  @return
*    Trimmed string
*/
CPPASSIST_API std::string trim(const std::string & string, bool removeAllWhitespace = false);

/**
*  @brief
*    Pad string with character (add to the left until the given size is reached)
*
*  @param[in] string
*    String
*  @param[in] length
*    Desired string length
*  @param[in] c
*    Character that is used to pad the string
*
*  @return
*    Padded string
*/
CPPASSIST_API std::string padLeft(const std::string & string, size_t length, char c = ' ');

/**
*  @brief
*    Pad string with character (add to the right until the given size is reached)
*
*  @param[in] string
*    String
*  @param[in] length
*    Desired string length
*  @param[in] c
*    Character that is used to pad the string
*
*  @return
*    Padded string
*/
CPPASSIST_API std::string padRight(const std::string & string, size_t length, char c = ' ');

/**
*  @brief
*    Remove all occurences of provided characters from the string.
*
*  @param[in] string
*    Input string that is to be processed.
*  @param[in] blacklist
*    Set of single characters that are to be removed.
*
*  @return
*    New string with the characters beeing removed.
*/
CPPASSIST_API std::string stripped(const std::string & string, const std::set<char> & blacklist);

/**
*  @brief
*    Split string into substrings
*
*  @param[in] size
*    Number of elements
*  @param[in] string
*    Input string of the form "(<value>,<value>,<value>...)"
*
*  @return
*    List of strings
*/
CPPASSIST_API std::vector<std::string> parseArray(const std::string & string, size_t size);

/**
*  @brief
*    Split string into substrings
*
*  @param[in] string
*    Input string
*  @param[in] delimiter
*    Character that marks the next element
*  @param[in] keepEmptyParts
*    Flag to signal if empty parts are part of the result or skipped
*
*  @return
*    List of strings
*/
CPPASSIST_API std::vector<std::string> split(const std::string & string, char delimiter, bool keepEmptyParts = true);

/**
*  @brief
*    Check if a string contains a substring
*
*  @param[in] string
*    Input string
*  @param[in] containsstring
*    String that is checked if contained in first param string
*
*  @return
*    `true` if string contains `containsstring`, `false` otherwise
*/
CPPASSIST_API bool contains(const std::string & string, const std::string & containsstring);

/**
*  @brief
*    Check if a string starts with a given prefix
*
*  @param[in] string
*    Input string
*  @param[in] prefix
*    Prefix to be checked
*
*  @return
*    `true` if string starts with `prefix`, `false` otherwise
*/
CPPASSIST_API bool hasPrefix(const std::string & string, const std::string & prefix);

/**
*  @brief
*    Check if a string ends with a given suffix
*
*  @param[in] string
*    Input string
*  @param[in] suffix
*    Suffix to be checked
*
*  @return
*    `true` if string ends with `suffix`, `false` otherwise
*/
CPPASSIST_API bool hasSuffix(const std::string & string, const std::string & suffix);


} // namespace string
} // namespace cppassist


#include <cppassist/string/manipulation.inl>
