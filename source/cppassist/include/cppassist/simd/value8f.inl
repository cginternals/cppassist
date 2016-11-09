
#pragma once


namespace cppassist
{


value<float, 8>::value()
: m_value()
{
}

value<float, 8>::value(const value & value)
: m_value(value.m_value)
{
}

value<float, 8>::value(value && value)
: m_value(std::move(value.m_value))
{
}

value<float, 8>::value(const __m256 & value)
: m_value(value)
{
}

value<float, 8>::value(__m256 && value)
: m_value(std::move(value))
{
}

value<float, 8> & value<float, 8>::operator=(const value & value)
{
    m_value = value.m_value;

    return *this;
}

value<float, 8> & value<float, 8>::operator=(value && value)
{
    m_value = std::move(value.m_value);

    return *this;
}

value<float, 8> & value<float, 8>::operator=(const __m256 & value)
{
    m_value = value;

    return *this;
}

value<float, 8> & value<float, 8>::operator=(__m256 && value)
{
    m_value =std::move(value);

    return *this;
}

float * value<float, 8>::data()
{
    return reinterpret_cast<float *>(std::addressof(m_value));
}

const float * value<float, 8>::data() const
{
    return reinterpret_cast<const float *>(std::addressof(m_value));
}

float & value<float, 8>::at(size_t i)
{
    return *(data() + i);
}

const float & value<float, 8>::at(size_t i) const
{
    return *(data() + i);
}

float & value<float, 8>::operator[](size_t i)
{
    return *(data() + i);
}

const float & value<float, 8>::operator[](size_t i) const
{
    return *(data() + i);
}

value<float, 8>::operator __m256()
{
    return m_value;
}

value<float, 8>::operator const __m256 &() const
{
    return m_value;
}


// Operators


inline auto operator+(const value<float, 8> & first, const value<float, 8> & second) -> value<float, 8>
{
    return _mm256_add_ps(first.m_value, second.m_value);
}

inline auto operator-(const value<float, 8> & first, const value<float, 8> & second) -> value<float, 8>
{
    return _mm256_sub_ps(first.m_value, second.m_value);
}

inline auto operator*(const value<float, 8> & first, const value<float, 8> & second) -> value<float, 8>
{
    return _mm256_mul_ps(first.m_value, second.m_value);
}

inline auto operator/(const value<float, 8> & first, const value<float, 8> & second) -> value<float, 8>
{
    return _mm256_div_ps(first.m_value, second.m_value);
}

inline auto operator+(const value<float, 8> & first, const value<float, 8>::primitive_type & scalar) -> value<float, 8>
{
    return _mm256_add_ps(first.m_value, _mm256_set1_ps(scalar));
}

inline auto operator-(const value<float, 8> & first, const value<float, 8>::primitive_type & scalar) -> value<float, 8>
{
    return _mm256_sub_ps(first.m_value, _mm256_set1_ps(scalar));
}

inline auto operator*(const value<float, 8> & first, const value<float, 8>::primitive_type & scalar) -> value<float, 8>
{
    return _mm256_mul_ps(first.m_value, _mm256_set1_ps(scalar));
}

inline auto operator/(const value<float, 8> & first, const value<float, 8>::primitive_type & scalar) -> value<float, 8>
{
    return _mm256_div_ps(first.m_value, _mm256_set1_ps(scalar));
}

inline auto operator+(const value<float, 8>::primitive_type & scalar, const value<float, 8> & first) -> value<float, 8>
{
    return _mm256_add_ps(_mm256_set1_ps(scalar), first.m_value);
}

inline auto operator-(const value<float, 8>::primitive_type & scalar, const value<float, 8> & first) -> value<float, 8>
{
    return _mm256_sub_ps(_mm256_set1_ps(scalar), first.m_value);
}

inline auto operator*(const value<float, 8>::primitive_type & scalar, const value<float, 8> & first) -> value<float, 8>
{
    return _mm256_mul_ps(_mm256_set1_ps(scalar), first.m_value);
}

inline auto operator/(const value<float, 8>::primitive_type & scalar, const value<float, 8> & first) -> value<float, 8>
{
    return _mm256_div_ps(_mm256_set1_ps(scalar), first.m_value);
}

inline auto sqrt(const value<float, 8> & first) -> value<float, 8>
{
    return _mm256_sqrt_ps(first.m_value);
}


} // namespace cppassist
