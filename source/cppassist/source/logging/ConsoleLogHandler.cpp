
#include <cppassist/logging/ConsoleLogHandler.h>

#include <iostream>


namespace cppassist
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

std::string ConsoleLogHandler::levelString(int level)
{
         if (level == LogMessage::Critical) return "#critical";
    else if (level == LogMessage::Error)    return "#error";
    else if (level == LogMessage::Warning)  return "#warning";
    else if (level >= LogMessage::Debug)    return "#debug";
    else                                    return "";
}


} // namespace cppassist
