
#include <cppassist/threading/parallelfor.h>


namespace threadingzeug
{


size_t getNumberOfThreads()
{
	return std::max(static_cast<size_t>(2), static_cast<size_t>(std::thread::hardware_concurrency()));
}


} // namespace threadingzeug
