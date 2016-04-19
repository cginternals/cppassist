#pragma once

#include <cppassist/cppassist_api.h>
#include <cppassist/logging/AbstractLogHandler.h>
#include <cppassist/logging/LogMessage.h>

namespace cppassist
{

/** @brief
*     Writes LogMessages to a file (default: logfile.log).
*
*   @see setLoggingHandler
*   @see logging.h
*/
class CPPASSIST_API FileLogHandler : public AbstractLogHandler
{
public:
    /**
    *  @brief
    *    Constructor
    *  @param[in] logfile
    *
    */
    FileLogHandler(const std::string & logfile = "logfile.log");


    /**
    *  @brief
    *
    *  @param[in] message
    *
    */
    virtual void handle(const LogMessage & message) override;

protected:
    static std::string messagePrefix(const LogMessage & message);
    static std::string levelString(LogMessage::Level level);

    std::string m_logfile;
};

} // namespace cppassist
