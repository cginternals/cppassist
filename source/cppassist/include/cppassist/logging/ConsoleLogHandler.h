#pragma once

#include <cppassist/cppassist_api.h>
#include <cppassist/logging/AbstractLogHandler.h>
#include <cppassist/logging/LogMessage.h>

namespace loggingzeug
{

/** \brief Writes LogMessages to stdout.

	This is the default LogMessage handler of loggingzeug.

	\see setLoggingHandler
	\see logging.h
*/
class CPPASSIST_API ConsoleLogHandler : public AbstractLogHandler
{
public:
    virtual void handle(const LogMessage & message) override;

protected:
    static std::string messagePrefix(const LogMessage & message);
    static std::string levelString(LogMessage::Level level);
};

} // namespace loggingzeug
