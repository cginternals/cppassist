
#include "Program.h"

#include <cppassist/cppassist-version.h>

#include <cppassist/logging/logging.h>


using namespace cppassist;


Program::Program()
: CommandLineProgram(
    "cmdline-example",
    "cmdline-example " CPPASSIST_VERSION,
    "cmdline-example demonstrates how to parse (complex) command line options using the CommandLineProgram class in cppassist.")
, m_switchVerbose("--verbose", "-v", "Make output more verbose")
, m_actionHelp(*this)
, m_actionCount(*this)
, m_actionCopy(*this)
{
    add(&m_actionHelp);
    add(&m_actionCount);
    add(&m_actionCopy);
}

Program::~Program()
{
}

void Program::addDefaultOptionsTo(CommandLineProgram & action)
{
    action.add(&m_switchVerbose);
}

int Program::executeAction(CommandLineProgram * action)
{
    // Set log level
    int logLevel = LogMessage::Info;

    if (m_switchVerbose.activated())
    {
        logLevel += m_switchVerbose.count();
    }

    setVerbosityLevel(logLevel);

    // Display verbosity level
    info() << "Verbosity level: " << m_switchVerbose.count() << std::endl;

    // Call action
    if (action)
    {
        return action->execute();
    }

    return 0;
}
