#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <cmath>
#include <cstring>
#include <bit>
#include <array>
#include <numeric>
#include <algorithm>
#include <typeinfo>
#include <compare>
#include <string_view>
#include <experimental/simd>
#include <utility>
#include <iostream>
#include <filesystem>

namespace stdx = std::experimental;
using namespace stdx::parallelism_v2;

namespace math
{

//using f16      = _Float16;
using f32      = float;
using f64      = double;

using s8       = signed int8_t;
using u8       = uint8_t;
using i8       = int8_t;

using s16      = signed int16_t;
using u16      = uint16_t;
using i16      = int16_t;

using s32      = signed int32_t;
using u32      = uint32_t;
using i32      = int32_t;

using s64      = signed int64_t;
using u64      = uint64_t;
using i64      = int64_t;

using ssz      = ssize_t;
using usz      = size_t;
using sze      = int;

using sptr     = intptr_t;
using uptr     = uintptr_t;
using szeptr   = sptr;

using bf16     = u16;
using bf32     = u32;

using stime    = i64;
using utime    = u64;

using idx8     = uint8_t;
using idx16    = uint16_t;
using idx      = uint32_t;
using idx64    = uint64_t;

using c8       = char;
using enm      = unsigned int;

using b8       = bool;

typedef enum {
    MLR_FALSE = 0,
    MLR_TRUE  = 1,
    MLR_BOOLEAN_ENUM_FORCE_SIZE = 0x7FFFFFFF
} eb32;

#define MLR_CW  0x0900
#define MLR_CCW 0x0901

template<typename T>
concept iscalar = std::integral<T>;
template<typename T>
concept fscalar = std::floating_point<T>;
template<typename T>
concept scalar = iscalar<T> || fscalar<T>;
template<typename T>
concept container = requires(T t)
{
	std::begin(t);
	std::end(t);
};

enum channel
{
	R = 0,
	G = 1, 
	B = 2,
	A = 3,
};

};

