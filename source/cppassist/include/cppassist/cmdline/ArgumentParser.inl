
#include <cppassist/string/conversion.h>


namespace cppassist
{


template <typename T>
T ArgumentParser::value(const std::string & option, const T & defaultValue) const
{
    const auto it = m_options.find(option);

    if (it == m_options.end())
    {
        return defaultValue;
    }

    return string::fromString<T>(it->second);
}


} // namespace cppassist
