
#pragma once


#include <functional>
#include <string>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


//@{
/**
*  @brief
*    String encoding
*
*    This enum is mainly used to support the conversion of strings or
*    collections of characters to UTF-32.
*/
enum class Encoding : unsigned int
{
    ANSI
,   ASCII = Encoding::ANSI // for both ANSI and ASCII 1 byte in a std::string or char is used to encode it
,   UTF8
,   UTF16
};
//@}


namespace string
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

template <>
CPPASSIST_API bool fromString<bool>(const std::string & string);

template <>
CPPASSIST_API int fromString<int>(const std::string & string);
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

template <>
CPPASSIST_API std::string toString<bool>(const bool & value);
//@}

//@{
/**
*  @brief
*    Encode string to UTF-32
*
*  @param[in] input
*    Input string
*  @param[in] encoding
*    Encoding of the input string
*
*  @returns
*    UTF-32 encoded string
*
*/
CPPASSIST_API std::u32string encode(const std::string & input, Encoding encoding);
CPPASSIST_API std::u32string encode(const std::wstring & input, Encoding encoding);
CPPASSIST_API std::u32string encode(const std::u16string & input, Encoding encoding);
CPPASSIST_API std::u32string encode(const char * input, const size_t size, Encoding encoding);

CPPASSIST_API void decode(const std::u32string & input, std::string & output, Encoding encoding);
CPPASSIST_API void decode(const std::u32string & input, std::wstring & output, Encoding encoding);
CPPASSIST_API void decode(const std::u32string & input, std::u16string & output, Encoding encoding);
CPPASSIST_API void decode(const std::u32string & input, char * & output, std::size_t & size, Encoding encoding);
//@}


//@{
/**
*  @brief
*    Create lowercase string from input
*
*  @param[in] input
*    Input string
*
*  @return
*    String in lower-case
*/
CPPASSIST_API std::string toLower(const std::string & input);
CPPASSIST_API std::string toLower(std::string && input);
//@}

//@{
/**
*  @brief
*    Create uppercase string from input
*
*  @param[in] input
*    Input string
*
*  @return
*    String in upper-case
*/
CPPASSIST_API std::string toUpper(const std::string & input);
CPPASSIST_API std::string toUpper(std::string && input);
//@}


} // namespace string
} // namespace cppassist


namespace std
{


//@{
/**
*  @brief
*    Hash function for cppassist::Encoding
*/
template<>
struct hash<cppassist::Encoding>
{
    /**
    *  @brief
    *    Create hash for cppassist::Encoding value
    *
    *  @param[in] arg
    *    Encoding type
    *
    *  @returns
    *    Hash value
    */
    std::hash<unsigned int>::result_type operator()(const cppassist::Encoding & arg) const
    {
        std::hash<unsigned int> hasher;
        return hasher(static_cast<unsigned int>(arg));
    }
};
//@}


} // namespace std


#include <cppassist/string/conversion.inl>
