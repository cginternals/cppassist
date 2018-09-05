
#pragma once


#include <cppassist/cmdline/CommandLineProgram.h>
#include <cppassist/cmdline/CommandLineCommand.h>
#include <cppassist/cmdline/CommandLineParameter.h>


class Program;


/**
*  @brief
*    Command 'cp'
*/
class ActionCopy : public cppassist::CommandLineProgram
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

    // Virtual cppassist::CommandLineProgram functions
    virtual int execute() override;


protected:
    Program                         & m_program;
    cppassist::CommandLineCommand     m_commandCopy;
    cppassist::CommandLineParameter   m_paramSrc;
};
