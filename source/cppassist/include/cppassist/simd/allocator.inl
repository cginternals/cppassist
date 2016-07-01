
#pragma once


#if defined(__GLIBC__) && ((__GLIBC__>=2 && __GLIBC_MINOR__ >= 8) || __GLIBC__>2) \
 && defined(__LP64__)
  #define GLIBC_MALLOC_ALREADY_ALIGNED 1
#else
  #define GLIBC_MALLOC_ALREADY_ALIGNED 0
#endif

#if defined(__FreeBSD__) && !defined(__arm__) && !defined(__mips__)
  #define FREEBSD_MALLOC_ALREADY_ALIGNED 1
#else
  #define FREEBSD_MALLOC_ALREADY_ALIGNED 0
#endif

/*
#if (defined(__APPLE__) \
 || defined(_WIN64) \
 || GLIBC_MALLOC_ALREADY_ALIGNED \
 || FREEBSD_MALLOC_ALREADY_ALIGNED)
  #define MALLOC_ALREADY_ALIGNED 1
#else
  #define MALLOC_ALREADY_ALIGNED 0
#endif
*/

#if ((defined __QNXNTO__) || (defined _GNU_SOURCE) || ((defined _XOPEN_SOURCE) && (_XOPEN_SOURCE >= 600))) \
 && (defined _POSIX_ADVISORY_INFO) && (_POSIX_ADVISORY_INFO > 0)
  #define HAS_POSIX_MEMALIGN 1
#else
  #define HAS_POSIX_MEMALIGN 0
#endif

#if SSE_INSTR_SET > 0
    #define HAS_MM_MALLOC 1
#else
    #define HAS_MM_MALLOC 0
#endif


namespace cppassist
{


namespace detail
{
    inline void* _aligned_malloc(size_t size, size_t alignment)
    {
        void* res = 0;
        void* ptr = malloc(size+alignment);
        if(ptr != 0)
        {
            res = reinterpret_cast<void*>((reinterpret_cast<size_t>(ptr) & ~(size_t(alignment-1))) + alignment);
            *(reinterpret_cast<void**>(res) - 1) = ptr;
        }
        return res;
    }

    inline void _aligned_free(void* ptr)
    {
        if(ptr != 0)
            free(*(reinterpret_cast<void**>(ptr)-1));
    }
}

inline void* aligned_malloc(size_t size, size_t alignment)
{
    #if MALLOC_ALREADY_ALIGNED
        (void)alignment;

        return malloc(size);
    #elif HAS_MM_MALLOC
        return _mm_malloc(size,alignment);
    #elif HAS_POSIX_MEMALIGN
        void* res;
        const int failed = posix_memalign(&res,size,alignment);
        if(failed) res = 0;
        return res;
    #elif (defined _MSC_VER)
        return _aligned_malloc(size, alignment);
    #else
        return detail::_aligned_malloc(size,alignment);
    #endif
}

inline void aligned_free(void* ptr)
{
    #if MALLOC_ALREADY_ALIGNED
        free(ptr);
    #elif HAS_MM_MALLOC
        _mm_free(ptr);
    #elif HAS_POSIX_MEMALIGN
        free(ptr);
    #elif defined(_MSC_VER)
        _aligned_free(ptr);
    #else
        detail::_aligned_free(ptr);
    #endif
}

template <class T, int N>
typename aligned_allocator<T,N>::pointer
aligned_allocator<T,N>::allocate(size_type n, typename std::allocator<void>::const_pointer hint)
{
    (void)hint;

    pointer res = reinterpret_cast<pointer>(aligned_malloc(sizeof(T)*n,N));
    if(res == 0)
        throw std::bad_alloc();
    return res;
}

template <class T, int N>
void
aligned_allocator<T,N>::deallocate(pointer p, size_type)
{
    aligned_free(p);
}


} // namespace cppassist
