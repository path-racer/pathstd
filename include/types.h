/*
  Documentation: https://www.path.blog/docs/types.html
*/

#pragma once

#define EXPORT __declspec(dllexport)
#define U64_MAX 0xFFFFFFFFFFFFFFFFLLU
#define U32_MAX 0xFFFFFFFFU
#define I64_MAX 0x7FFFFFFFFFFFFFFFLL
#define I32_MAX 0x7FFFFFFF
#define SAME_TYPE(A, B) __is_same(A, B)

/**/
typedef signed __int32 Error;
typedef unsigned __int8   u8;
typedef   signed __int8   i8;
typedef unsigned __int16 u16;
typedef   signed __int16 i16;
typedef unsigned __int32 u32;
typedef   signed __int32 i32;
typedef unsigned __int64 u64;
typedef   signed __int64 i64;
typedef float  f32;
typedef double f64;
typedef char8_t utf8;

/**/
struct i32_2 { i32 x, y; };
struct i32_3 { i32 x, y, z; };
struct alignas(16) i32_4 { i32 x, y, z, w; };
struct alignas(32) i32_8 { i32_4 lo, hi; };
struct u32_2 { u32 x, y; };
struct u32_3 { u32 x, y, z; };
struct alignas(16) u32_4 { u32 x, y, z, w; };
struct alignas(32) u32_8 { u32_4 lo, hi; };
struct f32_2 { f32 x, y; };
struct f32_3 { f32 x, y, z; };
struct alignas(16) f32_4 { f32 x, y, z, w; };
struct alignas(32) f32_8 { f32_4 lo, hi; };

#define I4 __m128i
#define I8 __m256i
#define F4 __m128
#define F8 __m256