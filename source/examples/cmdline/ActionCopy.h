
#pragma once


#include <cppassist/cmdline/CommandLineAction.h>
#include <cppassist/cmdline/CommandLineCommand.h>
#include <cppassist/cmdline/CommandLineParameter.h>


class Program;


/**
*  @brief
*    Command 'cp'
*/
class ActionCopy : public cppassist::CommandLineAction
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] program
    *    Main program
    */
    ActionCopy(Program & program);

    /**
    *  @brief
    *    Destructor
    */
    ~ActionCopy();

    // Virtual cppassist::CommandLineAction functions
    virtual int execute() override;


protected:
    Program                         & m_program;
    cppassist::CommandLineCommand     m_commandCopy;
    cppassist::CommandLineParameter   m_paramSrc;
};
