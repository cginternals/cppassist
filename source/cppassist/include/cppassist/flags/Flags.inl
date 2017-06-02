
#pragma once


#include <numeric>


namespace cppassist
{


template <typename EnumType>
Flags<EnumType>::Flags()
: Flags(underlying_type(0))
{
}

template <typename EnumType>
Flags<EnumType>::Flags(EnumType value)
: Flags(static_cast<underlying_type>(value))
{
}

template <typename EnumType>
Flags<EnumType>::Flags(std::initializer_list<EnumType> values)
: Flags(std::accumulate(values.begin(), values.end(), static_cast<EnumType>(0), [](EnumType a, EnumType b) {
    return static_cast<EnumType>(static_cast<underlying_type>(a) | static_cast<underlying_type>(b));
}))
{
}

template <typename EnumType>
Flags<EnumType>::Flags(underlying_type value)
: m_value(value)
{
}

template <typename EnumType>
Flags<EnumType>::operator bool() const
{
    return static_cast<underlying_type>(m_value) != 0;
}

template <typename EnumType>
Flags<EnumType>::operator underlying_type() const
{
    return static_cast<underlying_type>(m_value);
}


} // namespace cppassist
