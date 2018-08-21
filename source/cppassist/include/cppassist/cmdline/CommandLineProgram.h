
#pragma once


#include <string>
#include <vector>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


class CommandLineAction;


/**
*  @brief
*    Command line program
*
*    This class can be used to define the logic of a command line program.
*/
class CPPASSIST_API CommandLineProgram
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Program name
    *  @param[in] shortDesc
    *    Short description (e.g., version and license)
    *  @param[in] description
    *    Description text
    *
    *  @remark
    *    If no name is set, the name will be set internally
    *    to the value of argv[0] when calling parse().
    */
    CommandLineProgram(const std::string & name = "", const std::string & shortDesc = "", const std::string & description = "");

    /**
    *  @brief
    *    Destructor
    */
    virtual ~CommandLineProgram();

    /**
    *  @brief
    *    Get program name
    *
    *  @return
    *    Program name
    */
    const std::string & name() const;

    /**
    *  @brief
    *    Set program name
    *
    *  @param[in] name
    *    Program name
    */
    void setName(const std::string & name);

    /**
    *  @brief
    *    Get short description
    *
    *  @return
    *    Short description (e.g., version and license)
    */
    const std::string & shortDesc() const;

    /**
    *  @brief
    *    Set short description
    *
    *  @param[in] shortDesc
    *    Short description (e.g., version and license)
    */
    void setShortDesc(const std::string & shortDesc);

    /**
    *  @brief
    *    Get description
    *
    *  @return
    *    Description text
    */
    const std::string & description() const;

    /**
    *  @brief
    *    Set description
    *
    *  @param[in] description
    *    Description text
    */
    void setDescription(const std::string & description);

    /**
    *  @brief
    *    Get actions
    *
    *  @return
    *    List of actions
    */
    const std::vector<CommandLineAction *> & actions() const;

    /**
    *  @brief
    *    Get action by name
    *
    *  @param[in] name
    *    Action name
    *
    *  @return
    *    Pointer to action, null on error
    */
    CommandLineAction * getAction(const std::string & name) const;

    /**
    *  @brief
    *    Add action
    *
    *  @param[in] action
    *    Command line action (must NOT be null!)
    */
    void add(CommandLineAction * action);

    /**
    *  @brief
    *    Get help text
    *
    *  @param[in] forAction
    *    Action for which help is requested, null for all actions
    *
    *  @return
    *    Help text
    *
    *  @remark
    *    By default, the help text contains the short description, the full
    *    program description, and the usage and options for each action.
    *    If help for a specific action is requested, only the usage and
    *    options for that action are given.
    *    You can change this behaviour by overriding this function.
    */
    virtual std::string help(CommandLineAction * forAction = nullptr) const;

    /**
    *  @brief
    *    Print message
    *
    *  @param[in] msg
    *    Message
    *
    *  @remark
    *    By default, the message is output to cppassist::info().
    *    The method can be overridden to change that.
    */
    virtual void print(const std::string & msg);

    /**
    *  @brief
    *    Reset state (forget all information from previous parsings)
    */
    void reset();

    /**
    *  @brief
    *    Parse command line
    *
    *  @param[in] argc
    *    Number of arguments
    *  @param[in] argv
    *    List of arguments
    */
    void parse(int argc, char * argv[]);

    /**
    *  @brief
    *    Execute command line program
    *
    *    This function parses the command line and executes the
    *    selected action. If no action was selected or there were
    *    parsing error, the help text is displayed and and error
    *    code (1) is returned.
    *
    *  @param[in] argc
    *    Number of arguments
    *  @param[in] argv
    *    List of arguments
    *
    *  @return
    *    Error code (0 on success)
    */
    int execute(int argc, char * argv[]);

    /**
    *  @brief
    *    Execute command line action
    *
    *    This function is called from execute(), when an action has
    *    been identified. Override this function to insert code that
    *    shall allways be executed (when no error has occured),
    *    regardless of the selected action. For example, a program
    *    can apply its global options here. Afterwards, the function
    *    is expected to call the specified action and return its
    *    error code.
    *
    *  @param[in] action
    *    Command line action to execute
    *
    *  @return
    *    Error code (0 on success)
    */
    virtual int executeAction(CommandLineAction * action);

    /**
    *  @brief
    *    Check if there were any errors during parsing
    *
    *  @return
    *    `true` if errors have been found, else `false`
    */
    bool hasErrors() const;

    /**
    *  @brief
    *    Get action that has been selected
    *
    *  @return
    *    Action, can be null
    */
    CommandLineAction * selectedAction() const;


protected:
    std::string                        m_name;           ///< Program name
    std::string                        m_shortDesc;      ///< Short description (e.g., version and license)
    std::string                        m_description;    ///< Description text
    std::vector<CommandLineAction *>   m_actions;        ///< List of registered actions
    CommandLineAction                * m_selectedAction; ///< Action that has been selected (can be null)
};


} // namespace cppassist
