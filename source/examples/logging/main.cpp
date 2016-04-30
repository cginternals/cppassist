
#include <cppassist/logging/logging.h>


using namespace cppassist;


int main(int, char * [])
{
    info() << "A normal info message.";
    debug() << "A normal debug message.";
    warning() << "A normal warning message.";
    critical() << "A normal critical message.";
    fatal() << "A normal fatal message." << std::endl;

    info("A") << "Info message from context A";
    warning("B") << "Warning from context B";
    fatal("C") << "Fatal message from context C";

    return 0;
}
