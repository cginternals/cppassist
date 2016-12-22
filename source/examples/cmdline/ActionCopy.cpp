
#include "ActionCopy.h"

#include <iostream>

#include <cppassist/logging/logging.h>


using namespace cppassist;


ActionCopy::ActionCopy()
: CommandLineAction("cp", "Copy files")
, m_defaultOptions(*this)
, m_commandCopy("cp")
, m_paramSrc("path", CommandLineParameter::NonOptional)
{
    setOptionalParametersAllowed(true);
    setOptionalParameterName("path");

    add(&m_commandCopy);
    add(&m_paramSrc);
}

ActionCopy::~ActionCopy()
{
}

int ActionCopy::execute(CommandLineProgram *)
{
    // Display verbosity level
    info() << "Verbosity level: " << m_defaultOptions.m_switchVerbose.count() << std::endl;

    // Copy
    info() << "Let me copy that for you ...";
    info() << "- " << m_paramSrc.value();

    for (auto arg : optionalParameters())
    {
        info() << "- " << arg;
    }

    // Return success
    return 0;
}
