
#pragma once


#include <vector>

#include <cppassist/simd/simd.h>
#include <cppassist/simd/allocator.h>
#include <cppassist/simd/value.h>



namespace cppassist
{


template <typename T, size_t SIMD_SIZE = CPPASSIST_SIMD_SIZE>
class CPPASSIST_TEMPLATE_API vector
{
    static const auto simd_size = SIMD_SIZE;

public:
    using primitive_type = T;
    using value_type = value<primitive_type, simd_size>;
    using allocator = cppassist::aligned_allocator<value_type, simd_size * sizeof(primitive_type)>;
    using iterator = typename std::vector<value_type, allocator>::iterator;
    using const_iterator = typename std::vector<value_type, allocator>::const_iterator;
    using size_type = typename std::vector<value_type, allocator>::size_type;
    using reference = typename std::vector<value_type, allocator>::reference;
    using const_reference = typename std::vector<value_type, allocator>::const_reference;

public:
    vector();
    vector(size_t count);
    vector(T * data, size_t count);
    vector(const vector & data);
    vector(vector && data);

    T * data();
    const T * data() const;

    size_t size() const;
    void resize(size_t size);

    bool empty();
    void clear();

    size_t chunkSize() const;

    value<T, SIMD_SIZE> & chunk(size_t i);
    const value<T, SIMD_SIZE> & chunk(size_t i) const;

    /*
    T & at(size_t i);
    const T & at(size_t i) const;

    T & operator[](size_t i);
    const T & operator[](size_t i) const;

    T & front();
    const T & front() const;
    T & back();
    const T & back() const;
    */

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    T * valueBegin();
    const T * valueBegin() const;
    T * valueEnd();
    const T * valueEnd() const;
protected:
    size_t m_size;
    std::vector<value<T, simd_size>, allocator> m_data;
};


// Iterators

template <typename Callback, typename Vector, typename... Vectors>
inline void traverse(Callback callback, Vector && vector, Vectors && ... vectors);

template <typename Callback, typename Vector, typename... Vectors>
inline void traverse_mt(Callback callback, Vector && vector, Vectors && ... vectors);


} // namespace cppassist


#include <cppassist/simd/vector.inl>
