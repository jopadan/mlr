#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdbool>
#include <ctime>
#include <cmath>
#include <array>
#include <utility>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <optional>
#include <iostream>
#include <string>
#include <bit>
#include <type_traits>
#include <experimental/simd>

#if defined(__SSE__)
#include <immintrin.h>
#else
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glcorearb.h>

namespace stdx = std::experimental;
using namespace stdx::parallelism_v2;

using qboolean        = khronos_boolean_enum_t;
const qboolean qfalse = KHRONOS_FALSE;
const qboolean qtrue  = KHRONOS_TRUE;
using qint8_t         = khronos_int8_t;
using quint8_t        = khronos_uint8_t;
using qint16_t        = khronos_int16_t;
using quint16_t       = khronos_uint16_t;
using qint32_t        = khronos_int32_t;
using quint32_t       = khronos_uint32_t;
using qint64_t        = khronos_int64_t;
using quint64_t       = khronos_uint64_t;
using qintptr_t       = khronos_intptr_t;
using quintptr_t      = khronos_uintptr_t;
using qssize_t        = khronos_ssize_t;
using qsize_t         = khronos_usize_t;
using qutime_ns_t     = khronos_utime_nanoseconds_t;
using qstime_ns_t     = khronos_stime_nanoseconds_t;
using qtime_ns_t      = qutime_ns_t;
using vecf_t          = khronos_float_t;
using vecd_t          = GLdouble;
using vec_t           = vecf_t;
using qbyte           = quint8_t;
using qindex          = GLuint;
using qint            = GLint;
using qsizei          = GLsizei;
using qbitfield32_t   = GLbitfield;
using qbitfield16_t   = quint16_t;

template<typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;
template<typename T>
concept scalar = arithmetic<T>;
template<typename T>
concept fscalar = std::floating_point<T>;
template<typename T>
concept iscalar = std::integral<T>;
template<size_t N>
concept power_of_two = (std::popcount(N) == 1);
template<scalar T>
bool non_zero(T i) { return i != 0; }


