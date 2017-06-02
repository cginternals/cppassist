
#pragma once


namespace cppassist
{


template <typename EnumType>
Flags<EnumType> operator|(EnumType flag1, EnumType flag2)
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flag1) | static_cast<underlying_type>(flag2));
}

template <typename EnumType>
Flags<EnumType> operator|(const Flags<EnumType> & flags1, EnumType flag2)
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flags1) | static_cast<underlying_type>(flag2));
}

template <typename EnumType>
Flags<EnumType> operator|(EnumType flag1, const Flags<EnumType> & flags2)
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flag1) | static_cast<underlying_type>(flags2));
}

template <typename EnumType>
Flags<EnumType> operator|(const Flags<EnumType> & flags1, const Flags<EnumType> & flags2)
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flags1) | static_cast<underlying_type>(flags2));
}


template <typename EnumType>
Flags<EnumType> operator&(EnumType flag1, EnumType flag2)
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flag1) & static_cast<underlying_type>(flag2));
}

template <typename EnumType>
Flags<EnumType> operator&(EnumType flag1, const Flags<EnumType> & flags2)
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flag1) & static_cast<underlying_type>(flags2));
}

template <typename EnumType>
Flags<EnumType> operator&(const Flags<EnumType> & flags1, EnumType flag2)
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flags1) & static_cast<underlying_type>(flag2));
}

template <typename EnumType>
Flags<EnumType> operator&(const Flags<EnumType> & flags1, const Flags<EnumType> & flags2)
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flags1) & static_cast<underlying_type>(flags2));
}


template <typename EnumType>
Flags<EnumType> operator^(EnumType flag1, EnumType flag2)
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flag1) ^ static_cast<underlying_type>(flag2));
}

template <typename EnumType>
Flags<EnumType> operator^(EnumType flag1, const Flags<EnumType> & flags2)
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flag1) ^ static_cast<underlying_type>(flags2));
}

template <typename EnumType>
Flags<EnumType> operator^(const Flags<EnumType> & flags1, EnumType flag2)
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flags1) ^ static_cast<underlying_type>(flag2));
}

template <typename EnumType>
Flags<EnumType> operator^(const Flags<EnumType> & flags1, const Flags<EnumType> & flags2)
{
    using underlying_type = typename std::underlying_type<EnumType>::type;

    return static_cast<EnumType>(static_cast<underlying_type>(flags1) ^ static_cast<underlying_type>(flags2));
}


} // namespace cppassist
