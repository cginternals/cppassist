
#pragma once


#include <string>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


/**
*  @brief
*    Command line option
*
*    A command line option is a named value than can be
*    specified on the command line. It can have a long and
*    a short version. Immediatly after the option itself,
*    the value must be specified on the command line.
*
*    Example:
*      `myapp [--config-file <filename>]`
*
*    @code
*      CommandLineOption optionConfigFile(
*        "--config-file", "-c",
*        "filename",
*        "Specify path to configuration file",
*        CommandLineOption::Optional);
*    @endcode
*/
class CPPASSIST_API CommandLineOption
{
public:
    /**
    *  @brief
    *    State whether or not an option is optional
    */
    enum OptionalState
    {
        NonOptional = 0,
        Optional = 1
    };


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] longName
    *    Long name (e.g., "--config-file")
    *  @param[in] shortName
    *    Short name (e.g., "-c")
    *  @param[in] valueName
    *    Name of the value (only relevant for the help text)
    *  @param[in] description
    *    Description text
    *  @param[in] optional
    *    Optional-state
    */
    CommandLineOption(
        const std::string & longName
      , const std::string & shortName
      , const std::string & valueName
      , const std::string & description
      , OptionalState optional = Optional);

    /**
    *  @brief
    *    Destructor
    */
    ~CommandLineOption();

    /**
    *  @brief
    *    Get name
    *
    *  @return
    *    Long name if available, else short name
    */
    const std::string & name() const;

    /**
    *  @brief
    *    Get names
    *
    *  @return
    *    String containing both the short and long name (e.g., "-c, --config-file")
    */
    const std::string & names() const;

    /**
    *  @brief
    *    Get long name
    *
    *  @return
    *    Long name (e.g., "--config-file")
    */
    const std::string & longName() const;

    /**
    *  @brief
    *    Set long name
    *
    *  @param[in] longName
    *    Long name (e.g., "--config-file")
    */
    void setLongName(const std::string & longName);

    /**
    *  @brief
    *    Get short name
    *
    *  @return
    *    Short name (e.g., "-c")
    */
    const std::string & shortName() const;

    /**
    *  @brief
    *    Set short name
    *
    *  @param[in] shortName
    *    Short name (e.g., "-c")
    */
    void setShortName(const std::string & shortName);

    /**
    *  @brief
    *    Get value name
    *
    *  @return
    *    Value name (e.g., "filename")
    */
    const std::string & valueName() const;

    /**
    *  @brief
    *    Set value name
    *
    *  @param[in] name
    *    Value name (e.g., "filename")
    */
    void setValueName(const std::string & name);

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
    *    Check optional-flag
    *
    *  @return
    *    `true` if optional, else `false`
    */
    bool isOptional() const;

    /**
    *  @brief
    *    Check optional-flag
    *
    *  @return
    *    Optional-state
    */
    OptionalState optional() const;

    /**
    *  @brief
    *    Set optional-flag
    *
    *  @param[in] optional
    *    Optional-state
    */
    void setOptional(OptionalState optional);

    /**
    *  @brief
    *    Get value
    *
    *  @return
    *    Option value
    */
    const std::string & value() const;

    /**
    *  @brief
    *    Set value
    *
    *  @param[in] value
    *    Option value
    */
    void setValue(const std::string & value);


protected:
    /**
    *  @brief
    *    Update #m_names
    */
    void updateNames();


protected:
    std::string   m_longName;    ///< Long name (e.g., "--config-file")
    std::string   m_shortName;   ///< Short name (e.g., "-c")
    std::string   m_names;       ///< String containing both the short and long name (e.g., "-c, --config-file")
    std::string   m_valueName;   ///< Value name (e.g., "filename")
    std::string   m_description; ///< Description text
    OptionalState m_optional;    ///< Optional-state
    std::string   m_value;       ///< Option value
};


} // namespace cppassist
