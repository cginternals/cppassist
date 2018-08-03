
#pragma once


#include <thread>


namespace cppassist
{


#ifndef USE_OPENMP
    const auto numberOfThreads = getNumberOfThreads();
#endif


template<typename T>
void forEach(T start, T end, typename identity<std::function<void(T)>>::type callback, bool parallelize)
{
    (parallelize ?
        static_cast<void(*)(T, T, std::function<void(T)>)>(parallelFor) :
        static_cast<void(*)(T, T, std::function<void(T)>)>(sequentialFor)
    )(start, end, callback);
}

template<typename T>
void parallelFor(T start, T end, typename identity<std::function<void(T)>>::type callback)
{
#ifdef USE_OPENMP

    using signed_T = typename std::make_signed<T>::type;

    #pragma omp parallel for
    for (signed_T i = static_cast<signed_T>(start); i < static_cast<signed_T>(end); ++i)
    {
        callback(static_cast<T>(i));
    }

#else

    auto threads = std::vector<std::thread>(numberOfThreads);

    for (auto i = static_cast<size_t>(0); i < numberOfThreads; ++i)
    {
        threads[i] = std::thread([start, end, i, &callback] () {
            for (auto k = start + i; k < end; k += numberOfThreads)
            {
                callback(k);
            }
        });
    }

    for (auto & thread : threads)
    {
        thread.join();
    }

#endif
}

template<typename T>
void parallelFor(const std::vector<T> & elements, typename identity<std::function<void(const T & element)>>::type callback)
{
    parallelFor(0, elements.size(), [callback, &elements](size_t i) {
        callback(elements[i]);
    });
}

template<typename T>
void parallelFor(std::vector<T> & elements, typename identity<std::function<void(T & element)>>::type callback)
{
    parallelFor(0, elements.size(), [callback, &elements](size_t i) {
        callback(elements[i]);
    });
}

template<typename T>
void sequentialFor(T start, T end, typename identity<std::function<void(T)>>::type callback)
{
    for (auto i = start; i < end; ++i)
    {
        callback(i);
    }
}

template<typename T>
void sequentialFor(const std::vector<T> & elements, typename identity<std::function<void(const T & element)>>::type callback)
{
    sequentialFor(0, elements.size(), [callback, &elements](size_t i) {
        callback(elements[i]);
    });
}

template<typename T>
void sequentialFor(std::vector<T>& elements, typename identity<std::function<void(T& element)>>::type callback)
{
    sequentialFor(0, elements.size(), [callback, &elements](size_t i) {
        callback(elements[i]);
    });
}


} // namespace cppassist
