
#pragma once


#include <cppassist/cmdline/CommandLineSwitch.h>
#include <cppassist/cmdline/CommandLineParameter.h>

#include "DefaultOptions.h"


namespace cppassist
{
    class CommandLineProgram;
}


class ActionHelp : public cppassist::CommandLineAction
{
public:
    ActionHelp();
    ~ActionHelp();

    virtual int execute(cppassist::CommandLineProgram * program) override;


protected:
    DefaultOptions                  m_defaultOptions;
    cppassist::CommandLineSwitch    m_switchHelp;
    cppassist::CommandLineParameter m_paramCommand;
};
