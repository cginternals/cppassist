
#pragma once


#include <cppassist/strings/manipulation.h>

#include <sstream>


namespace stringzeug
{


template <class Iterable>
std::string join(const Iterable & iterable, const std::string & separator)
{
    std::stringstream stream;

    for (auto it = iterable.begin(); it != iterable.end(); ++it)
    {
        stream << *it;

        if (it != --iterable.end())
            stream << separator;
    }

    return stream.str();
}

    
} // namespace stringzeug
