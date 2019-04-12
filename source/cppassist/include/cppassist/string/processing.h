
#pragma once


#include <functional>
#include <string>

#include <cppassist/cppassist_api.h>


namespace cppassist
{
namespace string
{


/**
*  @brief
*    Splits the line at delimiter (while regarding the symmetric escapeCharacter) and calls the callback for each part.
*
*  @param[in] line
*    The line to parse
*  @param[in] start_pos
*    The start pos within the line for parsing
*  @param[in] delimiter
*    The delimiter for adjacent parts within the line
*  @param[in] escapeCharacter
*    The character for inline escaping (while escaped, the delimiter is ignored; symmetric)
*  @param[in] callback
*    The callback to invoke for each parsed line part
*/
CPPASSIST_API void parseLine(const std::string & line, const std::string::size_type start_pos, const char delimiter, const char escapeCharacter, std::function<void(std::string && value, const int index)> callback);


} // namespace string
} // namespace cppassist
