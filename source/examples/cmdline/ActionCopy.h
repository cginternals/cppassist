
#pragma once


#include <cppassist/cmdline/CommandLineAction.h>
#include <cppassist/cmdline/CommandLineCommand.h>
#include <cppassist/cmdline/CommandLineParameter.h>

#include <DefaultOptions.h>


namespace cppassist
{
    class CommandLineProgram;
}


class ActionCopy : public cppassist::CommandLineAction
{
public:
    ActionCopy(DefaultOptions & defaultOptions);
    ~ActionCopy();

    virtual int execute(cppassist::CommandLineProgram * program) override;


protected:
    DefaultOptions                  & m_defaultOptions;
    cppassist::CommandLineCommand     m_commandCopy;
    cppassist::CommandLineParameter   m_paramSrc;
};
