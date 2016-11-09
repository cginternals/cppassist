
#pragma once


namespace cppassist
{


value<float, 16>::value()
: m_value()
{
}

value<float, 16>::value(const value & value)
: m_value(value.m_value)
{
}

value<float, 16>::value(value && value)
: m_value(std::move(value.m_value))
{
}

value<float, 16>::value(const __m512 & value)
: m_value(value)
{
}

value<float, 16>::value(__m512 && value)
: m_value(std::move(value))
{
}

value<float, 16> & value<float, 16>::operator=(const value & value)
{
    m_value = value.m_value;

    return *this;
}

value<float, 16> & value<float, 16>::operator=(value && value)
{
    m_value = std::move(value.m_value);

    return *this;
}

value<float, 16> & value<float, 16>::operator=(const __m512 & value)
{
    m_value = value;

    return *this;
}

value<float, 16> & value<float, 16>::operator=(__m512 && value)
{
    m_value =std::move(value);

    return *this;
}

float * value<float, 16>::data()
{
    return reinterpret_cast<float *>(std::addressof(m_value));
}

const float * value<float, 16>::data() const
{
    return reinterpret_cast<const float *>(std::addressof(m_value));
}

float & value<float, 16>::at(size_t i)
{
    return *(data() + i);
}

const float & value<float, 16>::at(size_t i) const
{
    return *(data() + i);
}

float & value<float, 16>::operator[](size_t i)
{
    return *(data() + i);
}

const float & value<float, 16>::operator[](size_t i) const
{
    return *(data() + i);
}

value<float, 16>::operator __m512()
{
    return m_value;
}

value<float, 16>::operator const __m512 &() const
{
    return m_value;
}


// Operators


inline auto operator+(const value<float, 16> & first, const value<float, 16> & second) -> value<float, 16>
{
    return _mm512_add_ps(first.m_value, second.m_value);
}

inline auto operator-(const value<float, 16> & first, const value<float, 16> & second) -> value<float, 16>
{
    return _mm512_sub_ps(first.m_value, second.m_value);
}

inline auto operator*(const value<float, 16> & first, const value<float, 16> & second) -> value<float, 16>
{
    return _mm512_mul_ps(first.m_value, second.m_value);
}

inline auto operator/(const value<float, 16> & first, const value<float, 16> & second) -> value<float, 16>
{
    return _mm512_div_ps(first.m_value, second.m_value);
}

inline auto operator+(const value<float, 16> & first, const value<float, 16>::primitive_type & scalar) -> value<float, 16>
{
    return _mm512_add_ps(first.m_value, _mm512_set1_ps(scalar));
}

inline auto operator-(const value<float, 16> & first, const value<float, 16>::primitive_type & scalar) -> value<float, 16>
{
    return _mm512_sub_ps(first.m_value, _mm512_set1_ps(scalar));
}

inline auto operator*(const value<float, 16> & first, const value<float, 16>::primitive_type & scalar) -> value<float, 16>
{
    return _mm512_mul_ps(first.m_value, _mm512_set1_ps(scalar));
}

inline auto operator/(const value<float, 16> & first, const value<float, 16>::primitive_type & scalar) -> value<float, 16>
{
    return _mm512_div_ps(first.m_value, _mm512_set1_ps(scalar));
}

inline auto operator+(const value<float, 16>::primitive_type & scalar, const value<float, 16> & first) -> value<float, 16>
{
    return _mm512_add_ps(_mm512_set1_ps(scalar), first.m_value);
}

inline auto operator-(const value<float, 16>::primitive_type & scalar, const value<float, 16> & first) -> value<float, 16>
{
    return _mm512_sub_ps(_mm512_set1_ps(scalar), first.m_value);
}

inline auto operator*(const value<float, 16>::primitive_type & scalar, const value<float, 16> & first) -> value<float, 16>
{
    return _mm512_mul_ps(_mm512_set1_ps(scalar), first.m_value);
}

inline auto operator/(const value<float, 16>::primitive_type & scalar, const value<float, 16> & first) -> value<float, 16>
{
    return _mm512_div_ps(_mm512_set1_ps(scalar), first.m_value);
}

inline auto sqrt(const value<float, 16> & first) -> value<float, 4>
{
    return _mm512_sqrt_ps(first.m_value);
}


} // namespace cppassist
