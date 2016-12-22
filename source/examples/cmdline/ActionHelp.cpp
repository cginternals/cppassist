
#include "ActionHelp.h"

#include <cppassist/cmdline/CommandLineProgram.h>


using namespace cppassist;


ActionHelp::ActionHelp(DefaultOptions & defaultOptions)
: CommandLineAction("help", "Print help text")
, m_defaultOptions(defaultOptions)
, m_switchHelp("--help", "-h", "Print help text", CommandLineSwitch::NonOptional)
, m_paramCommand("command", CommandLineParameter::Optional)
{
    m_defaultOptions.apply(*this);

    add(&m_switchHelp);
    add(&m_paramCommand);
}

ActionHelp::~ActionHelp()
{
}

int ActionHelp::execute(CommandLineProgram * program)
{
    CommandLineAction * forAction = nullptr;

    if (!m_paramCommand.value().empty())
    {
        forAction = program->getAction(m_paramCommand.value());
    }

    program->print(program->help(forAction));

    // Return success
    return 0;
}
