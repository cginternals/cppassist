
#include <cppassist/string/conversion.h>

#include <cassert>
#include <algorithm>
#include <iterator>

#include <linenoise-ng/ConvertUTF.h>


namespace
{


void convertUTF8toUTF32(const std::string & input, std::u32string & output)
{
    output.resize(input.size());

    const uint8_t * inStart  = (uint8_t*)  input.data();
    const uint8_t * inEnd    = (uint8_t*)  input.data() + input.size();
    uint32_t      * outStart = (uint32_t*) output.data();
    uint32_t      * outEnd   = (uint32_t*) output.data() + output.size();

    uint32_t * outStartSaved = (uint32_t*) output.data();

    auto error = linenoise_ng::ConvertUTF8toUTF32(&inStart, inEnd, &outStart, outEnd, linenoise_ng::strictConversion);

    const auto outSize = error ? 0 : outStart - outStartSaved;
    output.resize(outSize);
}

void convertUTF16toUTF32(const std::u16string & input, std::u32string & output)
{
    output.resize(input.size());

    const uint16_t * inStart  = (uint16_t*) input.data();
    const uint16_t * inEnd    = (uint16_t*) input.data() + input.size();
    uint32_t       * outStart = (uint32_t*) output.data();
    uint32_t       * outEnd   = (uint32_t*) output.data() + output.size();

    uint32_t * outStartSaved = (uint32_t*) output.data();

    auto error = linenoise_ng::ConvertUTF16toUTF32(&inStart, inEnd, &outStart, outEnd, linenoise_ng::strictConversion);

    const auto outSize = error ? 0 : outStart - outStartSaved;
    output.resize(outSize);
}

void convertUTF32toUTF8(const std::u32string & input, std::string & output)
{
    output.resize(input.size() * 6);

    const uint32_t * inStart  = (uint32_t*) input.data();
    const uint32_t * inEnd    = (uint32_t*) input.data() + input.size();
    uint8_t        * outStart = (uint8_t*)  output.data();
    uint8_t        * outEnd   = (uint8_t*)  output.data() + output.size();

    uint8_t * outStartSaved = (uint8_t*) output.data();

    auto error = linenoise_ng::ConvertUTF32toUTF8(&inStart, inEnd, &outStart, outEnd, linenoise_ng::strictConversion);

    const auto outSize = error ? 0 : outStart - outStartSaved;
    output.resize(outSize);
}

void convertUTF32toUTF16(const std::u32string & input, std::u16string & output)
{
    // Note: char16_t instead of uint16_t because of an inconsistency in linenoise-ng
    output.resize(input.size() * 2);

    const uint32_t * inStart  = (uint32_t*) input.data();
    const uint32_t * inEnd    = (uint32_t*) input.data() + input.size();
    char16_t       * outStart = (char16_t*) output.data();
    char16_t       * outEnd   = (char16_t*) output.data() + output.size();

    char16_t * outStartSaved = (char16_t*) output.data();

    auto error = linenoise_ng::ConvertUTF32toUTF16(&inStart, inEnd, &outStart, outEnd, linenoise_ng::strictConversion);

    const auto outSize = error ? 0 : outStart - outStartSaved;
    output.resize(outSize);
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
        convertUTF8toUTF32(input, output);
        break;

    default:
        assert(false);
    }

    return output;
}

std::u32string encode(const std::wstring & input, const Encoding encoding)
{
    switch (sizeof(wchar_t))
    {
    case 1:
        return encode(std::string(input.begin(), input.end()), encoding);

    case 2:
        return encode(std::u16string(input.begin(), input.end()), encoding);

    case 4:
        return std::u32string(input.begin(), input.end());

    default:
        assert(false);
    }

	return std::u32string();
}

std::u32string encode(const std::u16string & input, const Encoding encoding)
{
    auto output = std::u32string();

    switch (encoding)
    {
    case Encoding::ANSI:
    //case Encoding::ASCII:
        std::copy(input.begin(), input.end(), std::back_inserter(output));
        break;

    case Encoding::UTF16:
        convertUTF16toUTF32(input, output);
        break;

    default:
        assert(false);
    }

    return output;
}

std::u32string encode(const char * input, const size_t size, const Encoding encoding)
{
    return encode(std::string(input, size), encoding);
}

void decode(const std::u32string & input, std::string & output, const Encoding encoding)
{
    output.clear();

    switch (encoding)
    {
    case Encoding::ANSI:
    //case Encoding::ASCII:
        std::copy(input.begin(), input.end(), std::back_inserter(output));
        break;

    case Encoding::UTF8:
        convertUTF32toUTF8(input, output);
        break;

    default:
        assert(false);
    }
}

void decode(const std::u32string & input, std::wstring & output, const Encoding encoding)
{
    switch(sizeof(wchar_t))
    {
    case 1:
    {
        std::string temp;
        decode(input, temp, encoding);
        output = std::wstring(temp.begin(), temp.end());
        break;
    }

    case 2:
    {
        std::u16string temp;
        decode(input, temp, encoding);
        output = std::wstring(temp.begin(), temp.end());
        break;
    }

    case 4:
        output = std::wstring(input.begin(), input.end());
        break;

    default:
        assert(false);
        break;
    }
}

void decode(const std::u32string & input, std::u16string & output, const Encoding encoding)
{
    output.clear();

    switch (encoding)
    {
    case Encoding::ANSI:
    //case Encoding::ASCII:
        std::copy(input.begin(), input.end(), std::back_inserter(output));
        break;

    case Encoding::UTF16:
        convertUTF32toUTF16(input, output);
        break;

    default:
        assert(false);
    }
}

void decode(const std::u32string & input, char * & output, size_t & size, const Encoding encoding)
{
    std::string temp;
    decode(input, temp, encoding);

    size = temp.size();
    free(output);
    output = (char*)malloc(size + 1);
    temp.copy(output, temp.npos);
    output[size] = 0x0;
}


std::string toLower(const std::string & input)
{
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](char c){return static_cast<char>(::tolower(c));});
    return result;
}

std::string toLower(std::string && input)
{
    std::string result = std::move(input);
    std::transform(result.begin(), result.end(), result.begin(), [](char c){return static_cast<char>(::tolower(c));});
    return result;
}

std::string toUpper(const std::string & input)
{
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](char c){return static_cast<char>(::toupper(c));});
    return result;
}

std::string toUpper(std::string && input)
{
    std::string result = std::move(input);
    std::transform(result.begin(), result.end(), result.begin(), [](char c){return static_cast<char>(::toupper(c));});
    return result;
}

} // namespace string
} // namespace cppassist
