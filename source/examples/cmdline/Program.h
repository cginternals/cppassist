
#pragma once


#include <cppassist/cmdline/CommandLineProgram.h>

#include "DefaultOptions.h"
#include "ActionHelp.h"
#include "ActionCount.h"
#include "ActionCopy.h"


class Program : public cppassist::CommandLineProgram
{
public:
    Program();
    ~Program();


protected:
    DefaultOptions m_defaultOptions;
    ActionHelp     m_actionHelp;
    ActionCount    m_actionCount;
    ActionCopy     m_actionCopy;
};
