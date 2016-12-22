
#include "ActionCount.h"

#include <iostream>

#include <cppassist/logging/logging.h>


using namespace cppassist;


ActionCount::ActionCount()
: CommandLineAction("count", "Count from one number to another")
, m_defaultOptions(*this)
, m_commandCount("count")
, m_optionStep("--increment-by", "-i", "step", "Number that is added per iteration", CommandLineOption::Optional)
, m_paramFrom("from", CommandLineParameter::NonOptional)
, m_paramTo("to", CommandLineParameter::NonOptional)
{
    add(&m_commandCount);
    add(&m_optionStep);
    add(&m_paramFrom);
    add(&m_paramTo);
}

ActionCount::~ActionCount()
{
}

int ActionCount::execute(CommandLineProgram *)
{
    // Display verbosity level
    info() << "Verbosity level: " << m_defaultOptions.m_switchVerbose.count() << std::endl;

    // Count
    info() << "Let me count for you ..." << std::endl;

    // Return success
    return 0;
}
