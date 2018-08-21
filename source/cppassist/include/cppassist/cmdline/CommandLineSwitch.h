
#pragma once


#include <string>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


/**
*  @brief
*    Command line switch
*
*    A command line switch is a binary option that can be turned on
*    by specifying the switch on the command line. It can have a
*    long and a short version. If the switch isn't specified
*    on the command line, it is turned off by default.
*
*    Example:
*      `myapp [--debug]`
*
*    @code
*      CommandLineSwitch switchDebug(
*          "--debug", "-d",
*          "Enabled debug mode",
*          CommandLineSwitch::Optional);
*    @endcode
*/
class CPPASSIST_API CommandLineSwitch
{
public:
    /**
    *  @brief
    *    State whether or not a switch is optional
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
    *    Long name (e.g., "--debug")
    *  @param[in] shortName
    *    Short name (e.g., "-d")
    *  @param[in] description
    *    Description text
    *  @param[in] optional
    *    Optional-state
    */
    CommandLineSwitch(
        const std::string & longName
      , const std::string & shortName
      , const std::string & description
      , OptionalState optional = Optional);

    /**
    *  @brief
    *    Destructor
    */
    ~CommandLineSwitch();

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
    *    String containing both the short and long name (e.g., "-d, --debug")
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
    *    Check if switch has been activated
    *
    *  @return
    *    `true` if activated, else `false`
    */
    bool activated() const;

    /**
    *  @brief
    *    Set if switch has been activated
    *
    *  @param[in] activated
    *    `true` if activated, else `false`
    */
    void setActivated(bool activated);

    /**
    *  @brief
    *    Get number of times the switch has been activated
    *
    *  @return
    *    Activation count
    */
    unsigned int count() const;

    /**
    *  @brief
    *    Set number of times the switch has been activated
    *
    *  @param[in] count
    *    Activation count
    */
    void setCount(unsigned int count);


protected:
    /**
    *  @brief
    *    Update #m_names
    */
    void updateNames();


protected:
    std::string   m_longName;    ///< Long name (e.g., "--debug")
    std::string   m_shortName;   ///< Short name (e.g., "-d")
    std::string   m_names;       ///< String containing both the short and long name (e.g., "-d, --debug")
    std::string   m_description; ///< Description text
    OptionalState m_optional;    ///< Optional-state
    bool          m_activated;   ///< `true` if activated, else `false`
    unsigned int  m_count;       ///< Activation count
};


} // namespace cppassist
