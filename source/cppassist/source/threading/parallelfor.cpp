
#include <cppassist/threading/parallelfor.h>

#include <algorithm>

namespace cppassist
{


size_t getNumberOfThreads()
{
    return std::max(static_cast<size_t>(2), static_cast<size_t>(std::thread::hardware_concurrency()));
}


} // namespace cppassist
