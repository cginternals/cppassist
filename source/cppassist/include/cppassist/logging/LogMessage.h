#pragma once

#include <string>

#include <cppassist/cppassist_api.h>

namespace cppassist
{

/**
*  @brief
*    Encapsulates a simple log message and its severity level.
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
    enum Level
    {
        Fatal,
        Critical,
        Warning,
        Debug,
        Info
    };

    /**
    *   @brief
    *     Constructor
    *   @param[in] level
    *
    *   @param[in] message
    *
    *   @param[in] context
    */
    LogMessage(Level level, const std::string& message, const std::string& context);

    /**
    *  @brief
    *
    *  @return
    *
    */
    Level level() const;

    /**
    *  @brief
    *
    *  @return
    *
    */
    const std::string& message() const;

    /**
    *  @brief
    *
    *  @return
    *
    */
    const std::string& context() const;

protected:
    Level m_level;
    std::string m_message;
    std::string m_context;
};

} // namespace cppassist
