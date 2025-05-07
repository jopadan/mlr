#pragma once

#include <bitset>
#include <optional>
#include <cstddef>
#include <cstdint>
#include <array>
#include <iostream>
#include <bit>

#include <mlr/scalar.hpp>
#include <mlr/array.hpp>

/* 
 * color type interface abstraction intended example usage style
 *
 * col::u16<{R,G,B            }> RGB161616    = {1,2,3  }; // array    type
 * col::u16<{R,G,B,A          }> RGBA16161616 = {1,2,3,4}; // array    type
 * col::u16<{R,G,B  },{5,6,5  }> RGB565       = {1,2,3  }; // bitfield type
 * col::u16<{R,G,B,A},{4,4,4,4}> RGBA4444     = {1,2,3,4}; // bitfield type
 *
 * col::u8 <{R,G,B            }> RGB888       = {1,2,3  }; // array    type
 * col::u8 <{R,G,B,A          }> RGBA8888     = {1,2,3,4}; // array    type
 * col::u8 <{R,G,B  },{2,4,2  }> RGB242       = {1,2,3  }; // bitfield type
 * col::u8 <{R,G,B,A},{2,2,2,2}> RGBA2222     = {1,2,3,4}; // bitfield type
 *
 */
namespace math
{
namespace col
{

static constexpr const std::array<math::channel,3> rgb  = {R,G,B  };
static constexpr const std::array<math::channel,4> rgba = {R,G,B,A};

template<typename T, std::array COLS>
struct vector : vec::type<T, COLS.size(), align::adaptive>
{
	/* accessors */
	inline constexpr T get(size_t i) const { return (*this)[COLS[i % COLS.size()]]; }
	inline constexpr T const r() { return get(R); }
	inline constexpr T const g() { return get(G); }
	inline constexpr T const b() { return get(B); }
	inline constexpr T const a() { return get(A); }

	/* rounding */
	template<scalar DST = T, std::array DST_COLS = rgba>
	inline constexpr vector<DST, DST_COLS> roundf() const
	{
		vector<DST,DST_COLS> dst;
		for(size_t i = 0; i < dst.size(); i++)
			dst[i] = static_cast<DST>(lroundf(static_cast<math::f32>(get(i))));
		return dst;
	}

	/* casts */
	inline constexpr operator vector<math::u8,rgba>() const { return roundf<math::u8, rgba>(); }
	inline constexpr operator vector<math::u8,rgb >() const { return roundf<math::u8, rgb >(); }
};

template<typename T, std::array COLS, std::array BITS>
struct alignas(alignof(T)) bf4
{
	T c0 : BITS[0];
	T c1 : BITS[1];
	T c2 : BITS[2];
	T c3 : BITS[3];

	inline constexpr T get(size_t i) const { switch(COLS[i % COLS.size()] % COLS.size()) { case 0: return c0; case 1: return c1; case 2: return c2; case 3: return c3; default: return i; } }
	inline constexpr T r() const { return get(R); }
	inline constexpr T g() const { return get(G); }
	inline constexpr T b() const { return get(B); }
	inline constexpr T a() const { return get(A); }

	inline constexpr operator vector<math::f32,{R,G,B,A}>() const
	{
		return (vector<math::f32,{R,G,B,A}>)
		{
			(math::f32)r() / ((1 << BITS[COLS[R]]) - 1),
			(math::f32)g() / ((1 << BITS[COLS[G]]) - 1),
			(math::f32)b() / ((1 << BITS[COLS[B]]) - 1),
			(math::f32)a() / ((1 << BITS[COLS[A]]) - 1)
		};
	}

	inline constexpr operator vector<math::u8,{R,G,B,A}>() const
	{
		return (vector<math::u8,{R,G,B,A}>)vector<math::f32,{R,G,B,A}>{((vector<math::f32,{R,G,B,A}>)(*this)) * UINT8_MAX};
	}

	/* TODO: Add alpha channel cast */
};

template<typename T, std::array COLS, std::array BITS>
struct alignas(alignof(T)) bf3
{
	T c0 : BITS[0];
	T c1 : BITS[1];
	T c2 : BITS[2];
	inline constexpr T get(size_t i) const { switch(COLS[i % COLS.size()] % COLS.size()) { case 0: return c0; case 1: return c1; case 2: return c2; default: return i; } }
	inline constexpr T r() const { return get(R); }
	inline constexpr T g() const { return get(G); }
	inline constexpr T b() const { return get(B); }
	inline constexpr operator vector<f32,{R,G,B}>() const
	{
		return (vector<f32,{R,G,B}>)
		{
			(math::f32)r() / ((1 << BITS[R]) - 1),
			(math::f32)g() / ((1 << BITS[G]) - 1),
			(math::f32)b() / ((1 << BITS[B]) - 1)
		};
	}

	inline constexpr operator vector<math::u8,{R,G,B}>() const
	{
		return (vector<math::u8,{R,G,B}>)vector<math::f32,{R,G,B}>{((vector<math::f32,{R,G,B}>)(*this)) * UINT8_MAX};
	}

	/* TODO: Add alpha channel cast */
};

template<typename T, std::array COLS, std::array BITS> requires(COLS.size() == BITS.size())
using bitfield = std::conditional_t<(COLS.size() > 3), bf4<T,COLS,BITS>, bf3<T,COLS,BITS>>;

template<std::array COLS, std::array BITS = std::array<int,COLS.size()>{0}>
using u16 = std::conditional_t<(BITS[0] == 0), vector<math::u16,COLS>, bitfield<math::u16, COLS, BITS>>;

template<std::array COLS, std::array BITS = std::array<int,COLS.size()>{0}>
using u8  = std::conditional_t<(BITS[0] == 0), vector<math::u8 ,COLS>, bitfield<math::u8 , COLS, BITS>>;

template<std::array COLS, std::array BITS = std::array<int,COLS.size()>{0}>
using f32 = vector<math::f32,COLS>;

namespace id
{
	/* quake color */
	union color4ub_t
	{
		vec::type<math::u8,4> rgba;
		math::u32 u32;
	};
};

};
};
