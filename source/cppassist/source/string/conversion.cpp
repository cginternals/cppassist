
#include <cppassist/string/conversion.h>

#include <cassert>
#include <algorithm>
#include <iterator>

#if defined(__GNUG__) && !defined(__clang__) && (__GNUG__ < 5)
// not implemented for GCC < 5
#else
#include <locale>
#include <codecvt>
#endif


namespace 
{


// [TODO]: probably rename to decodeUTF8 as it is UTF-8 -> UCS4
void encodeUTF8(const std::string & input, std::u32string & output)
{
#if defined(__GNUG__) && !defined(__clang__) && (__GNUG__ < 5)
    #pragma message "encodeUTF8 not implemented for GCC 4.x since it depends on codecvt"
    output.clear();
    output.reserve(input.size());
    std::copy(input.begin(), input.end(), std::back_inserter(output));
#else
    static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conversion;

    output = conversion.from_bytes(input);
#endif
}


} // namespace


namespace cppassist
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


} // namespace cppassist
