
#pragma once


#include <cppassist/logging/AbstractLogHandler.h>
#include <cppassist/logging/LogMessage.h>


namespace cppassist
{


/**
*  @brief
*    Log message handler that writes log messages to stdout
*
*    This is the default LogMessage handler of cppassist.
*
*  @see setLoggingHandler
*  @see logging.h
*/
class CPPASSIST_API ConsoleLogHandler : public AbstractLogHandler
{
public:
    // Virtual AbstractLogHandler interface
    virtual void handle(const LogMessage & message) override;


protected:
    static std::string messagePrefix(const LogMessage & message);
    static std::string levelString(int level);
};


} // namespace cppassist
