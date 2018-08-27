
#include <cppassist/cmdline/CommandLineCommand.h>


namespace cppassist
{


CommandLineCommand::CommandLineCommand(const std::string & name)
: m_name(name)
, m_activated(false)
{
}

CommandLineCommand::~CommandLineCommand()
{
}

const std::string & CommandLineCommand::name() const
{
    return m_name;
}

void CommandLineCommand::setName(const std::string & name)
{
    m_name = name;
}

bool CommandLineCommand::activated() const
{
    return m_activated;
}

void CommandLineCommand::setActivated(bool activated)
{
    m_activated = activated;
}


} // namespace cppassist
