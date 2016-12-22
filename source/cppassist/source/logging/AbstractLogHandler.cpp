
#include <cppassist/logging/AbstractLogHandler.h>

#include <cppassist/logging/LogMessage.h>


namespace cppassist
{


AbstractLogHandler::AbstractLogHandler()
{
}

AbstractLogHandler::~AbstractLogHandler()
{
}

std::string AbstractLogHandler::messagePrefix(const LogMessage & message)
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

std::string AbstractLogHandler::levelString(int level)
{
         if (level == LogMessage::Critical) return "#critical";
    else if (level == LogMessage::Error)    return "#error";
    else if (level == LogMessage::Warning)  return "#warning";
    else if (level >= LogMessage::Debug)    return "#debug";
    else                                    return "";
}


} // namespace cppassist
