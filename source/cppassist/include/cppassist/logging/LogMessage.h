
#pragma once


#include <string>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


/**
*  @brief
*    Representation of a log message
*
*    LogMessages are handled and dispatched by the global logging handler which
*    has to be a subclass of AbstractLogHandler.
*
*  @see logging.h
*  @see AbstractLogHandler
*/
class CPPASSIST_API LogMessage
{
public:
    /**
    *  @brief
    *    Log level
    */
    enum Level
    {
        Critical ///< Cricical errors
      , Error    ///< Errors
      , Warning  ///< Warnings
      , Info     ///< Info messages
      , Debug    ///< Debug messages (Use Debug + x for further debug levels)
    };


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] level
    *    Log level
    *  @param[in] message
    *    Log message
    *  @param[in] context
    *    User defined context string
    */
    LogMessage(int level, const std::string & message, const std::string & context);

    /**
    *  @brief
    *    Get log level of the message
    *
    *  @return
    *    Log level
    */
    int level() const;

    /**
    *  @brief
    *    Get log message
    *
    *  @return
    *    Log message
    */
    const std::string & message() const;

    /**
    *  @brief
    *    Get context of the log message
    *
    *  @return
    *    User defined context string
    */
    const std::string & context() const;


protected:
    int         m_level;   ///< Log level
    std::string m_message; ///< Log message
    std::string m_context; ///< User defined context string
};


} // namespace cppassist