template<scalar T, size_t N>
struct col : vec<T, N>
{
	col() = default;
	col(std::initializer_list<T> src)
	{
		size_t i = 0;
		for(T s : src)
			(*this)[i++] = s;
	}
	col(uint16_t color, vec<uint8_t,4> bits = {5,6,5,0}, vec<uint8_t,4> perm = {0,1,2,3})
	{
		vec<uint8_t , 4> shift = { 0, bits[perm[0]], bits[perm[0]] + bits[perm[1]], bits[perm[0]] + bits[perm[1]] + bits[perm[2]] };
		vec<uint16_t, 4> mask  = { ((1 << bits[perm[0]]) - 1) << shift[0],
		                           ((1 << bits[perm[1]]) - 1) << shift[1],
					   ((1 << bits[perm[2]]) - 1) << shift[2],
					   ((1 << bits[perm[3]]) - 1) << shift[3] };
		for(size_t i = 0; i < std::min<size_t>(bits.size(),N); i++)
		{
			if(bits[perm[i]] != 0)
				(*this)[i] = static_cast<T>(lroundf((static_cast<float>(((color & mask[i]) >> shift[i])) / (1 << bits[perm[i]]) - 1) * UINT8_MAX));
		}
		if(bits[perm[3]] == 0)
			(*this) += (vec<T,N>::set1(UINT8_MAX) - (*this)) * (1 - static_cast<T>(lroundf((static_cast<float>(color & mask[3] >> shift[3]) / ((1 << bits[perm[3]]) - 1) * UINT8_MAX))));
	}
};
/*
template<sca T, size_t ROWS = 4, size_t COLS = 1>
using mat = std::conditional_t<COLS == 1, vec::vec<T, ROWS>, vec::vec<T, ROWS>[COLS]>;

using byte_vec4_t     = vec<qbyte, 4>;
using vec2_t          = vec<vec_t, 2>;
using vec3_t          = vec<vec_t, 3>;
using vec4_t          = vec<vec_t, 4>;
using vec5_t          = vec<vec_t, 5>;

using vec3f_t         = f32<3>;
using vec3d_t         = f64<3>;
using vec5f_t         = f32<5>;
using vec5d_t         = f64<5>;

using vec2f_t         = f32<2>;
using vec2d_t         = f64<2>;
using vec2i_t         = i32<2>;
using vec2u_t         = u32<2>;
using vec2l_t         = i64<2>;
using vec2lu_t        = u64<2>;

using vec4f_t         = f32<4>;
using vec4d_t         = f64<4>;
using vec4i_t         = i32<4>;
using vec4u_t         = u32<4>;
using vec4l_t         = i64<4>;
using vec4lu_t        = u64<4>;

using avec4_t         = vec4_t;
using avec3_t alignas(sizeof(vec_t) * 4) = vec3_t;

using qcolor4f        = vec4f_t;
using qcolor4b        = byte_vec4_t;


namespace col
{
	using fmt = std::pair<std::array<idx8<1>, 4>, std::array<idx8<1>, 4>>;

	static constexpr fmt rgb565       = {{0,1,2,3}, {5,6,5,0}};
	static constexpr fmt bgr565       = {{2,1,0,3}, {5,6,5,0}};

	static constexpr fmt rgba4444     = {{0,1,2,3}, {4,4,4,4}};
	static constexpr fmt bgra4444     = {{2,1,0,3}, {4,4,4,4}};
	static constexpr fmt argb4444     = {{3,0,1,2}, {4,4,4,4}};

	static constexpr fmt rgba8888     = {{0,1,2,3}, {8,8,8,8}};
	static constexpr fmt bgra8888     = {{2,1,0,3}, {8,8,8,8}};
	static constexpr fmt argb8888     = {{3,0,1,2}, {8,8,8,8}};

	static constexpr fmt rgba16161616 = {{0,1,2,3}, {16,16,16,16}};
	static constexpr fmt bgra16161616 = {{2,1,0,3}, {16,16,16,16}};
	static constexpr fmt argb16161616 = {{3,0,1,2}, {16,16,16,16}};

	static constexpr fmt rgbaf32      = {{0,1,2,3}, {32,32,32,32}};
	static constexpr fmt bgraf32      = {{2,1,0,3}, {32,32,32,32}};
	static constexpr fmt argbf32      = {{3,0,1,2}, {32,32,32,32}};

	static constexpr fmt rgbaf64      = {{0,1,2,3}, {64,64,64,64}};
	static constexpr fmt bgraf64      = {{2,1,0,3}, {64,64,64,64}};
	static constexpr fmt argbf64      = {{3,0,1,2}, {64,64,64,64}};

	template<fmt format = rgba8888, size_t N = 4>
	using u8  = u8<N>;
	template<fmt format = rgbaf32 , size_t N = 4>
	using f32  = f32<N>;
	template<fmt format = rgbaf64 , size_t N = 4>
	using f64  = f64<N>;

	enum index : uint8_t
	{
		r    =  0,
		g    =  1,
		b    =  2,
		a    =  3,
		rgba =  8,
		none = (uint8_t)-1,
	};

	template<fmt format>
	struct bitfield_color
	{
		static constexpr const std::array<idx8<1>,4> perm   = format.first;
		static constexpr const std::array<idx8<1>,4> bits   = format.second;
		static constexpr const size_t                  size = std::bit_ceil((unsigned)std::accumulate(bits.begin(), bits.end(), 0));
		static constexpr const size_t            components = std::count_if<bits.begin(), bits.end(), non_zero>;
		using element_type = std::make_unsigned_t<__int_with_sizeof_t<std::bit_ceil((unsigned)*std::max_element(bits.begin(), bits.end()))/8>>;
		using storage_type = std::make_unsigned_t<__int_with_sizeof_t<size/8>>;
		static constexpr std::array<idx8<1>, 4>   shift = {   0  , bits[perm[col::r]], (bits[perm[col::r]] + bits[perm[col::g]]), (bits[perm[col::r]] + bits[perm[col::g]] + bits[perm[col::b]]) };
		static constexpr std::array<storage_type, 4> mask = { ((1 << bits[perm[col::r]]) - 1) << 0,
			((1 << bits[perm[col::g]]) - 1) <<  bits[perm[col::r]],
			((1 << bits[perm[col::b]]) - 1) << (bits[perm[col::r]] + bits[perm[col::g]]),
			((1 << bits[perm[col::a]]) - 1) << (bits[perm[col::r]] + bits[perm[col::g]] + bits[perm[col::b]]) };

		union
		{
			struct
			{
				storage_type c0 : bits[perm[col::r]];
				storage_type c1 : bits[perm[col::g]];
				storage_type c2 : bits[perm[col::b]];
			};
			storage_type c3;
		};
		bitfield_color(element_type r = 0, element_type g = 0, element_type b = 0, element_type a = 0) : c3(0)
		{
			set(col::r, r);
			set(col::g, g);
			set(col::b, b);
			set(col::a, a);
		}
		inline constexpr         void set(size_t i, element_type val)
		{
			if(i == col::none) return;
			if(i >= col::rgba)
			{
				for(uint8_t j = 0; j <= col::a; j++)
					c3 |= (val << shift[perm[j]]) & mask[perm[j]];
				return;
			}
			c3 |= (val << shift[perm[i]]) & mask[perm[i]];
		}

		inline constexpr element_type get(size_t i) const
		{ 
			switch(perm[i])
			{
				case col::r: return c0; 
				case col::g: return c1;
				case col::b: return c2;
				case col::a: return ((c3 & mask[col::a]) >> shift[col::a]);
				default: return c3;
			}
		}
		inline constexpr element_type operator[](size_t i) const { return get(i); }

		inline constexpr element_type r() const { return get(col::r); }
		inline constexpr element_type g() const { return get(col::g); }
		inline constexpr element_type b() const { return get(col::b); }
		inline constexpr element_type a() const { return get(col::a); }

		inline constexpr operator vec4f_t() const
		{
			return (vec4f_t)
			{
				(vecf_t)r() / ((1 << bits[perm[col::r]]) - 1),
				(vecf_t)g() / ((1 << bits[perm[col::g]]) - 1),
				(vecf_t)b() / ((1 << bits[perm[col::b]]) - 1),
				(vecf_t)a() / ((1 << bits[perm[col::a]]) - 1)
			};
		}
		inline constexpr operator byte_vec4_t() const
		{
			return ubroundf<4>(((vec4f_t)(*this)) * UINT8_MAX);
		}
	};

	template<fmt format = rgb565>
	template<fmt format = rgba8888>
	using u32 = bitfield_color<format>;
	template<fmt format = rgba16161616>
	using u64 = bitfield_color<format>;

	};
};

#if defined (__SSE__)

#define _MM_TRANSPOSE4_PI(row0, row1, row2, row3)			\
do {									\
  __v4si __r0 = (row0), __r1 = (row1), __r2 = (row2), __r3 = (row3);	\
  __v4si __t0 = __builtin_ia32_unpcklpi (__r0, __r1);			\
  __v4si __t1 = __builtin_ia32_unpcklpi (__r2, __r3);			\
  __v4si __t2 = __builtin_ia32_unpckhpi (__r0, __r1);			\
  __v4si __t3 = __builtin_ia32_unpckhpi (__r2, __r3);			\
  (row0) = __builtin_ia32_movlhpi (__t0, __t1);				\
  (row1) = __builtin_ia32_movhlpi (__t1, __t0);				\
  (row2) = __builtin_ia32_movlhpi (__t2, __t3);				\
  (row3) = __builtin_ia32_movhlpi (__t3, __t2);				\
} while (0)

#endif

#if defined (__AVX__)

#define _MM_TRANSPOSE4_PD(row0, row1, row2, row3)			\
do {									\
  __v4df __r0 = (row0), __r1 = (row1), __r2 = (row2), __r3 = (row3);	\
  __v4df __t0 = __builtin_ia32_unpcklpd256 (__r0, __r1);		\
  __v4df __t1 = __builtin_ia32_unpcklpd256 (__r2, __r3);		\
  __v4df __t2 = __builtin_ia32_unpckhpd256 (__r0, __r1);		\
  __v4df __t3 = __builtin_ia32_unpckhpd256 (__r2, __r3);		\
  (row0) = __builtin_ia32_vperm2f128_pd256 (__t0, __t1, 0x20);		\
  (row1) = __builtin_ia32_vperm2f128_pd256 (__t2, __t3, 0x20);		\
  (row2) = __builtin_ia32_vperm2f128_pd256 (__t0, __t1, 0x31);		\
  (row3) = __builtin_ia32_vperm2f128_pd256 (__t2, __t3, 0x31);		\
} while (0)

#endif

#ifndef __AVX__
extern __inline __m256d __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm256_set_m128d     (__m128d __H, __m128d __L) { return (__m256d){ __L[0], __L[1], __H[0], __H[1] }; }
extern __inline __m128d __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm256_extractf128_pd(__m256d __X, const int __N)   { return _mm_load_pd(&__X[(__N * 2) % 4]); }
extern __inline __m256d __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm256_hadd_pd       (__m256d __X, __m256d __Y) { return (__m256d){ __X[0] + __X[1], __Y[0] + __Y[1], __X[2] + __X[3], __Y[2] + __Y[3] }; }
#endif

extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_select4_ps(__v4sf v, uint8_t i, uint8_t j, uint8_t k, uint8_t l) { return (__v4sf){v[i%4],v[j%4],v[k%4],v[l%4]}; }
extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_select3_ps(__v4sf v, uint8_t i, uint8_t j, uint8_t k) { return (__v4sf){v[i%4],v[j%4],v[k%4], 0}; }
extern __inline __v2sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_select2_ps(__v4sf v, uint8_t i, uint8_t j) { return (__v2sf){v[i%4],v[j%4]}; }
extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_select4_pd(__v4df v, uint8_t i, uint8_t j, uint8_t k, uint8_t l) { return (__v4df){v[i%4],v[j%4],v[k%4],v[l%4]}; }
extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_select3_pd(__v4df v, uint8_t i, uint8_t j, uint8_t k) { return (__v4df){v[i%4],v[j%4],v[k%4], 0}; }
extern __inline __v2df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_select2_pd(__v4df v, uint8_t i, uint8_t j) { return (__v2df){v[i%4],v[j%4]}; }

extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_4to3_ps(__v4sf v, double w = 0)
{
	if(w != 0 && v[3] != 0)
		return (__v4sf){ v[0] / w * v[3], v[1] / w * v[3], v[2] / w * v[3], w };
	return (__v4sf){ v[0], v[1], v[2], w };
}

extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_4to3_pd(__v4df v, double w = 0)
{
	if(w != 0 && v[3] != 0)
		return (__v4df){ v[0] / w * v[3], v[1] / w * v[3], v[2] / w * v[3], w };
	return (__v4df){ v[0], v[1], v[2], w };
}

extern __inline __m256d __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm256_dp_pd(__m256d __X, __m256d __Y, const int __M)
{
	__m256d cond  = { (__M & (1 << 4)) >> 4, (__M & (1 << 5)) >> 5, (__M & (1 << 6)) >> 6, (__M & (1 << 7)) >> 7};
	__m256d broad = { (__M & (1 << 0)) >> 0, (__M & (1 << 1)) >> 1, (__M & (1 << 2)) >> 2, (__M & (1 << 3)) >> 3};
	__m256d tmp = __X * __Y * cond;
	tmp = _mm256_hadd_pd(tmp, tmp);
	__m128d sum = _mm256_extractf128_pd(tmp, 0) + _mm256_extractf128_pd(tmp, 1);
	return _mm256_set_m128d(sum, sum) * broad;
}

extern __inline __v2sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_laplace2_ps(__v2sf __X) { return (__v2sf){ __X[1], __X[0] }; }
extern __inline __v2df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_laplace2_pd(__v2df __X) { return (__v2df){ __X[1], __X[0] }; }

extern __inline float __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_det2_ps(__v2sf a, __v2sf b)
{
	__v2sf dst = (__v2sf){ 1, -1 } * a * _mm_laplace2_ps(b);
	return dst[0] + dst[1];
}
extern __inline double __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_det2_pd(__v2df a, __v2df b)
{
	__v2df dst = (__v2df){ 1, -1 } * a * _mm_laplace2_pd(b);
	return dst[0] + dst[1];
}

extern __inline __v2sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_neg2_ps(__v2sf __X, uint8_t mod = 2, uint8_t val = 0)
{
	return (__v2sf){ (0 % mod == val) ? -__X[0] : __X[0],
	                 (1 % mod == val) ? -__X[1] : __X[1] };
}

extern __inline __v2df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_neg2_pd(__v2df __X, uint8_t mod = 2, uint8_t val = 0)
{
	return (__v2df) { (0 % mod == val) ? -__X[0] : __X[0],
	                  (1 % mod == val) ? -__X[1] : __X[1] };
}

extern __inline __v2sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_cross2_ps(__v2sf a, unsigned int winding = GL_CCW)
{
	return _mm_neg2_ps((__v2sf){1, 1}, 2, 1 - (winding % 2)) * _mm_laplace2_ps(a);
}

extern __inline __v2df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_cross2_pd(__v2df a, unsigned int winding = GL_CCW)
{
	return _mm_neg2_pd((__v2df){1, 1}, 2, 1 - (winding % 2)) * _mm_laplace2_pd(a);
}

extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_laplace3_ps(__v4sf __X, __v4sf __Y)
{
	__v4sf dst  = { _mm_det2_ps(_mm_select2_ps(__X,1,2), _mm_select2_ps(__Y,1,2)),
	                _mm_det2_ps(_mm_select2_ps(__X,0,2), _mm_select2_ps(__Y,0,2)),
	                _mm_det2_ps(_mm_select2_ps(__X,0,1), _mm_select2_ps(__Y,0,1)),
		        0
		      };
	return dst;
}

extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_laplace3_pd(__v4df __X, __v4df __Y)
{
	__v4df dst  = { _mm_det2_pd(_mm_select2_pd(__X,1,2), _mm_select2_pd(__Y,1,2)),
	                _mm_det2_pd(_mm_select2_pd(__X,0,2), _mm_select2_pd(__Y,0,2)),
	                _mm_det2_pd(_mm_select2_pd(__X,0,1), _mm_select2_pd(__Y,0,1)),
		        0
		      };
	return dst;
}

extern __inline float __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_det3_ps(__v4sf a, __v4sf b, __v4sf c)
{
	__v4sf dst = (__v4sf){1, -1, 1, 0} * a * _mm_laplace3_ps(b, c);
	return dst[0] + dst[1] + dst[2];
}

extern __inline double __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_det3_pd(__v4df a, __v4df b, __v4df c)
{
	__v4df dst = (__v4df){1, -1, 1, 0} * a * _mm_laplace3_pd(b, c);
	return dst[0] + dst[1] + dst[2];
}

extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_cross3_ps(__v4sf a, __v4sf b)
{
	return (__v4sf){1, -1, 1, 0} * _mm_laplace3_ps(a, b);
}

extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_cross3_pd(__v4df a, __v4df b)
{
	return (__v4df){1, -1, 1, 0} * _mm_laplace3_pd(a, b);
}

extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_laplace4_ps(__v4sf __X, __v4sf __Y, __v4sf __Z)
{
	__v4sf dst  = { _mm_det3_ps(_mm_select3_ps(__X,1,2,3), _mm_select3_ps(__Y,1,2,3), _mm_select3_ps(__Z,1,2,3)), 
	                _mm_det3_ps(_mm_select3_ps(__X,0,2,3), _mm_select3_ps(__Y,0,2,3), _mm_select3_ps(__Z,0,2,3)),
	                _mm_det3_ps(_mm_select3_ps(__X,0,1,3), _mm_select3_ps(__Y,0,1,3), _mm_select3_ps(__Z,0,1,3)),
		        _mm_det3_ps(_mm_select3_ps(__X,0,1,2), _mm_select3_ps(__Y,0,1,2), _mm_select3_ps(__Z,0,1,2))
		      };
	return dst;
}

extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_laplace4_pd(__v4df __X, __v4df __Y, __v4df __Z)
{
	__v4df dst  = { _mm_det3_pd(_mm_select3_pd(__X,1,2,3), _mm_select3_pd(__Y,1,2,3), _mm_select3_pd(__Z,1,2,3)), 
	                _mm_det3_pd(_mm_select3_pd(__X,0,2,3), _mm_select3_pd(__Y,0,2,3), _mm_select3_pd(__Z,0,2,3)),
	                _mm_det3_pd(_mm_select3_pd(__X,0,1,3), _mm_select3_pd(__Y,0,1,3), _mm_select3_pd(__Z,0,1,3)),
		        _mm_det3_pd(_mm_select3_pd(__X,0,1,2), _mm_select3_pd(__Y,0,1,2), _mm_select3_pd(__Z,0,1,2))
		      };
	return dst;
}

extern __inline float __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_det4_ps(__v4sf a, __v4sf b, __v4sf c, __v4sf d)
{
	__v4sf dst = (__v4sf){1, -1, 1, -1} * a * _mm_laplace4_ps(b, c, d);
	return dst[0] + dst[1] + dst[2] + dst[3];
}

extern __inline double __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_det4_pd(__v4df a, __v4df b, __v4df c, __v4df d)
{
	__v4df dst = (__v4df){1, -1, 1, -1} * a * _mm_laplace4_pd(b, c, d);
	return dst[0] + dst[1] + dst[2] + dst[3];
}

extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_cross4_ps(__v4sf a, __v4sf b, __v4sf c)
{
	return (__v4sf){-1, 1, -1, 1} * _mm_laplace4_ps(a, b, c);
}

extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_cross4_pd(__v4df a, __v4df b, __v4df c)
{ 
	return (__v4df){-1, 1, -1, 1} * _mm_laplace4_pd(a, b, c);
}
*/
