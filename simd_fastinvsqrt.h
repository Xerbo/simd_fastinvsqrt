/*
 * simd_fastinvsqrt - SSE version of Quake III's Q_rsqrt function
 * Copyright (C) 2021 Xerbo (xerbo@protonmail.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SIMD_FASTINVSQRT_H
#define SIMD_FASTINVSQRT_H

#include <immintrin.h>

#ifdef INCLUDE_ORIGINAL
static inline float Q_rsqrt(float number) {
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( int * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}
#endif

static inline __m128 Q_rsqrt_sse(__m128 number) {
	__m128i i;
	__m128 x2, y;
	const __m128 threehalfs = _mm_set1_ps(1.5f);

	x2 = _mm_mul_ps(number, _mm_set_ps1(0.5f));
	y = number;
	i = *(__m128i *)&y;                                                          // evil floating point bit level hacking
	i = _mm_sub_epi32(_mm_set1_epi32(0x5f3759df), _mm_srli_epi32(i, 1));         // what the fuck?
	y = *(__m128 *)&i;
	y = _mm_mul_ps(y, _mm_sub_ps(threehalfs, _mm_mul_ps(x2, _mm_mul_ps(y, y)))); // 1st iteration
//	y = _mm_mul_ps(y, _mm_sub_ps(threehalfs, _mm_mul_ps(x2, _mm_mul_ps(y, y)))); // 2nd iteration, this can be removed

	return y;
}

#endif // SIMD_FASTINVSQRT_H
