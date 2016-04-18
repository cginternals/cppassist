
#pragma once


#include <string>
#include <functional>

#include <cppassist/cppassist_api.h>


namespace stringzeug
{


//@{
/**
*  @brief
*    Convert from std::string to Type
*
*  @param[in] string
*    String representation
*
*  @return
*    Primitive type value
*/
template <typename Type>
Type fromString(const std::string & string);

template <>
CPPASSIST_API char fromString<char>(const std::string & string);

template <>
CPPASSIST_API unsigned char fromString<unsigned char>(const std::string & string);
//@}

//@{
/**
*  @brief
*    Convert from Type to std::string
*
*  @param[in] value
*    Primitive type value
*
*  @return
*    String representation
*/
template <typename Type>
std::string toString(const Type & value);

template <>
CPPASSIST_API std::string toString<char>(const char & value);

template <>
CPPASSIST_API std::string toString<unsigned char>(const unsigned char & value);
//@}


/**
*  @brief
*    The used encoding of a passed std::string.
*
*    This enum is mainly used to support the conversion of strings or a collections of characters to UTF-32, which is internally used by gloperate-text.
*/
enum class Encoding : unsigned int
{
    ANSI
,   ASCII = Encoding::ANSI // for both ANSI and ASCII 1 byte in a std::string or char is used to encode it
,   UTF8
};

CPPASSIST_API std::u32string encode(const std::string & input, Encoding encoding);
//CPPASSIST_API std::u32string encode(const std::wstring & input, Encoding encoding);
//CPPASSIST_API std::u32string encode(const std::u16string & input, Encoding encoding);
//CPPASSIST_API std::u32string encode(const char * input, size_t size, Encoding encoding);
//
//CPPASSIST_API void decode(const std::u32string & input, std::string & output, Encoding encoding);
//CPPASSIST_API void decode(const std::u32string & input, std::wstring & output, Encoding encoding);
//CPPASSIST_API void decode(const std::u32string & input, std::u16string & output, Encoding encoding);
//CPPASSIST_API void decode(const std::u32string & input, const char * & output, std::size_t size, Encoding encoding);


} // namespace stringzeug


namespace std
{

template<>
struct hash<stringzeug::Encoding>
{
    std::hash<unsigned int>::result_type operator()(const stringzeug::Encoding & arg) const
    {
        std::hash<unsigned int> hasher;
        return hasher(static_cast<unsigned int>(arg));
    }
};

} // namespace std


#include <cppassist/strings/conversion.hpp>
