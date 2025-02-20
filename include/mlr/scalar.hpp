#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <cstdbool>
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

#include <GL/glcorearb.h>
#include <GL/glu.h>
#include <GL/gl.h>

namespace stdx = std::experimental;
using namespace stdx::parallelism_v2;

namespace math
{

using f16      = GLhalf;
using f32      = GLfloat;
using f64      = GLdouble;

using s8       = GLbyte;
using u8       = GLubyte;
using i8       = GLbyte;

using s16      = GLshort;
using u16      = GLushort;
using i16      = GLshort;

using s32      = GLint;
using u32      = GLuint;
using i32      = GLint;

using s64      = GLint64;
using u64      = GLuint64;
using i64      = GLint64;

using ssz      = khronos_ssize_t;
using usz      = khronos_usize_t;
using sze      = GLsizei;

using sptr     = khronos_intptr_t;
using uptr     = khronos_uintptr_t;
using szeptr   = GLsizeiptr;
using syncptr  = GLsync;

using bf16     = GLushort;
using bf32     = GLbitfield;

using stime    = khronos_stime_nanoseconds_t;
using utime    = khronos_utime_nanoseconds_t;

using idx8     = GLubyte;
using idx16    = GLushort;
using idx      = GLuint;
using idx64    = u64;

using c8       = GLchar;
using enm      = GLenum;

using b8       = GLboolean;
using b32enm   = khronos_boolean_enum_t;

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

/* quake scalar type */
using qboolean        = b32enm;
const qboolean qfalse = KHRONOS_FALSE;
const qboolean qtrue  = KHRONOS_TRUE;
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

