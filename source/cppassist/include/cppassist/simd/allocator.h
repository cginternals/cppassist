
#pragma once

#ifdef _MSC_VER
    #pragma warning (push)
    #pragma warning (disable: 4100) // 'identifier': unreferenced formal parameter
#endif


#include <cstddef>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


/**
 * @see http://jmabille.github.io/blog/2014/12/06/aligned-memory-allocator/
 */
template <class T, int N>
class CPPASSIST_TEMPLATE_API aligned_allocator
{
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    template <class U>
    struct rebind
    {
        typedef aligned_allocator<U,N> other;
    };

    inline aligned_allocator() throw() {}
    inline aligned_allocator(const aligned_allocator&) throw() {}

    template <class U>
    inline aligned_allocator(const aligned_allocator<U,N>&) throw() {}

    inline ~aligned_allocator() throw() {}

    inline pointer address(reference r) { return &r; }
    inline const_pointer address(const_reference r) const { return &r; }

    pointer allocate(size_type n, typename std::allocator<void>::const_pointer hint = 0);
    inline void deallocate(pointer p, size_type);

    inline void construct(pointer p, const_reference value) { new (p) value_type(value); }
    inline void destroy(pointer p) { p->~value_type(); }

    inline size_type max_size() const throw() { return size_type(-1) / sizeof(T); }

    inline bool operator==(const aligned_allocator&) { return true; }
    inline bool operator!=(const aligned_allocator& rhs) { return !operator==(rhs); }
};


} // namespace cppassist


#include <cppassist/simd/allocator.inl>

#ifdef _MSC_VER
    #pragma warning (pop)
#endif
