
#pragma once


namespace cppassist
{


/**
*  @brief
*    A compile-time list of types.
*
*    This is the default template for template specializations.
*/
template <typename... Types>
class TypeList;

/**
*  @brief
*    A compile-time list of types.
*
*    This is the template specialization for non-zero type lists.
*    There is an interface to call a template method invoke() on a Functor for each type in the type list.
*/
template <typename T, typename... Types>
class TypeList<T, Types...>
{
public:
    /**
    *  @brief
    *    Call the template method invoke() on the Functor for each type.
    *
    *  @param[in] callback
    *    The functor, supporting a templated method invoke()
    */
    template <typename Functor>
    static void apply(Functor && callback);
};

/**
*  @brief
*    A compile-time list of types.
*
*    This is the template specialization for a zero type list.
*    It is used as the recursion break condition.
*/
template <>
class TypeList<>
{
public:
    /**
    *  @brief
    *    Call the template method invoke() on the Functor for each type.
    *
    *    As this is the empty type list, no operator is called.
    *
    *  @param[in] callback
    *    The functor, supporting a templated method invoke()
    */
    template <typename Functor>
    static void apply(Functor && callback);
};


} // namespace cppassist


#include <cppassist/typelist/TypeList.inl>
