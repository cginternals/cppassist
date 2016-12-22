
#include "ActionHelp.h"

#include <cppassist/cmdline/CommandLineProgram.h>


using namespace cppassist;


ActionHelp::ActionHelp()
: CommandLineAction("help", "Print help text")
, m_defaultOptions(*this)
, m_switchHelp("--help", "-h", "Print help text", CommandLineSwitch::NonOptional)
, m_paramCommand("command", CommandLineParameter::Optional)
{
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
