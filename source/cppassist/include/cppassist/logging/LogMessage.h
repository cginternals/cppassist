#pragma once

#include <string>

#include <cppassist/cppassist_api.h>

namespace loggingzeug
{

/** \brief Encapsulates a simple log message and its severity level.

	LogMessages are handled and dispatched by the global logging handler which 
    has to be a subclass of AbstractLogHandler.

	\see logging.h
	\see AbstractLogHandler
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

	LogMessage(Level level, const std::string& message, const std::string& context);

	Level level() const;
	const std::string& message() const;
	const std::string& context() const;

protected:
	Level m_level;
	std::string m_message;
	std::string m_context;
};

} // namespace loggingzeug
