
#pragma once


namespace cppassist
{


template<class T, class... Args>
typename detail::UniqueIf<T>::UniqueSingle make_unique(Args && ... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
typename detail::UniqueIf<T>::UniqueArrayUnknownBound make_unique(std::size_t n)
{
    using U = typename std::remove_extent<T>::type;
    return std::unique_ptr<T>(new U[n]());
}


} // namespace cppassist
