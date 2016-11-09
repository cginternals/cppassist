
#pragma once


#include <cmath>


namespace cppassist
{


value<float, 1>::value()
: m_value()
{
}

value<float, 1>::value(const value & value)
: m_value(value.m_value)
{
}

value<float, 1>::value(value && value)
: m_value(std::move(value.m_value))
{
}

value<float, 1>::value(const float & value)
: m_value(value)
{
}

value<float, 1>::value(float && value)
: m_value(std::move(value))
{
}

value<float, 1> & value<float, 1>::operator=(const value & value)
{
    m_value = value.m_value;

    return *this;
}

value<float, 1> & value<float, 1>::operator=(value && value)
{
    m_value = std::move(value.m_value);

    return *this;
}

value<float, 1> & value<float, 1>::operator=(const float & value)
{
    m_value = value;

    return *this;
}

value<float, 1> & value<float, 1>::operator=(float && value)
{
    m_value =std::move(value);

    return *this;
}

float * value<float, 1>::data()
{
    return std::addressof(m_value);
}

const float * value<float, 1>::data() const
{
    return std::addressof(m_value);
}

float & value<float, 1>::at(size_t i)
{
    return *(data() + i);
}

const float & value<float, 1>::at(size_t i) const
{
    return *(data() + i);
}

float & value<float, 1>::operator[](size_t i)
{
    return *(data() + i);
}

const float & value<float, 1>::operator[](size_t i) const
{
    return *(data() + i);
}

value<float, 1>::operator float()
{
    return m_value;
}

value<float, 1>::operator const float &() const
{
    return m_value;
}


// Operators


inline auto operator+(const value<float, 1> & first, const value<float, 1> & second) -> value<float, 1>
{
    return first.m_value + second.m_value;
}

inline auto operator-(const value<float, 1> & first, const value<float, 1> & second) -> value<float, 1>
{
    return first.m_value - second.m_value;
}

inline auto operator*(const value<float, 1> & first, const value<float, 1> & second) -> value<float, 1>
{
    return first.m_value * second.m_value;
}

inline auto operator/(const value<float, 1> & first, const value<float, 1> & second) -> value<float, 1>
{
    return first.m_value / second.m_value;
}

inline auto operator+(const value<float, 1> & first, const value<float, 1>::primitive_type & scalar) -> value<float, 1>
{
    return first.m_value + scalar;
}

inline auto operator-(const value<float, 1> & first, const value<float, 1>::primitive_type & scalar) -> value<float, 1>
{
    return first.m_value - scalar;
}

inline auto operator*(const value<float, 1> & first, const value<float, 1>::primitive_type & scalar) -> value<float, 1>
{
    return first.m_value * scalar;
}

inline auto operator/(const value<float, 1> & first, const value<float, 1>::primitive_type & scalar) -> value<float, 1>
{
    return first.m_value / scalar;
}

inline auto operator+(const value<float, 1>::primitive_type & scalar, const value<float, 1> & first) -> value<float, 1>
{
    return scalar + first.m_value;
}

inline auto operator-(const value<float, 1>::primitive_type & scalar, const value<float, 1> & first) -> value<float, 1>
{
    return scalar - first.m_value;
}

inline auto operator*(const value<float, 1>::primitive_type & scalar, const value<float, 1> & first) -> value<float, 1>
{
    return scalar * first.m_value;
}

inline auto operator/(const value<float, 1>::primitive_type & scalar, const value<float, 1> & first) -> value<float, 1>
{
    return scalar / first.m_value;
}

inline auto sqrt(const value<float, 1> & first) -> value<float, 1>
{
    return std::sqrt(first.m_value);
}


} // namespace cppassist
