
#pragma once


#include <string>
#include <vector>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


class CommandLineProgram;
class CommandLineCommand;
class CommandLineOption;
class CommandLineSwitch;
class CommandLineParameter;


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
    const std::vector<CommandLineProgram *> & actions() const;

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
    CommandLineProgram * getAction(const std::string & name) const;

    /**
    *  @brief
    *    Add action
    *
    *  @param[in] action
    *    Command line action (must NOT be null!)
    */
    void add(CommandLineProgram * action);

    /**
    *  @brief
    *    Get commands
    *
    *  @return
    *    List of commands
    */
    const std::vector<CommandLineCommand *> & commands() const;

    /**
    *  @brief
    *    Get command by name
    *
    *  @param[in] name
    *    Command name
    *
    *  @return
    *    Pointer to command, null on error
    */
    CommandLineCommand * getCommand(const std::string & name) const;

    /**
    *  @brief
    *    Add command
    *
    *  @param[in] command
    *    Command line command (must NOT be null!)
    */
    void add(CommandLineCommand * command);

    /**
    *  @brief
    *    Get options
    *
    *  @return
    *    List of options
    */
    const std::vector<CommandLineOption *> & options() const;

    /**
    *  @brief
    *    Get option by name
    *
    *  @param[in] name
    *    Option name
    *
    *  @return
    *    Pointer to option, null on error
    */
    CommandLineOption * getOption(const std::string & name) const;

    /**
    *  @brief
    *    Add option
    *
    *  @param[in] option
    *    Command line option (must NOT be null!)
    */
    void add(CommandLineOption * option);

    /**
    *  @brief
    *    Get switches
    *
    *  @return
    *    List of switches
    */
    const std::vector<CommandLineSwitch *> & switches() const;

    /**
    *  @brief
    *    Get switch by name
    *
    *  @param[in] name
    *    Switch name
    *
    *  @return
    *    Pointer to switch, null on error
    */
    CommandLineSwitch * getSwitch(const std::string & name) const;

    /**
    *  @brief
    *    Add switch
    *
    *  @param[in] sw
    *    Command line switch (must NOT be null!)
    */
    void add(CommandLineSwitch * sw);

    /**
    *  @brief
    *    Get parameters
    *
    *  @return
    *    List of parameters
    */
    const std::vector<CommandLineParameter *> & parameters() const;

    /**
    *  @brief
    *    Get parameter by name
    *
    *  @param[in] name
    *    Parameter name
    *
    *  @return
    *    Pointer to parameter, null on error
    */
    CommandLineParameter * getParameter(const std::string & name) const;

    /**
    *  @brief
    *    Get parameter by index
    *
    *  @param[in] index
    *    Parameter index
    *
    *  @return
    *    Pointer to parameter, null on error
    */
    CommandLineParameter * getParameter(size_t index) const;

    /**
    *  @brief
    *    Add parameter
    *
    *  @param[in] parameter
    *    Command line parameter (must NOT be null!)
    */
    void add(CommandLineParameter * parameter);

    /**
    *  @brief
    *    Check if optional parameters are allowed by the action
    *
    *  @return
    *    `true` if optional parameters are allowed, else `false`
    */
    bool optionalParametersAllowed() const;

    /**
    *  @brief
    *    Set if optional parameters are allowed by the action
    *
    *  @param[in] allowed
    *    `true` if optional parameters are allowed, else `false`
    */
    void setOptionalParametersAllowed(bool allowed);

    /**
    *  @brief
    *    Get optional parameter name
    *
    *  @return
    *    Parameter name (e.g., "path")
    */
    const std::string & optionalParameterName() const;

    /**
    *  @brief
    *    Set optional parameter name
    *
    *  @param[in] name
    *    Parameter name (e.g., "path")
    */
    void setOptionalParameterName(const std::string & name);

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
    virtual std::string help(CommandLineProgram * forAction = nullptr) const;

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
    *    Get usage text
    *
    *  @return
    *    Usage text
    */
    std::string usage() const;

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
    virtual int executeAction(CommandLineProgram * action);

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
    CommandLineProgram * selectedAction() const;

    /**
    *  @brief
    *    Get errors
    *
    *  @return
    *    List of parsing errors
    */
    const std::vector<std::string> & errors() const;

    /**
    *  @brief
    *    Check if action has been activated
    *
    *  @return
    *    `true` if activated, else `false`
    */
    bool activated() const;

    /**
    *  @brief
    *    Get optional parameters specified on the command line
    *
    *  @return
    *    List of optional parameters
    */
    const std::vector<std::string> & unknownArguments() const;

    /**
    *  @brief
    *    Execute action
    *
    *  @return
    *    Error code (0 on success)
    */
    virtual int execute();


protected:
    /**
    *  @brief
    *    Try to parse arguments
    *
    *  @param[in] args
    *    Arguments to parse.
    *
    *  @return
    *    `true` if parsing resulted in no errors, `false` otherwise
    */
    bool tryParse(std::vector<std::string> & args);

    /**
    *  @brief
    *    Check if this action has been activated
    *
    *  @return
    *    `true` if activated, else `false`
    */
    bool checkActivated();

    /**
    *  @brief
    *    Checks for errors and collects error messages
    *
    *  @see
    *    errors
    */
    void checkErrors();


protected:
    std::string                         m_name;                      ///< Program name
    std::string                         m_shortDesc;                 ///< Short description (e.g., version and license)
    std::string                         m_description;               ///< Description text
    CommandLineProgram                * m_selectedAction;            ///< Action that has been selected (can be null)
    std::vector<CommandLineProgram *>   m_actions;                   ///< List of registered actions
    std::vector<CommandLineCommand *>   m_commands;                  ///< List of commands
    std::vector<CommandLineOption *>    m_options;                   ///< List of options
    std::vector<CommandLineSwitch *>    m_switches;                  ///< List of switches
    std::vector<CommandLineParameter *> m_parameters;                ///< List of parameters
    bool                                m_optionalParametersAllowed; ///< `true` if optional parameters are allowed, else `false`
    std::string                         m_optionalParameterName;     ///< Name for optional parameters
    bool                                m_activated;                 ///< `true` if activated, else `false`
    std::vector<std::string>            m_unknownArgs;               ///< List of optional parameters
    std::vector<std::string>            m_errors;                    ///< List of parsing errors
};


} // namespace cppassist
