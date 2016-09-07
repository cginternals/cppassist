
#pragma once

#include <cassert>


namespace cppassist
{


template <typename T, size_t SIMD_SIZE>
void add(const vector<T, SIMD_SIZE> & first, const vector<T, SIMD_SIZE> & second, vector<T, SIMD_SIZE> & result)
{
    assert(first.size() == second.size() && first.size() == result.size());

    for (auto i = size_t(0); i < result.chunkSize(); ++i)
    {
        result.chunk(i) = first.chunk(i) + second.chunk(i);
    }
}

template <typename T, size_t SIMD_SIZE>
void sub(const vector<T, SIMD_SIZE> & first, const vector<T, SIMD_SIZE> & second, vector<T, SIMD_SIZE> & result)
{
    assert(first.size() == second.size() && first.size() == result.size());

    for (auto i = size_t(0); i < result.chunkSize(); ++i)
    {
        result.chunk(i) = first.chunk(i) - second.chunk(i);
    }
}

template <typename T, size_t SIMD_SIZE>
void mul(const vector<T, SIMD_SIZE> & first, const vector<T, SIMD_SIZE> & second, vector<T, SIMD_SIZE> & result)
{
    assert(first.size() == second.size() && first.size() == result.size());

    for (auto i = size_t(0); i < result.chunkSize(); ++i)
    {
        result.chunk(i) = first.chunk(i) * second.chunk(i);
    }
}

template <typename T, size_t SIMD_SIZE>
void div(const vector<T, SIMD_SIZE> & first, const vector<T, SIMD_SIZE> & second, vector<T, SIMD_SIZE> & result)
{
    assert(first.size() == second.size() && first.size() == result.size());

    for (auto i = size_t(0); i < result.chunkSize(); ++i)
    {
        result.chunk(i) = first.chunk(i) / second.chunk(i);
    }
}

template <typename T, size_t SIMD_SIZE>
void add(const vector<T, SIMD_SIZE> & first, const typename vector<T, SIMD_SIZE>::primitive_type & scalar, vector<T, SIMD_SIZE> & result)
{
    assert(first.size() == result.size());

    for (auto i = size_t(0); i < result.chunkSize(); ++i)
    {
        result.chunk(i) = first.chunk(i) + scalar;
    }
}

template <typename T, size_t SIMD_SIZE>
void sub(const vector<T, SIMD_SIZE> & first, const typename vector<T, SIMD_SIZE>::primitive_type & scalar, vector<T, SIMD_SIZE> & result)
{
    assert(first.size() == result.size());

    for (auto i = size_t(0); i < result.chunkSize(); ++i)
    {
        result.chunk(i) = first.chunk(i) - scalar;
    }
}

template <typename T, size_t SIMD_SIZE>
void mul(const vector<T, SIMD_SIZE> & first, const typename vector<T, SIMD_SIZE>::primitive_type & scalar, vector<T, SIMD_SIZE> & result)
{
    assert(first.size() == result.size());

    for (auto i = size_t(0); i < result.chunkSize(); ++i)
    {
        result.chunk(i) = first.chunk(i) * scalar;
    }
}

template <typename T, size_t SIMD_SIZE>
void div(const vector<T, SIMD_SIZE> & first, const typename vector<T, SIMD_SIZE>::primitive_type & scalar, vector<T, SIMD_SIZE> & result)
{
    assert(first.size() == result.size());

    for (auto i = size_t(0); i < result.chunkSize(); ++i)
    {
        result.chunk(i) = first.chunk(i) / scalar;
    }
}

template <typename T, size_t SIMD_SIZE>
void add(const typename vector<T, SIMD_SIZE>::primitive_type & scalar, const vector<T, SIMD_SIZE> & first, vector<T, SIMD_SIZE> & result)
{
    assert(first.size() == result.size());

    for (auto i = size_t(0); i < result.chunkSize(); ++i)
    {
        result.chunk(i) = scalar + first.chunk(i);
    }
}

template <typename T, size_t SIMD_SIZE>
void sub(const typename vector<T, SIMD_SIZE>::primitive_type & scalar, const vector<T, SIMD_SIZE> & first, vector<T, SIMD_SIZE> & result)
{
    assert(first.size() == result.size());

    for (auto i = size_t(0); i < result.chunkSize(); ++i)
    {
        result.chunk(i) = scalar - first.chunk(i);
    }
}

template <typename T, size_t SIMD_SIZE>
void mul(const typename vector<T, SIMD_SIZE>::primitive_type & scalar, const vector<T, SIMD_SIZE> & first, vector<T, SIMD_SIZE> & result)
{
    assert(first.size() == result.size());

    for (auto i = size_t(0); i < result.chunkSize(); ++i)
    {
        result.chunk(i) = scalar * first.chunk(i);
    }
}

template <typename T, size_t SIMD_SIZE>
void div(const typename vector<T, SIMD_SIZE>::primitive_type & scalar, const vector<T, SIMD_SIZE> & first, vector<T, SIMD_SIZE> & result)
{
    assert(first.size() == result.size());

    for (auto i = size_t(0); i < result.chunkSize(); ++i)
    {
        result.chunk(i) = scalar / first.chunk(i);
    }
}

template <typename T, size_t SIMD_SIZE>
void sqrt(const vector<T, SIMD_SIZE> & first, vector<T, SIMD_SIZE> & result)
{
    assert(first.size() == result.size());

    for (auto i = size_t(0); i < result.chunkSize(); ++i)
    {
        result.chunk(i) = sqrt(first.chunk(i));
    }
}


} // namespace cppassist
