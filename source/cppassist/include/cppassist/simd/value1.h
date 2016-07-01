
#pragma once


#include <cppassist/simd/value.h>


namespace cppassist
{


template <>
class value<float, 1>
{
public:
    static const auto simd_size = 1;
    using store_type = float;
    using primitive_type = float;

public:
    value();
    value(const value & value);
    value(value && value);
    value(const store_type & value);
    value(store_type && value);

    value & operator=(const value & value);
    value & operator=(value && value);
    value & operator=(const store_type & value);
    value & operator=(store_type && value);

    primitive_type * data();
    const primitive_type * data() const;

    primitive_type & at(size_t i);
    const primitive_type & at(size_t i) const;

    primitive_type & operator[](size_t i);
    const primitive_type & operator[](size_t i) const;

    operator store_type();
    operator const store_type &() const;
    operator store_type &&() &&;

public:
    store_type m_value;
};


inline auto operator+(const value<float, 1> & first, const value<float, 1> & second) -> value<float, 1>;
inline auto operator-(const value<float, 1> & first, const value<float, 1> & second) -> value<float, 1>;
inline auto operator*(const value<float, 1> & first, const value<float, 1> & second) -> value<float, 1>;
inline auto operator/(const value<float, 1> & first, const value<float, 1> & second) -> value<float, 1>;

inline auto operator+(const value<float, 1> & first, const value<float, 1>::primitive_type & scalar) -> value<float, 1>;
inline auto operator-(const value<float, 1> & first, const value<float, 1>::primitive_type & scalar) -> value<float, 1>;
inline auto operator*(const value<float, 1> & first, const value<float, 1>::primitive_type & scalar) -> value<float, 1>;
inline auto operator/(const value<float, 1> & first, const value<float, 1>::primitive_type & scalar) -> value<float, 1>;

inline auto operator+(const value<float, 1>::primitive_type & scalar, const value<float, 1> & other) -> value<float, 1>;
inline auto operator-(const value<float, 1>::primitive_type & scalar, const value<float, 1> & other) -> value<float, 1>;
inline auto operator*(const value<float, 1>::primitive_type & scalar, const value<float, 1> & other) -> value<float, 1>;
inline auto operator/(const value<float, 1>::primitive_type & scalar, const value<float, 1> & other) -> value<float, 1>;

inline auto sqrt(const value<float, 1> & first) -> value<float, 1>;

} // namespace cppassist


#include <cppassist/simd/value1.inl>
