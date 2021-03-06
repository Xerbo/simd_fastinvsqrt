# simd_fastinvsqrt

SIMD (SSE) implementation of the infamous Fast Inverse Square Root algorithm from Quake III Arena.

## Why

Why not.

## How

[This](https://www.youtube.com/watch?v=p8u_k2LIZyo) video explains it well.

## Speed test

Here is the results of running `benchmark.c` compiled with `-O2` on my hardware:

```
Q_rsqrt took(x) 110.617000ms
1.0f/sqrtf(x) took 343.441000ms
Q_rsqrt_sse(x) took 31.145000ms
_mm_div_ps(_mm_set1_ps(1.0f), _mm_sqrt_ps(x)) took 85.942000ms
_mm_rsqrt_ps(x) took 13.855000ms
```

We can clearly see that `Q_rsqrt_sse` significantly faster (about 3.5x, the theoretical maximum being 4x) than the scalar version, with the fastest being SSE's native inverse square root function.

## Using it

If for some god forsaken reason you want to use this just include the `simd_fastinvsqrt.h` header in your program, define `INCLUDE_ORIGINAL` before including to bring in the original `Q_rsqrt` as well.
