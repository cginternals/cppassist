
#include <cppassist/cmdline/CommandLineSwitch.h>


namespace cppassist
{


CommandLineSwitch::CommandLineSwitch(const std::string & longName, const std::string & shortName, const std::string & description, OptionalState optional)
: m_longName(longName)
, m_shortName(shortName)
, m_names("")
, m_description(description)
, m_optional(optional)
, m_activated(false)
, m_count(0)
{
    updateNames();
}

CommandLineSwitch::~CommandLineSwitch()
{
}

const std::string & CommandLineSwitch::name() const
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

const std::string & CommandLineSwitch::names() const
{
    return m_names;
}

const std::string & CommandLineSwitch::longName() const
{
    return m_longName;
}

void CommandLineSwitch::setLongName(const std::string & longName)
{
    m_longName = longName;

    updateNames();
}

const std::string & CommandLineSwitch::shortName() const
{
    return m_shortName;
}

void CommandLineSwitch::setShortName(const std::string & shortName)
{
    m_shortName = shortName;

    updateNames();
}

const std::string & CommandLineSwitch::description() const
{
    return m_description;
}

void CommandLineSwitch::setDescription(const std::string & description)
{
    m_description = description;
}

bool CommandLineSwitch::isOptional() const
{
    return m_optional == Optional;
}

CommandLineSwitch::OptionalState CommandLineSwitch::optional() const
{
    return m_optional;
}

void CommandLineSwitch::setOptional(CommandLineSwitch::OptionalState optional)
{
    m_optional = optional;
}

bool CommandLineSwitch::activated() const
{
    return m_activated;
}

void CommandLineSwitch::setActivated(bool activated)
{
    m_activated = activated;
}

unsigned int CommandLineSwitch::count() const
{
    return m_count;
}

void CommandLineSwitch::setCount(unsigned int count)
{
    m_count = count;
}

void CommandLineSwitch::updateNames()
{
    m_names = "";

    if (!m_shortName.empty()) m_names += m_shortName + ", ";
    else                      m_names += "    ";
    if (!m_longName.empty())  m_names += m_longName;
}


} // namespace cppassist
