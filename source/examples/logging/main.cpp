
#include <cppassist/logging/logging.h>


using namespace cppassist;


int main(int, char * [])
{
    setVerbosityLevel(LogMessage::Debug + 2);

    critical() << "A normal critical message.";
    error() << "A normal error message.";
    warning() << "A normal warning message.";
    info() << "A normal info message.";
    debug() << "A normal debug message.";
    debug(1) << "Another debug message.";

    info("A") << "Info message from context A";
    warning("B") << "Warning from context B";
    critical("C") << "Critical message from context C";

    return 0;
}
