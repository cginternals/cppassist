
#pragma once


namespace cppassist
{


value<float, 4>::value()
: m_value()
{
}

value<float, 4>::value(const value & value)
: m_value(value.m_value)
{
}

value<float, 4>::value(value && value)
: m_value(std::move(value.m_value))
{
}

value<float, 4>::value(const __m128 & value)
: m_value(value)
{
}

value<float, 4>::value(__m128 && value)
: m_value(std::move(value))
{
}

value<float, 4> & value<float, 4>::operator=(const value & value)
{
    m_value = value.m_value;

    return *this;
}

value<float, 4> & value<float, 4>::operator=(value && value)
{
    m_value = std::move(value.m_value);

    return *this;
}

value<float, 4> & value<float, 4>::operator=(const __m128 & value)
{
    m_value = value;

    return *this;
}

value<float, 4> & value<float, 4>::operator=(__m128 && value)
{
    m_value =std::move(value);

    return *this;
}

float * value<float, 4>::data()
{
    return reinterpret_cast<float *>(std::addressof(m_value));
}

const float * value<float, 4>::data() const
{
    return reinterpret_cast<const float *>(std::addressof(m_value));
}

float & value<float, 4>::at(size_t i)
{
    return *(data() + i);
}

const float & value<float, 4>::at(size_t i) const
{
    return *(data() + i);
}

float & value<float, 4>::operator[](size_t i)
{
    return *(data() + i);
}

const float & value<float, 4>::operator[](size_t i) const
{
    return *(data() + i);
}

value<float, 4>::operator __m128()
{
    return m_value;
}

value<float, 4>::operator const __m128 &() const
{
    return m_value;
}


// Operators


inline auto operator+(const value<float, 4> & first, const value<float, 4> & second) -> value<float, 4>
{
    return _mm_add_ps(first.m_value, second.m_value);
}

inline auto operator-(const value<float, 4> & first, const value<float, 4> & second) -> value<float, 4>
{
    return _mm_sub_ps(first.m_value, second.m_value);
}

inline auto operator*(const value<float, 4> & first, const value<float, 4> & second) -> value<float, 4>
{
    return _mm_mul_ps(first.m_value, second.m_value);
}

inline auto operator/(const value<float, 4> & first, const value<float, 4> & second) -> value<float, 4>
{
    return _mm_div_ps(first.m_value, second.m_value);
}

inline auto operator+(const value<float, 4> & first, const value<float, 4>::primitive_type & scalar) -> value<float, 4>
{
    return _mm_add_ps(first.m_value, _mm_set1_ps(scalar));
}

inline auto operator-(const value<float, 4> & first, const value<float, 4>::primitive_type & scalar) -> value<float, 4>
{
    return _mm_sub_ps(first.m_value, _mm_set1_ps(scalar));
}

inline auto operator*(const value<float, 4> & first, const value<float, 4>::primitive_type & scalar) -> value<float, 4>
{
    return _mm_mul_ps(first.m_value, _mm_set1_ps(scalar));
}

inline auto operator/(const value<float, 4> & first, const value<float, 4>::primitive_type & scalar) -> value<float, 4>
{
    return _mm_div_ps(first.m_value, _mm_set1_ps(scalar));
}

inline auto operator+(const value<float, 4>::primitive_type & scalar, const value<float, 4> & first) -> value<float, 4>
{
    return _mm_add_ps(_mm_set1_ps(scalar), first.m_value);
}

inline auto operator-(const value<float, 4>::primitive_type & scalar, const value<float, 4> & first) -> value<float, 4>
{
    return _mm_sub_ps(_mm_set1_ps(scalar), first.m_value);
}

inline auto operator*(const value<float, 4>::primitive_type & scalar, const value<float, 4> & first) -> value<float, 4>
{
    return _mm_mul_ps(_mm_set1_ps(scalar), first.m_value);
}

inline auto operator/(const value<float, 4>::primitive_type & scalar, const value<float, 4> & first) -> value<float, 4>
{
    return _mm_div_ps(_mm_set1_ps(scalar), first.m_value);
}

inline auto sqrt(const value<float, 4> & first) -> value<float, 4>
{
    return _mm_sqrt_ps(first.m_value);
}


} // namespace cppassist
