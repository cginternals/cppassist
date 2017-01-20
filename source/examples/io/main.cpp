
#include <cppassist/logging/logging.h>
#include <cppassist/fs/SystemInfo.h>


using namespace cppassist;


int main(int, char * [])
{
    SystemInfo si;

    info() << "homeDir:   '" << si.homeDir() << "'";
    info() << "configDir: '" << si.configDir("DemoApp") << "'";

    return 0;
}
