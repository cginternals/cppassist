
#pragma once


#include <cppassist/cmdline/CommandLineProgram.h>

#include "ActionHelp.h"
#include "ActionCount.h"
#include "ActionCopy.h"


class Program : public cppassist::CommandLineProgram
{
public:
    Program();
    ~Program();


protected:
    ActionHelp  m_actionHelp;
    ActionCount m_actionCount;
    ActionCopy  m_actionCopy;
};
