
#pragma once


#include <functional>
#include <vector>
#include <cstdint>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


CPPASSIST_API size_t getNumberOfThreads();


// Necessary for type deduction with lambdas
// see http://stackoverflow.com/questions/13358672/how-to-convert-a-lambda-to-an-stdfunction-using-templates
template <typename T>
struct identity
{
    typedef T type;
};

template<typename T>
void forEach(T start, T end, typename identity<std::function<void(T)>>::type callback, bool parallelize = true);

template<typename T>
void parallelFor(T start, T end, typename identity<std::function<void(T)>>::type callback);

template<typename T>
void parallelFor(const std::vector<T> & elements, typename identity<std::function<void(const T & element)>>::type callback);

template<typename T>
void parallelFor(std::vector<T> & elements, typename identity<std::function<void(T & element)>>::type callback);

template<typename T>
void sequentialFor(T start, T end, typename identity<std::function<void(T)>>::type callback);

template<typename T>
void sequentialFor(const std::vector<T> & elements, typename identity<std::function<void(const T & element)>>::type callback);

template<typename T>
void sequentialFor(std::vector<T> & elements, typename identity<std::function<void(T & element)>>::type callback);



} // namespace cppassist


#include <cppassist/threading/parallelfor.hpp>
