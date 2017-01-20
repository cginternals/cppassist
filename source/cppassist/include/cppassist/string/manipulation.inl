
#pragma once


#include <sstream>


namespace cppassist
{
namespace string
{


template <class Iterable>
std::string join(const Iterable & iterable, const std::string & separator)
{
    std::stringstream stream;

    for (auto it = iterable.begin(); it != iterable.end(); ++it)
    {
        stream << *it;

        if (it+1 != iterable.end())
            stream << separator;
    }

    return stream.str();
}


} // namespace string
} // namespace cppassist
