
#include <cppassist/logging/logging.h>
#include <cppassist/fs/SystemInfo.h>


using namespace cppassist;


int main(int, char * [])
{
    info() << "homeDir:   '" << SystemInfo::homeDir() << "'";
    info() << "configDir: '" << SystemInfo::configDir("DemoApp") << "'";

    return 0;
}
