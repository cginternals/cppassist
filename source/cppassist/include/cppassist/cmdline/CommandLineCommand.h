
#pragma once


#include <string>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


/**
*  @brief
*    Command line command
*
*    A command decribes a certain function that can be invoked
*    by specifying the command name on the command line.
*
*    Example:
*      `myapp list`
*
*    @code
*      CommandLineCommand commandList("list");
*    @endcode
*/
class CPPASSIST_API CommandLineCommand
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Command name (e.g., "list")
    */
    CommandLineCommand(const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    ~CommandLineCommand();

    /**
    *  @brief
    *    Get command name
    *
    *  @return
    *    Command name (e.g., "list")
    */
    const std::string & name() const;

    /**
    *  @brief
    *    Set command name
    *
    *  @param[in] name
    *    Command name (e.g., "list")
    */
    void setName(const std::string & name);

    /**
    *  @brief
    *    Check if command has been activated
    *
    *  @return
    *    `true` if activated, else `false`
    */
    bool activated() const;

    /**
    *  @brief
    *    Set if command has been activated
    *
    *  @param[in] activated
    *    `true` if activated, else `false`
    */
    void setActivated(bool activated);


protected:
    std::string m_name;      ///< Command name (e.g., "list")
    bool        m_activated; ///< `true` if activated, else `false`
};


} // namespace cppassist
