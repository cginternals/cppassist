
#include <cppassist/fs/RawFile.h>

#include <iostream>

#include <cppassist/fs/readfile.h>


namespace cppassist
{


RawFile::RawFile()
: m_valid(false)
{
}

RawFile::~RawFile()
{
}

bool RawFile::load(const std::string & filePath)
{
    m_filePath = filePath;

    return reload();
}

bool RawFile::reload()
{
    m_valid = readFile();

    return m_valid;
}

bool RawFile::isValid() const
{
    return m_valid;
}

const std::string & RawFile::filePath() const
{
    return m_filePath;
}

const char * RawFile::data() const
{
    if (!m_valid)
    {
        return nullptr;
    }

    return m_data.data();
}

size_t RawFile::size() const
{
    if (!m_valid)
    {
        return size_t(0);
    }

    return m_data.size();
}

bool RawFile::readFile()
{
    m_data.clear();

    if (!fs::readFile(m_filePath, m_data))
    {
        std::cerr << "Reading from file \"" << m_filePath << "\" failed." << std::endl;
        return false;
    }

    return true;
}


} // namespace cppassist
