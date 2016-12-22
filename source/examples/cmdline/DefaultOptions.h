
#pragma once


#include <cppassist/cmdline/CommandLineAction.h>
#include <cppassist/cmdline/CommandLineSwitch.h>


namespace cppassist
{
    class CommandLineAction;
}


class DefaultOptions
{
public:
    DefaultOptions();
    ~DefaultOptions();

    void apply(cppassist::CommandLineAction & action);


public:
    cppassist::CommandLineSwitch m_switchVerbose;
};
