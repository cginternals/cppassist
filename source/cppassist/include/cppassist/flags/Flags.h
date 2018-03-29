
#pragma once


#include <initializer_list>
#include <type_traits>


namespace cppassist
{


template <typename EnumType>
class Flags
{
public:
    // Exposed for template parameter access in deducable contexts
    using type = EnumType; ///< enum type
    using underlying_type = typename std::underlying_type<EnumType>::type; ///< Underlying enum type

    /**
    *  @brief
    *    Constructor
    *
    *  Creates an empty flag object
    */
    constexpr Flags();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    The initial value of the flags object
    */
    constexpr Flags(EnumType value);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] values
    *    The initial values of the flags object
    *
    *  All values are 'or'-ed for the resulting value of the flags object
    */
    constexpr Flags(std::initializer_list<EnumType> values);

    /**
    *  @brief
    *    Conversion to bool for explicit contexts
    *
    *  @return
    *    'true' if at least one bit is set, else 'false'
    */
    constexpr explicit operator bool() const;

    /**
    *  @brief
    *    Conversion to underlying type
    *
    *  @return
    *    The internal value as underlying type
    */
    constexpr operator underlying_type() const;


protected:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    The value of the flags object
    */
    constexpr Flags(underlying_type value);


protected:
    underlying_type m_value; ///< The current value (a bit combination)

};


} // namespace cppassist


// namespace
// {


template <typename EnumType>
constexpr auto operator|(EnumType flag1, EnumType flag2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type;
template <typename EnumType>
constexpr auto operator|(const cppassist::Flags<EnumType> & flags1, EnumType flag2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type;
template <typename EnumType>
constexpr auto operator|(EnumType flag1, const cppassist::Flags<EnumType> & flags2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type;
template <typename EnumType>
constexpr auto operator|(const cppassist::Flags<EnumType> & flags1, const cppassist::Flags<EnumType> & flags2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type;

template <typename EnumType>
constexpr auto operator&(EnumType flag1, EnumType flag2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type;
template <typename EnumType>
constexpr auto operator&(EnumType flag1, const cppassist::Flags<EnumType> & flags2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type;
template <typename EnumType>
constexpr auto operator&(const cppassist::Flags<EnumType> & flags1, EnumType flag2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type;
template <typename EnumType>
constexpr auto operator&(const cppassist::Flags<EnumType> & flags1, const cppassist::Flags<EnumType> & flags2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type;

template <typename EnumType>
constexpr auto operator^(EnumType flag1, EnumType flag2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type;
template <typename EnumType>
constexpr auto operator^(EnumType flag1, const cppassist::Flags<EnumType> & flags2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type;
template <typename EnumType>
constexpr auto operator^(const cppassist::Flags<EnumType> & flags1, EnumType flag2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type;
template <typename EnumType>
constexpr auto operator^(const cppassist::Flags<EnumType> & flags1, const cppassist::Flags<EnumType> & flags2) -> typename std::enable_if<std::is_enum<EnumType>::value, cppassist::Flags<EnumType>>::type;


// } // global namespace


#include <cppassist/flags/Flags.inl>
