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
using bf32     = unsigned int;

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
concept scalar = std::integral<T> || std::floating_point<T>;
template<typename T>
concept iscalar = std::integral<T>;
template<typename T>
concept fscalar = std::floating_point<T>;
template<scalar T>
bool non_zero(T i) { return i != 0; }
template<size_t N>
concept power_of_two = (std::popcount(N) == 1);
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

namespace id
{
/* quake scalar type */
using qboolean        = eb32;
const qboolean qfalse = MLR_FALSE;
const qboolean qtrue  = MLR_TRUE;
using qint8_t         = i8;
using quint8_t        = u8;
using qint16_t        = i16;
using quint16_t       = u16;
using qint32_t        = i32;
using quint32_t       = u32;
using qint64_t        = i64;
using quint64_t       = u64;
using qintptr_t       = sptr;
using quintptr_t      = uptr;
using qssize_t        = ssz;
using qsize_t         = usz;
using qutime_ns_t     = utime;
using qstime_ns_t     = stime;
using qtime_ns_t      = qutime_ns_t;
using vecf_t          = f32;
using vecd_t          = f64;
using vec_t           = vecf_t;
using qbyte           = quint8_t;
using qindex          = idx;
using qint            = s32;
using qsizei          = sze;
using qbitfield32_t   = bf32;
using qbitfield16_t   = bf16;
};

};

