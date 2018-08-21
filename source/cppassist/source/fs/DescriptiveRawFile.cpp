
#include <cppassist/fs/DescriptiveRawFile.h>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>


namespace
{


template<typename T>
T read(std::ifstream & stream)
{
    T value;
    stream.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
}

template<>
std::string read<std::string>(std::ifstream & stream)
{
    std::stringstream ss;
    char c;

    while (stream.good())
    {
        stream.get(c);
        if (c == '\0')
            break;

        ss << c;
    }

    return ss.str();
}

template <typename T>
void collectKeys(const std::map<std::string, T> & map, std::vector<std::string> & keys)
{
    std::transform(
        map.begin(),
        map.end(),
        std::back_inserter(keys),
        [](const typename std::map<std::string, T>::value_type & pair) { return pair.first; }
    );
}


} // namespace


namespace cppassist
{


uint16_t DescriptiveRawFile::s_signature = 0xC6F5;

DescriptiveRawFile::DescriptiveRawFile()
: m_filePath()
, m_parseProperties(false)
, m_valid(false)
{
}

DescriptiveRawFile::~DescriptiveRawFile()
{
}

bool DescriptiveRawFile::load(const std::string & filePath, bool parseProperties)
{
    m_filePath = filePath;
    m_parseProperties = parseProperties;

    return reload();
}

bool DescriptiveRawFile::reload()
{
    m_valid = readFile();

    return m_valid;
}

bool DescriptiveRawFile::isValid() const
{
    return m_valid;
}

const char * DescriptiveRawFile::data() const
{
    if (!m_valid)
    {
        return nullptr;
    }

    return m_data.data();
}

size_t DescriptiveRawFile::size() const
{
    if (!m_valid)
    {
        return size_t(0);
    }

    return m_data.size();
}

const std::string & DescriptiveRawFile::filePath() const
{
    if (!m_valid)
    {
        const static std::string emptyPath;
        return emptyPath;
    }

    return m_filePath;
}

const std::string & DescriptiveRawFile::stringProperty(const std::string & key) const
{
    return m_stringProperties.at(key);
}

int32_t DescriptiveRawFile::intProperty(const std::string & key) const
{
    return m_intProperties.at(key);
}

double DescriptiveRawFile::doubleProperty(const std::string & key) const
{
    return m_doubleProperties.at(key);
}

bool DescriptiveRawFile::hasStringProperty(const std::string & key) const
{
    return m_stringProperties.find(key) != m_stringProperties.end();
}

bool DescriptiveRawFile::hasIntProperty(const std::string & key) const
{
    return m_intProperties.find(key) != m_intProperties.end();
}

bool DescriptiveRawFile::hasDoubleProperty(const std::string & key) const
{
    return m_doubleProperties.find(key) != m_doubleProperties.end();
}

std::vector<std::string> DescriptiveRawFile::stringPropertyKeys() const
{
    std::vector<std::string> keys;

    collectKeys(m_stringProperties, keys);

    return keys;
}

std::vector<std::string> DescriptiveRawFile::intPropertyKeys() const
{
    std::vector<std::string> keys;

    collectKeys(m_intProperties, keys);

    return keys;
}

std::vector<std::string> DescriptiveRawFile::doublePropertyKeys() const
{
    std::vector<std::string> keys;

    collectKeys(m_doubleProperties, keys);

    return keys;
}

bool DescriptiveRawFile::readFile()
{
    std::ifstream ifs(m_filePath, std::ios::in | std::ios::binary);

    m_stringProperties.clear();
    m_intProperties.clear();
    m_doubleProperties.clear();
    m_data.clear();

    if (!ifs)
    {
        std::cerr << "Reading from file \"" << m_filePath << "\" failed." << std::endl;
        return false;
    }

    uint64_t offset = 0;

    if (read<uint16_t>(ifs) == s_signature)
    {
        offset = read<uint64_t>(ifs);

        if (m_parseProperties)
        {
            readProperties(ifs, offset);
        }
    }
    else
    {
        ifs.seekg(0);
    }

    readRawData(ifs, offset);

    ifs.close();

    return true;
}

void DescriptiveRawFile::readProperties(std::ifstream & ifs, uint64_t offset)
{
    while (ifs.tellg() < static_cast<int64_t>(offset) && ifs.good())
    {
        auto type = read<PropertyType>(ifs);

        std::string key = read<std::string>(ifs);

        switch (type)
        {
        case PropertyType::Integer:
            m_intProperties[key] = read<int32_t>(ifs);
            break;

        case PropertyType::Double:
            m_doubleProperties[key] = read<double>(ifs);
            break;

        case PropertyType::String:
            m_stringProperties[key] = read<std::string>(ifs);
            break;

        default:
            return;
        }
    }
}

void DescriptiveRawFile::readRawData(std::ifstream & ifs, uint64_t rawDataOffset)
{
    ifs.seekg(0, std::ios::end);

    size_t endPosition = ifs.tellg();
    const size_t size = endPosition - rawDataOffset;

    ifs.seekg(rawDataOffset, std::ios::beg);

    m_data.resize(size);

    ifs.read(const_cast<char*>(m_data.data()), size);
}


} // namespace cppassist
