
#pragma once


#ifdef AVX512_ENABLED
#include <zmmintrin.h>
#define CPPASSIST_SIMD_SIZE 16
#elif defined(AVX2_ENABLED)
#include <immintrin.h>
#define CPPASSIST_SIMD_SIZE 8
#elif defined(SSE_ENABLED)
#include <xmmintrin.h>
#define CPPASSIST_SIMD_SIZE 4
#else
// include nothing
#define CPPASSIST_SIMD_SIZE 1
#endif
