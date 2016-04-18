
#include <cppassist/io/FilePath.h>

#include <algorithm>


namespace cppassist
{


FilePath::FilePath()
: m_string("")
, m_path("")
{
}

FilePath::FilePath(const FilePath & filePath)
: m_string(filePath.path())
, m_path(toPath(m_string))
{
}

FilePath::FilePath(const std::string & string)
: m_string(string)
, m_path(toPath(m_string))
{
}

FilePath::FilePath(const char * string)
: m_string(string)
, m_path(toPath(m_string))
{
}

FilePath::~FilePath()
{
}

const std::string & FilePath::originalPath() const
{
    return m_string;
}

void FilePath::setPath(const std::string & path)
{
    m_string = path;
    m_path = toPath(m_string);
}

const std::string & FilePath::path() const
{
    return m_path;
}

std::string FilePath::toPath(const std::string & str) const
{
    auto copy = str;
    std::replace( copy.begin(), copy.end(), '\\', '/');
    auto i = copy.find_last_of('/');
    if (i == copy.size()-1)
    {
        copy = copy.substr(0, copy.size()-1);
    }
    return copy;
}

std::string FilePath::baseName() const
{
    auto path = this->path();
    auto i = path.find_last_of('/');

    if (i != std::string::npos)
    {
        path = path.substr(++i);
    }

    auto pos = path.find_first_of('.', 1); // Make sure the filename doesn't start with '.'

    if (pos == std::string::npos)
        return path;

    return path.substr(0, pos);
}

std::string FilePath::fileName() const
{
    auto path = this->path();
    auto i = path.find_last_of('/');

    if (i != std::string::npos)
    {
        path = path.substr(++i);
    }

    return path;
}

std::string FilePath::extension() const
{
    auto path = this->path();
    auto i = path.find_last_of('/');

    if (i != std::string::npos)
    {
        path = path.substr(++i);
    }

    auto pos = path.find_first_of('.', 1); // Make sure the filename doesn't start with '.'

    if (pos == std::string::npos)
        return std::string();

    return path.substr(++pos);
}

std::string FilePath::directoryPath() const
{
    auto path = this->path();
    auto pos = path.find_last_of('/');

    if (pos == std::string::npos)
        return std::string();

    return path.substr(0, pos+1); // Add trailing slash
}

std::string FilePath::driveLetter() const
{
    auto pos = m_string.find_first_of(':');

    if (pos == std::string::npos)
        return std::string();

    return m_string.substr(0, pos);
}


} // namespace cppassist
