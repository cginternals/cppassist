
#include <cppassist/cmdline/ArgumentParser.h>


using namespace cppassist;


int main(int argc, char * argv[])
{
    ArgumentParser arguments;
    arguments.parse(argc, argv);

    arguments.print();

    return 0;
}
