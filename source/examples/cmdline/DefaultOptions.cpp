
#include "DefaultOptions.h"


using namespace cppassist;


DefaultOptions::DefaultOptions(CommandLineAction & action)
: m_switchVerbose("--verbose", "-v", "Make output more verbose")
{
    action.add(&m_switchVerbose);
}

DefaultOptions::~DefaultOptions()
{
}
