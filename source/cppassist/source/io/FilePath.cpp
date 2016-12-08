
#include <cppassist/io/FilePath.h>

#include <algorithm>


namespace cppassist
{


FilePath::FilePath()
: m_originalPath("")
, m_path("")
{
}

FilePath::FilePath(const FilePath & filePath)
: m_originalPath(filePath.m_originalPath)
, m_path(filePath.m_path)
{
}

FilePath::FilePath(FilePath && filePath)
: m_originalPath(std::move(filePath.m_originalPath))
, m_path(std::move(filePath.m_path))
{
}

FilePath::FilePath(const std::string & path)
: m_originalPath(path)
, m_path(toPath(m_originalPath))
{
}

FilePath::FilePath(std::string && path)
: m_originalPath(std::move(path))
, m_path(toPath(m_originalPath))
{
}

FilePath::FilePath(const char * path)
: m_originalPath(path)
, m_path(toPath(m_originalPath))
{
}

FilePath::~FilePath()
{
}

const std::string & FilePath::originalPath() const
{
    return m_originalPath;
}

void FilePath::setPath(const std::string & path)
{
    m_originalPath = path;
    m_path = toPath(m_originalPath);
}

const std::string & FilePath::path() const
{
    return m_path;
}

std::string FilePath::toPath(const std::string & path)
{
    auto copy = path;

    std::replace(copy.begin(), copy.end(), '\\', '/');

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
    auto pos = m_originalPath.find_first_of(':');

    if (pos == std::string::npos)
        return std::string();

    return m_originalPath.substr(0, pos);
}

FilePath & FilePath::operator =(const FilePath & filePath)
{
    m_originalPath = filePath.m_originalPath;
    m_path = filePath.m_path;

    return *this;
}

FilePath & FilePath::operator =(FilePath && filePath)
{
    m_originalPath = std::move(filePath.m_originalPath);
    m_path = std::move(filePath.m_path);

    return *this;
}


} // namespace cppassist
