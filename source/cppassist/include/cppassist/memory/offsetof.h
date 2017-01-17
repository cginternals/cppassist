
#pragma once


#include <cstddef>


namespace cppassist
{


template <typename Class, typename Type>
std::ptrdiff_t offset(Type Class::*member);


} // namespace cppassist


#include <cppassist/memory/offsetof.inl>
