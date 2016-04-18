
#include <iostream>
#include <fstream>

#include <cppassist/cppassist-version.h>

#include <cppassist/baselib.h>


namespace cppassist
{


void printInfo()
{
    std::string dataPath = "data";

    // Library name
    std::cout << "Library cppassist::cppassist" << std::endl;
    std::cout << "========================================" << std::endl;

    // Library version
    std::cout << "Version: " << CPPASSIST_VERSION << std::endl;
    std::cout << std::endl;

    // Library type (static or dynamic)
    #ifdef CPPASSIST_STATIC_DEFINE
        std::cout << "Library type: STATIC" << std::endl;
    #else
        std::cout << "Library type: SHARED" << std::endl;
    #endif

    // Data directory
    std::cout << "Data path:    " << dataPath << std::endl;
    std::cout << std::endl;

    // Read file
    std::cout << "Data directory access" << std::endl;
    std::cout << "========================================" << std::endl;

    std::string fileName = dataPath + "/DATA_FOLDER.txt";
    std::cout << "Reading from '" << fileName << "': " << std::endl;
    std::cout << std::endl;

    std::ifstream f(fileName);
    if (f.is_open()) {
        std::string line;
        while (getline(f, line)) {
            std::cout << line << '\n';
        }
        f.close();
    } else {
        std::cout << "Unable to open file." << std::endl;
    }
}


} // namespace cppassist
