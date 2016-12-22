
#pragma once


#include <cppassist/cmdline/CommandLineAction.h>
#include <cppassist/cmdline/CommandLineSwitch.h>
#include <cppassist/cmdline/CommandLineParameter.h>


class Program;


/**
*  @brief
*    Command 'help'
*/
class ActionHelp : public cppassist::CommandLineAction
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] program
    *    Main program
    */
    ActionHelp(Program & program);

    /**
    *  @brief
    *    Destructor
    */
    ~ActionHelp();

    // Virtual cppassist::CommandLineAction functions
    virtual int execute() override;


protected:
    Program                         & m_program;
    cppassist::CommandLineSwitch      m_switchHelp;
    cppassist::CommandLineParameter   m_paramCommand;
};
