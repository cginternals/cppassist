
#pragma once


#include <string>
#include <vector>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


class CommandLineCommand;
class CommandLineOption;
class CommandLineSwitch;
class CommandLineParameter;


/**
*  @brief
*    Command line action
*
*    Specifies an action that can be invoked on the command line.
*    An action is defined by a set of items (commands, options,
*    switches, and parameters), which may be present on the command line.
*    If all non-optional commands, switches, and options are found,
*    the action is invoked.
*
*    Example:
*      `myapp list <category> [<type>] [--show-details]`
*
*    @code
*      CommandLineAction actionList("list", "List objects");
*
*      CommandLineCommand cmdList("list")
*      actionList.add(&cmdList);
*
*      CommandLineParameter paramCategory(
*          "category",
*          CommandLineParameter::NonOptional
*      );
*      actionList.add(&paramCategory);
*
*      CommandLineParameter paramType("type", CommandLineParameter::Optional);
*      actionList.add(&paramType);
*
*      CommandLineSwitch swHelp(
*          "--show-details", "-d",
*          "Show detailed object information",
*          CommandLineSwitch::Optional
*      );
*      actionList.add(&swHelp);
*    @endcode
*/
class CPPASSIST_API CommandLineAction
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Program name
    *  @param[in] description
    *    Description text
    */
    CommandLineAction(const std::string & name = "", const std::string & description = "");

    /**
    *  @brief
    *    Destructor
    */
    virtual ~CommandLineAction();

    /**
    *  @brief
    *    Get action name
    *
    *  @return
    *    Action name
    */
    const std::string & name() const;

    /**
    *  @brief
    *    Set action name
    *
    *  @param[in] name
    *    Action name
    */
    void setName(const std::string & name);

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
    *    Check if there were any errors during parsing
    *
    *  @return
    *    `true` if errors have been found, else `false`
    */
    bool hasErrors() const;

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
    const std::vector<std::string> & optionalParameters() const;

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
    std::string                         m_name;                      ///< Action name
    std::string                         m_description;               ///< Description text
    std::vector<CommandLineCommand *>   m_commands;                  ///< List of commands
    std::vector<CommandLineOption *>    m_options;                   ///< List of options
    std::vector<CommandLineSwitch *>    m_switches;                  ///< List of switches
    std::vector<CommandLineParameter *> m_parameters;                ///< List of parameters
    bool                                m_optionalParametersAllowed; ///< `true` if optional parameters are allowed, else `false`
    std::string                         m_optionalParameterName;     ///< Name for optional parameters
    bool                                m_activated;                 ///< `true` if activated, else `false`
    std::vector<std::string>            m_optionalParameters;        ///< List of optional parameters
    std::vector<std::string>            m_errors;                    ///< List of parsing errors
};


} // namespace cppassist
