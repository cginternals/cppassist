
#pragma once


#include <cppassist/flags/Flags.h>


namespace cppassist
{


template <typename EnumType>
Flags<EnumType> operator|(EnumType flag1, EnumType flag2);
template <typename EnumType>
Flags<EnumType> operator|(const Flags<EnumType> & flags1, EnumType flag2);
template <typename EnumType>
Flags<EnumType> operator|(EnumType flag1, const Flags<EnumType> & flags2);
template <typename EnumType>
Flags<EnumType> operator|(const Flags<EnumType> & flags1, const Flags<EnumType> & flags2);

template <typename EnumType>
Flags<EnumType> operator&(EnumType flag1, EnumType flag2);
template <typename EnumType>
Flags<EnumType> operator&(EnumType flag1, const Flags<EnumType> & flags2);
template <typename EnumType>
Flags<EnumType> operator&(const Flags<EnumType> & flags1, EnumType flag2);
template <typename EnumType>
Flags<EnumType> operator&(const Flags<EnumType> & flags1, const Flags<EnumType> & flags2);

template <typename EnumType>
Flags<EnumType> operator^(EnumType flag1, EnumType flag2);
template <typename EnumType>
Flags<EnumType> operator^(EnumType flag1, const Flags<EnumType> & flags2);
template <typename EnumType>
Flags<EnumType> operator^(const Flags<EnumType> & flags1, EnumType flag2);
template <typename EnumType>
Flags<EnumType> operator^(const Flags<EnumType> & flags1, const Flags<EnumType> & flags2);


} // namespace cppassist


#include <cppassist/flags/operators.inl>
