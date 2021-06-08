# simd_fastinvsqrt

SIMD (SSE) implementation of the infamous Fast Inverse Square Root algorithm from Quake III Arena.

## Why

Why not.

## How

[This](https://www.youtube.com/watch?v=p8u_k2LIZyo) video explains it well.

## Speed test

Here is the results of running `benchmark.c` with `-O2` on my hardware (and manually averaging 3 runs):

```
Q_rsqrt took(x) 99.410333ms
1.0f/sqrtf(x) took 35.515666ms
Q_rsqrt_sse(x) took 7.105333ms
_mm_div_ps(_mm_set1_ps(1.0f), _mm_sqrt_ps(x)) took 10.934666ms
_mm_rsqrt_ps(x) took 10.303000ms
```

We can clearly see that `Q_rsqrt_sse` easily beats every other method (in this test at least), being followed by SSE's native inverse square root function. With the original `Q_rsqrt` surprisingly taking the longest.

## Using it

If for some god forsaken reason you want to use this just include the `simd_fastinvsqrt.h` header in your program, define `INCLUDE_ORIGINAL` before including to bring in the original `Q_rsqrt` as well.
