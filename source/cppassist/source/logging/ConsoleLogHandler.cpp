#include <cppassist/logging/ConsoleLogHandler.h>

#include <iostream>

namespace loggingzeug
{

void ConsoleLogHandler::handle(const LogMessage & message)
{
    if (LogMessage::Info > message.level())
	    std::cerr << messagePrefix(message) << message.message() << std::endl;
    else
        std::cout << messagePrefix(message) << message.message() << std::endl;
}

std::string ConsoleLogHandler::messagePrefix(const LogMessage & message)
{
	std::string prefix = levelString(message.level());


	if (!message.context().empty())
	{
		if (!prefix.empty())
			prefix = prefix + " ";

		prefix = prefix + "[" + message.context() + "]";
	}

	if (prefix.empty())
		return prefix;

	return prefix + ": ";
}

std::string ConsoleLogHandler::levelString(LogMessage::Level level)
{
	switch (level)
	{
	case LogMessage::Fatal:
		return "#fatal";
	case LogMessage::Critical:
		return "#critical";
	case LogMessage::Warning:
		return "#warning";
	default:
		return "";
	}
}

} // namespace loggingzeug
