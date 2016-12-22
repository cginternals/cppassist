
#include "ActionCount.h"

#include <cppassist/logging/logging.h>

#include "Program.h"


using namespace cppassist;


ActionCount::ActionCount(Program & program)
: CommandLineAction("count", "Count from one number to another")
, m_program(program)
, m_commandCount("count")
, m_optionStep("--increment-by", "-i", "step", "Number that is added per iteration", CommandLineOption::Optional)
, m_paramFrom("from", CommandLineParameter::NonOptional)
, m_paramTo("to", CommandLineParameter::NonOptional)
{
    m_program.addDefaultOptionsTo(*this);

    add(&m_commandCount);
    add(&m_optionStep);
    add(&m_paramFrom);
    add(&m_paramTo);
}

ActionCount::~ActionCount()
{
}

int ActionCount::execute()
{
    // Display verbosity level
    info() << "Verbosity level: " << m_program.m_switchVerbose.count() << std::endl;

    // Count
    info() << "Let me count for you ..." << std::endl;

    // Return success
    return 0;
}
