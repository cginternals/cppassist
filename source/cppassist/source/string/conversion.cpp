
#include <cppassist/string/conversion.h>

#include <cassert>
#include <algorithm>
#include <iterator>


namespace 
{


void encodeUTF8(const std::string & input, std::u32string & output)
{
    std::size_t currentCharacterIndex = 0;
    std::size_t characterCount = 0;

    output.resize(input.size() * 4);
    while (currentCharacterIndex < input.size())
    {
        if ((input.at(currentCharacterIndex) & (1 << 7)) == 0) // 1 byte
        {
            output.at(characterCount) = input.at(currentCharacterIndex) & 127;
            currentCharacterIndex += 1;
            ++characterCount;
        }
        else if ((input.at(currentCharacterIndex) & (7 << 5)) == (6 << 5)) // 2 bytes
        {
            assert(currentCharacterIndex + 1 < input.size());
            assert((input.at(currentCharacterIndex + 1) & (2 << 6)) == (2 << 6));

            output.at(characterCount) = (input.at(currentCharacterIndex) & 31 << 6) +
                (input.at(currentCharacterIndex + 1) & 63);
            currentCharacterIndex += 2;
            ++characterCount;
        }
        else if ((input.at(currentCharacterIndex) & (15 << 4)) == (14 << 4)) // 3 bytes
        {
            assert(currentCharacterIndex + 2 < input.size());
            assert((input.at(currentCharacterIndex + 1) & (2 << 6)) == (2 << 6));
            assert((input.at(currentCharacterIndex + 2) & (2 << 6)) == (2 << 6));

            output.at(characterCount) = (input.at(currentCharacterIndex) & 31 << 12) +
                (input.at(currentCharacterIndex + 1) & 63 << 6) +
                (input.at(currentCharacterIndex + 2) & 63);
            currentCharacterIndex += 3;
            ++characterCount;
        }
        else if ((input.at(currentCharacterIndex) & (31 << 3)) == (30 << 3)) // 4 bytes
        {
            assert(currentCharacterIndex + 3 < input.size());
            assert((input.at(currentCharacterIndex + 1) & (2 << 6)) == (2 << 6));
            assert((input.at(currentCharacterIndex + 2) & (2 << 6)) == (2 << 6));
            assert((input.at(currentCharacterIndex + 3) & (2 << 6)) == (2 << 6));

            output.at(characterCount) = (input.at(currentCharacterIndex) & 31 << 18) +
                (input.at(currentCharacterIndex + 1) & 63 << 12) +
                (input.at(currentCharacterIndex + 1) & 63 << 6) +
                (input.at(currentCharacterIndex + 2) & 63);
            currentCharacterIndex += 4;
            ++characterCount;
        }
        else
        {
            assert(false);
        }
    }

    output.resize(characterCount);
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
    return !(string == "" || string == "false");
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
