
#include <cppassist/cmdline/CommandLineParameter.h>


namespace cppassist
{


CommandLineParameter::CommandLineParameter(const std::string & name, CommandLineParameter::OptionalState optional)
: m_name(name)
, m_optional(optional)
, m_value("")
{
}

CommandLineParameter::~CommandLineParameter()
{
}

const std::string & CommandLineParameter::name() const
{
    return m_name;
}

void CommandLineParameter::setName(const std::string & name)
{
    m_name = name;
}

bool CommandLineParameter::isOptional() const
{
    return m_optional == Optional;
}

CommandLineParameter::OptionalState CommandLineParameter::optional() const
{
    return m_optional;
}

void CommandLineParameter::setOptional(CommandLineParameter::OptionalState optional)
{
    m_optional = optional;
}

const std::string & CommandLineParameter::value() const
{
    return m_value;
}

void CommandLineParameter::setValue(const std::string & value)
{
    m_value = value;
}


} // namespace cppassist
