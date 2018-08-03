
#include <cppassist/cmdline/CommandLineOption.h>


namespace cppassist
{


CommandLineOption::CommandLineOption(const std::string & longName, const std::string & shortName, const std::string & valueName, const std::string & description, OptionalState optional)
: m_longName(longName)
, m_shortName(shortName)
, m_names("")
, m_valueName(valueName)
, m_description(description)
, m_optional(optional)
, m_value("")
{
    updateNames();
}

CommandLineOption::~CommandLineOption()
{
}

const std::string & CommandLineOption::name() const
{
    if (!m_longName.empty())
    {
        return m_longName;
    }
    else
    {
        return m_shortName;
    }
}

const std::string & CommandLineOption::names() const
{
    return m_names;
}

const std::string & CommandLineOption::longName() const
{
    return m_longName;
}

void CommandLineOption::setLongName(const std::string & longName)
{
    m_longName = longName;

    updateNames();
}

const std::string & CommandLineOption::shortName() const
{
    return m_shortName;
}

void CommandLineOption::setShortName(const std::string & shortName)
{
    m_shortName = shortName;

    updateNames();
}

const std::string & CommandLineOption::valueName() const
{
    return m_valueName;
}

void CommandLineOption::setValueName(const std::string & valueName)
{
    m_valueName = valueName;
}

const std::string & CommandLineOption::description() const
{
    return m_description;
}

void CommandLineOption::setDescription(const std::string & description)
{
    m_description = description;
}

bool CommandLineOption::isOptional() const
{
    return m_optional == Optional;
}

CommandLineOption::OptionalState CommandLineOption::optional() const
{
    return m_optional;
}

void CommandLineOption::setOptional(CommandLineOption::OptionalState optional)
{
    m_optional = optional;
}

const std::string & CommandLineOption::value() const
{
    return m_value;
}

void CommandLineOption::setValue(const std::string & value)
{
    m_value = value;
}

void CommandLineOption::updateNames()
{
    m_names = "";

    if (!m_shortName.empty()) m_names += m_shortName + ", ";
    else                      m_names += "    ";
    if (!m_longName.empty())  m_names += m_longName;
}


} // namespace cppassist
