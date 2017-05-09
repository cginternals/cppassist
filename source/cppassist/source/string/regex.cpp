
#include <cppassist/string/regex.h>

#ifdef USE_STD_REGEX
    #include <regex>

    namespace regex_namespace = std;
#else
    #include <boost/regex.hpp>

    namespace regex_namespace = boost;
#endif


namespace cppassist
{
namespace string
{


bool matchesRegex(const std::string & string, const std::string & regex)
{
    return regex_namespace::regex_match(string, regex_namespace::regex(regex));
}

std::vector<std::string> extract(const std::string & string, const std::string & regex)
{
    std::vector<std::string> values;

    regex_namespace::smatch matchResults;
    const regex_namespace::regex r(regex);

    std::string s = string;
    while (regex_namespace::regex_search(s, matchResults, r))
    {
        values.push_back(matchResults[0]);
        s = matchResults.suffix().str();
    }

    return values;
}

std::string::const_iterator extractNext(std::string::const_iterator begin, std::string::const_iterator end, const std::string & regex, std::string & match)
{
    match.clear();

    regex_namespace::smatch matchResults;
    const regex_namespace::regex r(regex);

    if (!regex_namespace::regex_search(begin, end, matchResults, r))
    {
        return begin;
    }

    match = matchResults[0];

    return begin + match.size();
}

const char * extractNext(const char * begin, const char * end, const std::string & regex, std::string & match)
{
    match.clear();

    regex_namespace::cmatch matchResults;
    const regex_namespace::regex r(regex);

    if (!regex_namespace::regex_search(begin, end, matchResults, r))
    {
        return begin;
    }

    match = matchResults[0];

    return begin + match.size();
}


} // namespace string
} // namespace cppassist
