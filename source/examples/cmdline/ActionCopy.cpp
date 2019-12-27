
#include "ActionCopy.h"

#include <cppassist/logging/logging.h>

#include "Program.h"


using namespace cppassist;


ActionCopy::ActionCopy(Program & program)
: CommandLineProgram("cp", "Copy files")
, m_program(program)
, m_commandCopy("cp")
, m_paramSrc("path", CommandLineParameter::NonOptional)
{
    m_program.addDefaultOptionsTo(*this);

    setOptionalParametersAllowed(true);
    setOptionalParameterName("path");

    add(&m_commandCopy);
    add(&m_paramSrc);
}

ActionCopy::~ActionCopy()
{
}

int ActionCopy::execute()
{
    // Copy
    info() << "Let me copy that for you ...";
    info() << "- " << m_paramSrc.value();

    for (auto arg : unknownArguments())
    {
        info() << "- " << arg;
    }

    // Return success
    return 0;
}
