
#pragma once


#include <ostream>
#include <string>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


/**
*  @brief
*    Parse integer number from string
*
*  @param[in] str
*    Input string
*
*  @param[in] number
*    Integral number parsed from string
*
*  @return
*    Number of characters read
*/
CPPASSIST_API int readInt(const char * str, int & number);

/**
*  @brief
*    Parse format string and output to stream
*
*  @param[in] stream
*    Output stream
*  @param[in] format
*    Format string (must NOT be null!)
*/
CPPASSIST_API void parseFormat(std::ostream & stream, const char *& format);

/**
*  @brief
*    Print formatted string to stream
*
*  @param[in] stream
*    Output stream
*  @param[in] format
*    Format string (must NOT be null!)
*
*  @see
*    formatString
*/
CPPASSIST_API void streamprintf(std::ostream & stream, const char * format);

/**
*  @brief
*    Print formatted string to stream
*
*  @param[in] stream
*    Output stream
*  @param[in] format
*    Format string (must NOT be null!)
*  @param[in] args
*    Arguments according to the format string
*
*  @see
*    formatString
*/
template <typename T, typename... Args>
void streamprintf(std::ostream & stream, const char * format, const T & value, Args... args);

/**
*  @brief
*    Format string
*
*    This function takes a format string and any number of arguments of different types.
*    It works similar to printf, but is safer as it can infer the types.
*    This also means that the type does not need to be encoded in the format string,
*    instead they only indicate stream manipulators.
*
*    Format syntax
*    =============
*
*    `%[alignment flag][independent flags][floatfield flag][fill character][width][precision][base];`
*    `%[ l | r | i ][ a | # | + | u | p ]*[ e | f ][?<fill character>][<width>][.<precision>][ d | o | x ];`
*
*    alignment flags
*    ---------------
*
*    flag | manipulator
*    ---- | -----
*    `l` | left
*    `r` | right
*    `i` | internal
*
*    independent flags
*    -----------------
*
*    flag | manipulator
*    ---- | -----
*    `a` | boolalpha
*    `#` | showbase
*    `+` | showpos
*    `u` | uppercase
*    `p` | showpoint
*    `0` | setfill(0) [redundant]
*
*    floatfield flags
*    ----------------
*
*    flag | manipulator
*    ---- | -----
*    `e` | scientific
*    `f` | fixed
*
*    base
*    ----
*
*    flag | manipulator
*    ---- | -----
*    `d` | decimal
*    `o` | octal
*    `x` | hexadecimal
*
*    In addition, if the base or floatfield flag is uppercase, it will automatically enable the uppercase flag without 'u'.
*    Note: To end a format specifier, you have to add a semicolon.
*    `%%` will escape a % character.
*
*  @param[in] format
*    Format string (must NOT be null!)
*  @param[in] args
*    Arguments according to the format string
*
*  @see
*    http://www.cplusplus.com/reference/ios/ios_base/fmtflags/
*/
template <typename... Args>
std::string formatString(const char * format, Args... args);


} // namespace cppassist


#include <cppassist/logging/formatString.hpp>
