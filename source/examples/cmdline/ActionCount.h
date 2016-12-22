
#pragma once


#include <cppassist/cmdline/CommandLineCommand.h>
#include <cppassist/cmdline/CommandLineOption.h>
#include <cppassist/cmdline/CommandLineParameter.h>

#include "DefaultOptions.h"


namespace cppassist
{
    class CommandLineProgram;
}


class ActionCount : public cppassist::CommandLineAction
{
public:
    ActionCount();
    ~ActionCount();

    virtual int execute(cppassist::CommandLineProgram * program) override;


protected:
    DefaultOptions                  m_defaultOptions;
    cppassist::CommandLineCommand   m_commandCount;
    cppassist::CommandLineOption    m_optionStep;
    cppassist::CommandLineParameter m_paramFrom;
    cppassist::CommandLineParameter m_paramTo;
};
