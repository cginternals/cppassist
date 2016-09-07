
#include <cppassist/logging/logging.h>
#include <cppassist/io/SystemInfo.h>


using namespace cppassist;


int main(int, char * [])
{
    SystemInfo si;

    info() << "homeDir:   '" << si.homeDir() << "'";
    info() << "configDir: '" << si.configDir("DemoApp") << "'";

    return 0;
}
