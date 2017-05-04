
#pragma once


#include <memory>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


// based on the implementation from libc++ (MIT-licensed)


namespace detail
{


template<class T>
struct CPPASSIST_TEMPLATE_API UniqueIf
{
    using UniqueSingle = std::unique_ptr<T>;
};

template<class T>
struct CPPASSIST_TEMPLATE_API UniqueIf<T[]>
{
    using UniqueArrayUnknownBound = std::unique_ptr<T[]>;
};

template<class T, size_t N>
struct CPPASSIST_TEMPLATE_API UniqueIf<T[N]>
{
    using UniqueArrayKnownBound = void;
};


} // namespace detail


template<class T, class... Args>
typename detail::UniqueIf<T>::UniqueSingle make_unique(Args && ... args);

template<class T>
typename detail::UniqueIf<T>::UniqueArrayUnknownBound make_unique(std::size_t n);

template<class T, class... Args>
typename detail::UniqueIf<T>::UniqueArrayKnownBound make_unique(Args && ...) = delete;


} // namespace cppassist


#include <cppassist/memory/make_unique.inl>
