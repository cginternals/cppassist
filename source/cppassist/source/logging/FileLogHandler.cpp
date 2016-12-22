
#include <cppassist/logging/FileLogHandler.h>

#include <fstream>


namespace cppassist
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

} // namespace cppassist
