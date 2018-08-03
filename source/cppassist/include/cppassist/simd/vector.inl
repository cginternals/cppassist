
#pragma once

#include <algorithm>
#include <functional>

#include <cppassist/threading/parallelfor.h>


namespace cppassist
{

template <typename T, size_t SIMD_SIZE>
vector<T, SIMD_SIZE>::vector()
: m_size(0)
{
}

template <typename T, size_t SIMD_SIZE>
vector<T, SIMD_SIZE>::vector(size_t count)
: m_size(count)
, m_data(count % simd_size == 0 ? count / simd_size : count / simd_size + 1)
{
}

template <typename T, size_t SIMD_SIZE>
vector<T, SIMD_SIZE>::vector(T * data, size_t count)
: m_size(count)
, m_data(count % simd_size == 0 ? count / simd_size : count / simd_size + 1)
{
    std::copy(data, data + count, m_data.begin());
}

template <typename T, size_t SIMD_SIZE>
vector<T, SIMD_SIZE>::vector(const vector & data)
: m_size(data.m_size)
, m_data(data.m_data)
{
}

template <typename T, size_t SIMD_SIZE>
vector<T, SIMD_SIZE>::vector(vector && data)
: m_size(std::move(data.m_size))
, m_data(std::move(data.m_data))
{
}

template <typename T, size_t SIMD_SIZE>
T * vector<T, SIMD_SIZE>::data()
{
    return reinterpret_cast<T *>(m_data.data());
}

template <typename T, size_t SIMD_SIZE>
const T * vector<T, SIMD_SIZE>::data() const
{
    return reinterpret_cast<const T *>(m_data.data());
}

template <typename T, size_t SIMD_SIZE>
size_t vector<T, SIMD_SIZE>::size() const
{
    return m_size;
}

template <typename T, size_t SIMD_SIZE>
void vector<T, SIMD_SIZE>::resize(size_t size)
{
    m_size = size;
    m_data.resize(size % simd_size == 0 ? size / simd_size : size / simd_size + 1);
}

template <typename T, size_t SIMD_SIZE>
bool vector<T, SIMD_SIZE>::empty()
{
    return m_data.empty();
}

template <typename T, size_t SIMD_SIZE>
void vector<T, SIMD_SIZE>::clear()
{
    m_size = 0;
    m_data.clear();
}

template <typename T, size_t SIMD_SIZE>
size_t vector<T, SIMD_SIZE>::chunkSize() const
{
    return m_data.size();
}

template <typename T, size_t SIMD_SIZE>
value<T, SIMD_SIZE> & vector<T, SIMD_SIZE>::chunk(size_t i)
{
    return m_data.at(i);
}

template <typename T, size_t SIMD_SIZE>
const value<T, SIMD_SIZE> & vector<T, SIMD_SIZE>::chunk(size_t i) const
{
    return m_data.at(i);
}

/*
template <typename T, size_t SIMD_SIZE>
T & vector<T, SIMD_SIZE>::at(size_t i)
{
    return m_data.at(i / simd_size).at(i % simd_size);
}

template <typename T, size_t SIMD_SIZE>
const T & vector<T, SIMD_SIZE>::at(size_t i) const
{
    return m_data.at(i / simd_size).at(i % simd_size);
}

template <typename T, size_t SIMD_SIZE>
T & vector<T, SIMD_SIZE>::operator[](size_t i)
{
    return m_data[i / simd_size][i % simd_size];
}

template <typename T, size_t SIMD_SIZE>
const T & vector<T, SIMD_SIZE>::operator[](size_t i) const
{
    return m_data[i / simd_size][i % simd_size];
}
*/

template <typename T, size_t SIMD_SIZE>
typename vector<T, SIMD_SIZE>::iterator vector<T, SIMD_SIZE>::begin()
{
    return m_data.begin();
}

template <typename T, size_t SIMD_SIZE>
typename vector<T, SIMD_SIZE>::const_iterator vector<T, SIMD_SIZE>::begin() const
{
    return m_data.begin();
}

template <typename T, size_t SIMD_SIZE>
typename vector<T, SIMD_SIZE>::iterator vector<T, SIMD_SIZE>::end()
{
    return m_data.end();
}

template <typename T, size_t SIMD_SIZE>
typename vector<T, SIMD_SIZE>::const_iterator vector<T, SIMD_SIZE>::end() const
{
    return m_data.end();
}

template <typename T, size_t SIMD_SIZE>
T * vector<T, SIMD_SIZE>::valueBegin()
{
    return data();
}

template <typename T, size_t SIMD_SIZE>
const T * vector<T, SIMD_SIZE>::valueBegin() const
{
    return data();
}

template <typename T, size_t SIMD_SIZE>
T * vector<T, SIMD_SIZE>::valueEnd()
{
    return data() + size();
}

template <typename T, size_t SIMD_SIZE>
const T * vector<T, SIMD_SIZE>::valueEnd() const
{
    return data() + size();
}

/*
template <typename T, size_t SIMD_SIZE>
T & vector<T, SIMD_SIZE>::front()
{
    return m_data.front();
}

template <typename T, size_t SIMD_SIZE>
const T & vector<T, SIMD_SIZE>::front() const
{
    return m_data.front();
}

template <typename T, size_t SIMD_SIZE>
T & vector<T, SIMD_SIZE>::back()
{
    return m_data.back();
}

template <typename T, size_t SIMD_SIZE>
const T & vector<T, SIMD_SIZE>::back() const
{
    return m_data.back();
}
*/


// Iterators


template <typename Callback, typename Vector, typename... Vectors>
inline void traverse(Callback callback, Vector && vector, Vectors && ... vectors)
{
    for (auto i = size_t(0); i < vector.chunkSize(); ++i)
    {
        callback(vector.chunk(i), vectors.chunk(i)...);
    }
}

template <typename Callback, typename Vector, typename... Vectors>
inline void traverse_mt(Callback callback, Vector && vector, Vectors && ... vectors)
{
    // circumvent compiler bug, see http://stackoverflow.com/questions/14191989/how-do-i-use-variadic-perfect-forwarding-into-a-lambda
#if defined(__GNUG__) && !defined(__clang__) && ((__GNUG__ == 4) && (__GNUC_MINOR__ <= 8))
    forEach(size_t(0), vector.chunkSize(),
        std::bind([&](size_t i, Vector && vector, Vectors&& ... vectors) {
            callback(vector.chunk(i), vectors.chunk(i)...);
        }, std::placeholders::_1, std::forward<Vector>(vector), std::forward<Vectors>(vectors)...)
        , true);
#else
    forEach(size_t(0), vector.chunkSize(), [&](size_t i)
    {
        callback(vector.chunk(i), vectors.chunk(i)...);
    }, true);
#endif
}


} // namespace cppassist
