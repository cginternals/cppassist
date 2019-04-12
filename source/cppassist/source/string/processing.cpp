
#include <cppassist/string/processing.h>

#include <cassert>

#include <cppassist/string/manipulation.h>


namespace cppassist
{
namespace string
{


void parseLine(const std::string & line, const std::string::size_type start_pos, const char delimiter, const char escapeCharacter, std::function<void(std::string && value, const int index)> callback)
{
    if (start_pos == std::string::npos)
    {
        // No rest of line
        return;
    }

    int i = 0;
    auto last_pos = start_pos;

    // bool hasEscapeCharacter = line.find(escapeCharacter, last_pos);

    for (auto current_pos = line.find(delimiter, last_pos);
         current_pos != std::string::npos;
         current_pos = line.find(delimiter, last_pos))
    {
        // escaped string
        if (line.at(last_pos) == escapeCharacter)
        {
            // find correct closing escape character
            if (line.at(current_pos - 1) != escapeCharacter)
            {
                current_pos = line.find(escapeCharacter, current_pos);

                assert(current_pos == line.size() - 1 || line.at(current_pos+1) == delimiter);
            }

            callback(cppassist::string::trim(line.substr(last_pos + 1, current_pos - last_pos - 1)), i);

            last_pos = current_pos + 1 + 1;
            ++i;
        }
        else
        {
            callback(cppassist::string::trim(line.substr(last_pos, current_pos - last_pos)), i);

            last_pos = current_pos + 1;
            ++i;
        }
    }

    callback(cppassist::string::trim(line.substr(last_pos)), i);
}


} // namespace string
} // namespace cppassist
