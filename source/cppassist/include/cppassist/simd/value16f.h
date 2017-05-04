
#pragma once


#include <zmmintrin.h>

#include <cppassist/simd/value.h>


namespace cppassist
{


template <>
class CPPASSIST_TEMPLATE_API value<float, 16>
{
public:
    static const auto simd_size = 16;
    using store_type = __m512;
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

    inline operator store_type();
    inline operator const store_type & () const;

protected:
    store_type m_value;
};


inline auto operator+(const value<float, 16> & first, const value<float, 16> & second) -> value<float, 16>;
inline auto operator-(const value<float, 16> & first, const value<float, 16> & second) -> value<float, 16>;
inline auto operator*(const value<float, 16> & first, const value<float, 16> & second) -> value<float, 16>;
inline auto operator/(const value<float, 16> & first, const value<float, 16> & second) -> value<float, 16>;

inline auto operator+(const value<float, 16> & first, const value<float, 16>::primitive_type & scalar) -> value<float, 16>;
inline auto operator-(const value<float, 16> & first, const value<float, 16>::primitive_type & scalar) -> value<float, 16>;
inline auto operator*(const value<float, 16> & first, const value<float, 16>::primitive_type & scalar) -> value<float, 16>;
inline auto operator/(const value<float, 16> & first, const value<float, 16>::primitive_type & scalar) -> value<float, 16>;

inline auto operator+(const value<float, 16>::primitive_type & scalar, const value<float, 16> & other) -> value<float, 16>;
inline auto operator-(const value<float, 16>::primitive_type & scalar, const value<float, 16> & other) -> value<float, 16>;
inline auto operator*(const value<float, 16>::primitive_type & scalar, const value<float, 16> & other) -> value<float, 16>;
inline auto operator/(const value<float, 16>::primitive_type & scalar, const value<float, 16> & other) -> value<float, 16>;

inline auto sqrt(const value<float, 16> & first) -> value<float, 16>;


} // namespace cppassist


#include <cppassist/simd/value16f.inl>
