
#pragma once


#include <cppassist/cppassist_api.h>
#include <cppassist/simd/simd.h>


namespace cppassist
{


template <typename T, size_t SIMD_SIZE>
class value;


} // namespace cppassist


#if CPPASSIST_SIMD_SIZE >= 16
#include <cppassist/simd/value16f.h>
#endif

#if CPPASSIST_SIMD_SIZE >= 8
#include <cppassist/simd/value8f.h>
#endif

#if CPPASSIST_SIMD_SIZE >= 4
#include <cppassist/simd/value4f.h>
#endif

#if CPPASSIST_SIMD_SIZE >= 1
#include <cppassist/simd/value1.h>
#endif
