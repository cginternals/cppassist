
#include "Program.h"

#include <cppassist/cppassist-version.h>


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

void Program::addDefaultOptionsTo(CommandLineAction & action)
{
    action.add(&m_switchVerbose);
}
