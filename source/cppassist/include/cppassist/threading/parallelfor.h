
#pragma once


#include <functional>
#include <vector>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


/**
*  @brief
*    Helper class to deduce function types with lambdas
*
*  @see
*    http://stackoverflow.com/questions/13358672/how-to-convert-a-lambda-to-an-stdfunction-using-templates
*/
template <typename T>
struct identity
{
    typedef T type;
};

/**
*  @brief
*    Get optimal number of threads for parallelization
*
*  @return
*    Number of threads
*/
CPPASSIST_API size_t getNumberOfThreads();

/**
*  @brief
*    Call a function on each iteration of a loop
*
*  @param[in] start
*    Start value
*  @param[in] end
*    End value (must be >= start!)
*  @param[in] callback
*    Function that is called on each iteration
*  @param[in] parallelize
*    `true` to parallelize the execution (if possible), else `false`
*
*  @remark
*    Both start and end must be enumerable typed that support the + operator.
*/
template<typename T>
void forEach(T start, T end, typename identity<std::function<void(T)>>::type callback, bool parallelize = true);

/**
*  @brief
*    Call a function on each iteration of a loop (parallelized in threads)
*
*  @param[in] start
*    Start value
*  @param[in] end
*    End value (must be >= start!)
*  @param[in] callback
*    Function that is called on each iteration
*
*  @remark
*    Both start and end must be enumerable typed that support the + operator.
*/
template<typename T>
void parallelFor(T start, T end, typename identity<std::function<void(T)>>::type callback);

/**
*  @brief
*    Call a function on each item of a list (parallelized in threads)
*
*  @param[in] elements
*    List of elements
*  @param[in] callback
*    Function that is called on each iteration
*/
template<typename T>
void parallelFor(const std::vector<T> & elements, typename identity<std::function<void(const T & element)>>::type callback);

/**
*  @brief
*    Call a function on each item of a list (parallelized in threads)
*
*  @param[in] elements
*    List of elements
*  @param[in] callback
*    Function that is called on each iteration
*/
template<typename T>
void parallelFor(std::vector<T> & elements, typename identity<std::function<void(T & element)>>::type callback);

/**
*  @brief
*    Call a function on each iteration of a loop (sequential)
*
*  @param[in] start
*    Start value
*  @param[in] end
*    End value (must be >= start!)
*  @param[in] callback
*    Function that is called on each iteration
*
*  @remark
*    Both start and end must be enumerable typed that support the + operator.
*/
template<typename T>
void sequentialFor(T start, T end, typename identity<std::function<void(T)>>::type callback);

/**
*  @brief
*    Call a function on each item of a list (sequential)
*
*  @param[in] elements
*    List of elements
*  @param[in] callback
*    Function that is called on each iteration
*/
template<typename T>
void sequentialFor(const std::vector<T> & elements, typename identity<std::function<void(const T & element)>>::type callback);

/**
*  @brief
*    Call a function on each item of a list (sequential)
*
*  @param[in] elements
*    List of elements
*  @param[in] callback
*    Function that is called on each iteration
*/
template<typename T>
void sequentialFor(std::vector<T> & elements, typename identity<std::function<void(T & element)>>::type callback);


} // namespace cppassist


#include <cppassist/threading/parallelfor.inl>
