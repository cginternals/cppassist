
#pragma once


#if defined(CPPINTRINSICS_AVX512_ENABLED)
#include <zmmintrin.h>
#define CPPASSIST_SIMD_SIZE 16
#elif defined(CPPINTRINSICS_AVX2_ENABLED)
#include <immintrin.h>
#define CPPASSIST_SIMD_SIZE 8
#elif defined(CPPINTRINSICS_SSE_ENABLED)
#include <xmmintrin.h>
#define CPPASSIST_SIMD_SIZE 4
#else
// include nothing
#define CPPASSIST_SIMD_SIZE 1
#endif
