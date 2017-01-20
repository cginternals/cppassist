
#include <cppassist/string/manipulation.h>

#include <cassert>

#ifdef USE_STD_REGEX
    #include <regex>

    namespace regex_namespace = std;
#else
    #include <boost/regex.hpp>

    namespace regex_namespace = boost;
#endif


namespace
{


const regex_namespace::regex trimRegex("(^\\s+|\\s+$)");
const regex_namespace::regex trimRegexRemoveAllWhiteSpace("\\s+");


}


namespace cppassist
{
namespace string
{


std::string trim(const std::string & string, bool removeAllWhitespace)
{
    return regex_namespace::regex_replace(string, removeAllWhitespace ? trimRegexRemoveAllWhiteSpace : trimRegex, std::string());
}

std::string padLeft(const std::string & string, size_t length, char c)
{
    std::string padded = string;
    while (padded.size() < length) padded = c + padded;

    return padded;
}

std::string padRight(const std::string & string, size_t length, char c)
{
    std::string padded = string;
    while (padded.size() < length) padded = padded + c;

    return padded;
}

std::string stripped(const std::string & string, const std::set<char> & blacklist)
{
    auto result = string;
    result.erase(std::remove_if(result.begin(), result.end(), [&blacklist](char x) {
        return blacklist.count(x) > 0; }), result.end());

    return result;
}

std::vector<std::string> parseArray(const std::string & string, size_t size)
{
    std::string regexString = "\\s*\\(";
    for (size_t i = 0; i < size - 1; ++i)
        regexString.append("([^,]*),");
    regexString.append("([^,]*)\\)\\s*");

    regex_namespace::smatch match;
    regex_namespace::regex regex(regexString);

    if (!regex_namespace::regex_match(string, match, regex))
        return {};

    std::vector<std::string> result;
    for (size_t i = 1; i < match.size(); ++i)
        result.push_back(trim(match[i].str(), false));

    assert(result.size() == size);
    return result;
}

std::vector<std::string> split(const std::string & input, char delimiter)
{
    std::vector<std::string> result;
    std::string line;
    std::stringstream ss(input);

    while(std::getline(ss, line, delimiter))
    {
        if (!line.empty())
        {
            result.push_back(line);
        }
    }

    return result;
}

bool contains(const std::string & string, const std::string & containsstring)
{
    return string.find(containsstring) != std::string::npos;
}

bool hasPrefix(const std::string & string, const std::string & prefix)
{
    return string.find(prefix) == 0;
}

bool hasSuffix(const std::string & string, const std::string & suffix)
{
    return string.size() >= suffix.size() && string.compare(string.size() - suffix.size(), suffix.size(), suffix) == 0;
}


} // namespace string
} // namespace cppassist
