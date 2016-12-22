
#pragma once


#include <cppassist/cmdline/CommandLineAction.h>
#include <cppassist/cmdline/CommandLineSwitch.h>


class DefaultOptions
{
public:
    DefaultOptions(cppassist::CommandLineAction & action);
    ~DefaultOptions();


public:
    cppassist::CommandLineSwitch m_switchVerbose;
};
