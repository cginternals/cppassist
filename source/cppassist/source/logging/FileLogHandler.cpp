#include <cppassist/logging/FileLogHandler.h>

#include <fstream>

namespace loggingzeug
{

FileLogHandler::FileLogHandler(const std::string & logfile)
: m_logfile(logfile)
{
}

void FileLogHandler::handle(const LogMessage & message)
{
	std::ofstream logstream(m_logfile, std::ios_base::out | std::ios_base::app );
	
    logstream << messagePrefix(message) << message.message() << std::endl;
}

std::string FileLogHandler::messagePrefix(const LogMessage & message)
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

std::string FileLogHandler::levelString(LogMessage::Level level)
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
