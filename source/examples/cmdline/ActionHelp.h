
#pragma once


#include <cppassist/cmdline/CommandLineProgram.h>
#include <cppassist/cmdline/CommandLineSwitch.h>
#include <cppassist/cmdline/CommandLineParameter.h>


class Program;


/**
*  @brief
*    Command 'help'
*/
class ActionHelp : public cppassist::CommandLineProgram
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

    // Virtual cppassist::CommandLineProgram functions
    virtual int execute() override;


protected:
    Program                         & m_program;
    cppassist::CommandLineSwitch      m_switchHelp;
    cppassist::CommandLineParameter   m_paramCommand;
};
