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

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define INCLUDE_ORIGINAL
#include "simd_fastinvsqrt.h"

#define NUM_ITEMS 10000000

int main() {
    double elapsed_time;
    clock_t start_time;

    float *data = malloc(NUM_ITEMS * sizeof(float));
    float *result = malloc(NUM_ITEMS * sizeof(float));
    for (size_t i = 0; i < NUM_ITEMS; i++) {
        data[i] = (float)rand()/(float)RAND_MAX * 100;
    }

    start_time = clock();
    for (size_t i = 0; i < NUM_ITEMS; i++) {
        result[i] = Q_rsqrt(data[i]);
    }
    elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Q_rsqrt took(x) %fms\n", elapsed_time*1000.0);
    
    start_time = clock();
    for (size_t i = 0; i < NUM_ITEMS; i++) {
        result[i] = 1.0f/sqrtf(data[i]);
    }
    elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("1.0f/sqrtf(x) took %fms\n", elapsed_time*1000.0);

    start_time = clock();
    for (size_t i = 0; i < NUM_ITEMS; i += 4) {
        _mm_storeu_ps(&result[i], Q_rsqrt_sse(_mm_loadu_ps(&data[i])));
    }
    elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Q_rsqrt_sse(x) took %fms\n", elapsed_time*1000.0);


    start_time = clock();
    for (size_t i = 0; i < NUM_ITEMS; i += 4) {
        _mm_storeu_ps(&result[i], _mm_div_ps(_mm_set1_ps(1.0f), _mm_sqrt_ps(_mm_loadu_ps(&data[i]))));
    }
    elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("_mm_div_ps(_mm_set1_ps(1.0f), _mm_sqrt_ps(x)) took %fms\n", elapsed_time*1000.0);

    start_time = clock();
    for (size_t i = 0; i < NUM_ITEMS; i += 4) {
        _mm_storeu_ps(&result[i], _mm_rsqrt_ps(_mm_loadu_ps(&data[i])));
    }
    elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("_mm_rsqrt_ps(x) took %fms\n", elapsed_time*1000.0);

    free(data);
    free(result);

    return 0;
}
