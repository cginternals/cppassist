
#include <cppassist/logging/logging.h>

#include <cassert>

#include <cppassist/logging/AbstractLogHandler.h>
#include <cppassist/logging/LogMessageBuilder.h>
#include <cppassist/logging/ConsoleLogHandler.h>


namespace
{
    cppassist::LogMessage::Level    l_verbosityLevel = cppassist::LogMessage::Info;
    cppassist::AbstractLogHandler * l_logHandler     = new cppassist::ConsoleLogHandler();
}


namespace cppassist
{


AbstractLogHandler * loggingHandler()
{
    return l_logHandler;
}

void setLoggingHandler(AbstractLogHandler* handler)
{
    delete l_logHandler;
    l_logHandler = handler;
}

LogMessage::Level verbosityLevel()
{
    return l_verbosityLevel;
}

void setVerbosityLevel(LogMessage::Level verbosity)
{
    l_verbosityLevel = verbosity;
}

LogMessageBuilder log(const std::string & context, LogMessage::Level level)
{
    return LogMessageBuilder(level, level <= l_verbosityLevel ? l_logHandler : nullptr, context);
}

LogMessageBuilder info(const std::string & context)
{
    return log(context, LogMessage::Info);
}

LogMessageBuilder debug(const std::string & context)
{
    return log(context, LogMessage::Debug);
}

LogMessageBuilder warning(const std::string & context)
{
    return log(context, LogMessage::Warning);
}

LogMessageBuilder critical(const std::string & context)
{
    return log(context, LogMessage::Critical);
}

LogMessageBuilder fatal(const std::string & context)
{
    return log(context, LogMessage::Fatal);
}


} // namespace cppassist
