
#include "DefaultOptions.h"


using namespace cppassist;


DefaultOptions::DefaultOptions()
: m_switchVerbose("--verbose", "-v", "Make output more verbose")
{
}

DefaultOptions::~DefaultOptions()
{
}

void DefaultOptions::apply(CommandLineAction & action)
{
    action.add(&m_switchVerbose);
}
