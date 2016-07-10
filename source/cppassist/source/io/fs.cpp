
#include <cppassist/io/fs.h>

#ifdef WIN32
    #include <stdlib.h>
    #include <stdio.h>
    #include <direct.h>
#else
    #include <sys/stat.h>
#endif


namespace cppassist
{


int makeDir(const std::string & path)
{
#ifdef WIN32
    return _mkdir(path.c_str());
#else
    return mkdir(path.c_str(), 0755);
#endif
}


} // namespace cppassist
