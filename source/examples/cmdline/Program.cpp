
#include "Program.h"

#include <cppassist/cppassist-version.h>


using namespace cppassist;


Program::Program()
: CommandLineProgram(
    "cmdline-example",
    "cmdline-example " CPPASSIST_VERSION,
    "cmdline-example demonstrates how to parse (complex) command line options using the CommandLineProgram class in cppassist.")
, m_actionHelp(m_defaultOptions)
, m_actionCount(m_defaultOptions)
, m_actionCopy(m_defaultOptions)
{
    add(&m_actionHelp);
    add(&m_actionCount);
    add(&m_actionCopy);
}

Program::~Program()
{
}
