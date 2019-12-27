
#include "ActionHelp.h"

#include <cppassist/cmdline/CommandLineProgram.h>

#include "Program.h"


using namespace cppassist;


ActionHelp::ActionHelp(Program & program)
: CommandLineProgram("help", "Print help text")
, m_program(program)
, m_switchHelp("--help", "-h", "Print help text", CommandLineSwitch::NonOptional)
, m_paramCommand("command", CommandLineParameter::Optional)
{
    m_program.addDefaultOptionsTo(*this);

    add(&m_switchHelp);
    add(&m_paramCommand);
}

ActionHelp::~ActionHelp()
{
}

int ActionHelp::execute()
{
    CommandLineProgram * forAction = nullptr;

    if (!m_paramCommand.value().empty())
    {
        forAction = m_program.getAction(m_paramCommand.value());
    }

    m_program.print(m_program.help(forAction));

    // Return success
    return 0;
}
