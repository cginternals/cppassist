
#include <cppassist/logging/ConsoleLogHandler.h>

#include <iostream>


namespace cppassist
{


void ConsoleLogHandler::handle(const LogMessage & message)
{
    // For critical, error, and warning level
    if (message.level() < LogMessage::Info)
        std::cerr << messagePrefix(message) << message.message() << std::endl;
    else
        std::cout << messagePrefix(message) << message.message() << std::endl;
}


} // namespace cppassist
