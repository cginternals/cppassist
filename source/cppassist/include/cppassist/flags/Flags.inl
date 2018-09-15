
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


template <typename EnumType>
Flags<EnumType> makeFlags(EnumType value)
{
    return Flags<EnumType>(value);
}


} // namespace cppassist


// namespace
// {


template <typename EnumType>
auto operator|(const cppassist::Flags<EnumType> & flags1, EnumType flag2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flags1) | static_cast<underlying_type>(flag2));
}

template <typename EnumType>
auto operator|(EnumType flag1, const cppassist::Flags<EnumType> & flags2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flag1) | static_cast<underlying_type>(flags2));
}

template <typename EnumType>
auto operator|(const cppassist::Flags<EnumType> & flags1, const cppassist::Flags<EnumType> & flags2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flags1) | static_cast<underlying_type>(flags2));
}


template <typename EnumType>
auto operator&(EnumType flag1, const cppassist::Flags<EnumType> & flags2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flag1) & static_cast<underlying_type>(flags2));
}

template <typename EnumType>
auto operator&(const cppassist::Flags<EnumType> & flags1, EnumType flag2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flags1) & static_cast<underlying_type>(flag2));
}

template <typename EnumType>
auto operator&(const cppassist::Flags<EnumType> & flags1, const cppassist::Flags<EnumType> & flags2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flags1) & static_cast<underlying_type>(flags2));
}


template <typename EnumType>
auto operator^(EnumType flag1, const cppassist::Flags<EnumType> & flags2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flag1) ^ static_cast<underlying_type>(flags2));
}

template <typename EnumType>
auto operator^(const cppassist::Flags<EnumType> & flags1, EnumType flag2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flags1) ^ static_cast<underlying_type>(flag2));
}

template <typename EnumType>
auto operator^(const cppassist::Flags<EnumType> & flags1, const cppassist::Flags<EnumType> & flags2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flags1) ^ static_cast<underlying_type>(flags2));
}


// } // global namespace
