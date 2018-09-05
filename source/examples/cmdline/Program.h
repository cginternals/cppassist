
#pragma once


#include <cppassist/cmdline/CommandLineProgram.h>
#include <cppassist/cmdline/CommandLineSwitch.h>

#include "ActionHelp.h"
#include "ActionCount.h"
#include "ActionCopy.h"


/**
*  @brief
*    Main program interface
*/
class Program : public cppassist::CommandLineProgram
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Program();

    /**
    *  @brief
    *    Destructor
    */
    ~Program();

    /**
    *  @brief
    *    Add default options to a program action
    *
    *  @param[in] action
    *    Command line action
    */
    void addDefaultOptionsTo(cppassist::CommandLineProgram & action);

    // Virtual cppassist::CommandLineProgram functions
    virtual int executeAction(cppassist::CommandLineProgram * action) override;


public:
    // Global options
    cppassist::CommandLineSwitch m_switchVerbose;

    // Actions
    ActionHelp     m_actionHelp;
    ActionCount    m_actionCount;
    ActionCopy     m_actionCopy;
};
