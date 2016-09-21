
#include <cppassist/io/RawFile.h>

#include <fstream>
#include <iostream>

#include <cppassist/io/readfile.h>


namespace cppassist
{


RawFile::RawFile(const std::string & filePath)
: m_filePath(filePath)
, m_valid(false)
{
    m_valid = readFile();
}

RawFile::~RawFile()
{
}

bool RawFile::load()
{
    return readFile();
}

bool RawFile::load(const std::string & filePath)
{
    m_filePath = filePath;

    return readFile();
}

bool RawFile::reload()
{
    return readFile();
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
    if (!cppassist::readFile(m_filePath, m_data))
    {
        std::cerr << "Reading from file \"" << m_filePath << "\" failed." << std::endl;
        return false;
    }

    return true;
}


} // namespace cppassist
