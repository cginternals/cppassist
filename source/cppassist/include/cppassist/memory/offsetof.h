
#pragma once


#include <cstddef>


namespace cppassist
{


/**
*  @brief
*    Determines the offset of a member within a class
*
*  @param[in] member
*    Pointer to class member
*
*  @return
*    Offset of member
*/
template <typename Class, typename Type>
std::ptrdiff_t offset(Type Class::*member);


} // namespace cppassist


#include <cppassist/memory/offsetof.inl>
