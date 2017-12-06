
#include <cppassist/string/conversion.h>

#include <cassert>
#include <algorithm>
#include <iterator>

#ifndef __has_include
    #define __has_include(x) 0
#endif

#if defined(__GNUG__) && !defined(__clang__) && (__GNUG__ < 5)
// not implemented for GCC < 5
#define CPPASSIST_CODECVT_AVAILABLE 0
#elif defined(__clang__) && !__has_include(<codecvt>)
// not implemented for clang without codecvt header
#define CPPASSIST_CODECVT_AVAILABLE 0
#else
#include <locale>
#include <codecvt>
#define CPPASSIST_CODECVT_AVAILABLE 1
#endif


namespace 
{


// [TODO]: probably rename to decodeUTF8 as it is UTF-8 -> UCS4
void encodeUTF8(const std::string & input, std::u32string & output)
{
#if CPPASSIST_CODECVT_AVAILABLE
    #if defined(_MSC_VER) && (_MSC_VER >= 1900 && _MSC_VER <= 1912)
        // MSVC 2015 and 2017 were compiled using uint32_t instead of char32_t, see https://social.msdn.microsoft.com/Forums/expression/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral
        static std::wstring_convert<std::codecvt_utf8<uint32_t>, uint32_t> conversion;

        const auto temp = conversion.from_bytes(input);
        output = std::u32string(temp.begin(), temp.end());
    #else
        static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conversion;

        output = conversion.from_bytes(input);
    #endif
#else
    #pragma message "encodeUTF8 not implemented since it depends on codecvt"
    output.clear();
    output.reserve(input.size());
    std::copy(input.begin(), input.end(), std::back_inserter(output));
#endif
}


} // namespace


namespace cppassist
{
namespace string
{


template <>
char fromString<char>(const std::string & string)
{
    using T = int;

    std::stringstream stream(string);
    auto value = T();
    stream >> value;
    return static_cast<char>(value);
}

template <>
unsigned char fromString<unsigned char>(const std::string & string)
{
    using T = unsigned int;

    std::stringstream stream(string);
    auto value = T();
    stream >> value;
    return static_cast<unsigned char>(value);
}

template <>
bool fromString<bool>(const std::string & string)
{
    return !(string == "" || string == "0" || string == "false");
}

template <>
int fromString<int>(const std::string & string)
{
    return static_cast<int>(std::strtol(string.data(),nullptr,10));
}

template <>
std::string toString<char>(const char & value)
{
    std::stringstream stream;
    stream << static_cast<int>(value);
    return stream.str();
}

template <>
std::string toString<unsigned char>(const unsigned char & value)
{
    std::stringstream stream;
    stream << static_cast<unsigned int>(value);
    return stream.str();
}

template <>
std::string toString<bool>(const bool & value)
{
    if (value) return "true";
    else       return "false";
}

std::u32string encode(const std::string & input, const Encoding encoding)
{
    auto output = std::u32string();

    switch (encoding)
    {
    case Encoding::ANSI:
    //case Encoding::ASCII:
        std::copy(input.begin(), input.end(), std::back_inserter(output));
        break;

    case Encoding::UTF8:
        encodeUTF8(input, output);
        break;

    default:
        assert(false);
    }

    return output;
}

//std::u32string encode(const std::wstring & input, const Encoding encoding)
//{
//    assert(false);
//}
//
//std::u32string encode(const std::u16string & input, const Encoding encoding)
//{
//    assert(false);
//}
//
//std::u32string encode(const char * input, size_t size, const Encoding encoding)
//{
//    assert(false);
//}
//
//void decode(const std::u32string & input, std::string & output, const Encoding encoding)
//{
//    assert(false);
//}
//
//void decode(const std::u32string & input, std::wstring & output, const Encoding encoding)
//{
//    assert(false);
//}
//
//void decode(const std::u32string & input, std::u16string & output, const Encoding encoding)
//{
//    assert(false);
//}
//
//void decode(const std::u32string & input, const char * & output, size_t size, const Encoding encoding)
//{
//    assert(false);
//}


std::string toLower(const std::string & input)
{
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string toLower(std::string && input)
{
    std::string result = std::move(input);
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string toUpper(const std::string & input)
{
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string toUpper(std::string && input)
{
    std::string result = std::move(input);
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

} // namespace string
} // namespace cppassist
