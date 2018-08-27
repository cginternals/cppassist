
#include <cppassist/logging/logging.h>

#include <cppassist/logging/AbstractLogHandler.h>
#include <cppassist/logging/LogMessageBuilder.h>
#include <cppassist/logging/ConsoleLogHandler.h>


namespace
{
    int                             g_verbosityLevel = cppassist::LogMessage::Info;
    cppassist::AbstractLogHandler * g_logHandler     = new cppassist::ConsoleLogHandler();
}


namespace cppassist
{


AbstractLogHandler * loggingHandler()
{
    return g_logHandler;
}

void setLoggingHandler(AbstractLogHandler * handler)
{
    delete g_logHandler;
    g_logHandler = handler;
}

int verbosityLevel()
{
    return g_verbosityLevel;
}

void setVerbosityLevel(int verbosity)
{
    g_verbosityLevel = verbosity;
}

LogMessageBuilder log(int level, const std::string & context)
{
    return LogMessageBuilder(level, level <= g_verbosityLevel ? g_logHandler : nullptr, context);
}

LogMessageBuilder critical(const std::string & context)
{
    return log(LogMessage::Critical, context);
}

LogMessageBuilder error(const std::string & context)
{
    return log(LogMessage::Error, context);
}

LogMessageBuilder warning(const std::string & context)
{
    return log(LogMessage::Warning, context);
}

LogMessageBuilder info(const std::string & context)
{
    return log(LogMessage::Info, context);
}

LogMessageBuilder debug(const std::string & context)
{
    return log(LogMessage::Debug, context);
}

LogMessageBuilder debug(unsigned int debugLevel, const std::string & context)
{
    return log(LogMessage::Debug + debugLevel, context);
}


} // namespace cppassist
