#pragma once

#include <bitset>
#include <optional>
#include <cstddef>
#include <cstdint>
#include <array>
#include <iostream>
#include <bit>

#include <mlr/scalar.hpp>
#include <mlr/buffer.hpp>

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
static constexpr const std::array<math::channel,4> bgra = {B,G,R,A};
static constexpr const std::array<math::channel,4> argb = {G,B,A,R};
static constexpr const std::array<math::channel,4> abgr = {A,B,G,R};

template<typename T, std::array COLS>
struct vector : vec::type<T, COLS.size(), align::adaptive>
{
	/* accessors */
	inline constexpr T get(size_t i) const  { return (*this)[COLS[i % COLS.size()]]; }
	inline constexpr vector<T,COLS>& set(size_t i, T val) { (*this)[COLS[i % COLS.size()]] = val; return (*this); }
	inline constexpr T const r() { return get(R); }
	inline constexpr T const g() { return get(G); }
	inline constexpr T const b() { return get(B); }
	inline constexpr T const a() { return get(A); }

	/* rounding */
	inline constexpr vector<T, COLS> roundf() const
	{
		vector<T,COLS> dst;
		for(size_t i = 0; i < dst.size(); i++)
			dst[i] = static_cast<T>(lroundf(static_cast<math::f32>((*this)[i])));
		return dst;
	}

	/* casts */
	template<scalar DST = math::u8, std::array DST_COLS = rgba>
	inline constexpr operator vector<DST,DST_COLS>() const
	{
		vector<DST,DST_COLS> dst;
		if(DST_COLS == COLS)
			for(size_t i = 0; i < dst.size(); i++)
				dst[i] = static_cast<DST>(lroundf(static_cast<math::f32>((*this)[i])));
		else
			for(size_t i = 0; i < dst.size(); i++)
				dst.set(i, static_cast<DST>(std::floating_point<DST> ? static_cast<math::f32>(get(i)) : lroundf(static_cast<math::f32>(get(i)))));
		return dst;
	}
			
};

template<typename T, std::array COLS, std::array BITS>
struct alignas(alignof(T)) bf4
{
	T c0 : BITS[0];
	T c1 : BITS[1];
	T c2 : BITS[2];
	T c3 : BITS[3];

	inline constexpr T get(size_t i) const
	{
		switch(COLS[i % COLS.size()] % COLS.size())
		{
			case R: return c0;
			case G: return c1;
			case B: return c2;
			case A: return c3;
			default: return i;
		}
	}
	inline constexpr bf4<T,COLS,BITS>& set(size_t i, T val)
	{
		switch(COLS[i % COLS.size()] % COLS.size())
		{
			case R: c0 = val & T((1 << BITS[COLS[R]]) - 1); return (*this);
			case G: c1 = val & T((1 << BITS[COLS[G]]) - 1); return (*this);
			case B: c2 = val & T((1 << BITS[COLS[B]]) - 1); return (*this);
			case A: c3 = val & T((1 << BITS[COLS[A]]) - 1); return (*this);
			default: return (*this);
		}
	}
	inline constexpr T r() const { return get(R); }
	inline constexpr T g() const { return get(G); }
	inline constexpr T b() const { return get(B); }
	inline constexpr T a() const { return get(A); }

	template<std::array DST_COLS>
	inline constexpr operator vector<math::f32,DST_COLS>() const
	{
		vector<math::f32, DST_COLS> dst;
		dst.set(R, (math::f32)r() / ((1 << BITS[COLS[R]]) - 1));
		dst.set(G, (math::f32)g() / ((1 << BITS[COLS[G]]) - 1));
		dst.set(B, (math::f32)b() / ((1 << BITS[COLS[B]]) - 1));
		dst.set(A, (math::f32)a() / ((1 << BITS[COLS[A]]) - 1));
		return dst;
	}

	template<std::array DST_COLS>
	inline constexpr operator vector<math::u8,DST_COLS>() const
	{
		vector<math::f32, DST_COLS> tmp{(vector<math::f32,DST_COLS>)(*this) * UINT8_MAX};
		return (vector<math::u8,DST_COLS>)tmp;
	}

	/* TODO: Add alpha channel cast */
};

template<typename T, std::array COLS, std::array BITS>
struct alignas(alignof(T)) bf3
{
	T c0 : BITS[0];
	T c1 : BITS[1];
	T c2 : BITS[2];
	inline constexpr T get(size_t i) const
	{
		switch(COLS[i % COLS.size()] % COLS.size())
		{
			case R: return c0;
			case G: return c1;
			case B: return c2;
			default: return i;
		}
	}
	inline constexpr bf3<T,COLS,BITS>& set(size_t i, T val)
	{
		switch(COLS[i % COLS.size()] % COLS.size())
		{
			case R: c0 = val & T((1 << BITS[COLS[R]]) - 1); return (*this);
			case G: c1 = val & T((1 << BITS[COLS[G]]) - 1); return (*this);
			case B: c2 = val & T((1 << BITS[COLS[B]]) - 1); return (*this);
			default: return *(this);
		}
	}
	inline constexpr T r() const { return get(R); }
	inline constexpr T g() const { return get(G); }
	inline constexpr T b() const { return get(B); }

	template<std::array DST_COLS>
	inline constexpr operator vector<math::f32,DST_COLS>() const
	{
		vector<math::f32, DST_COLS> dst;
		dst.set(R, (math::f32)r() / ((1 << BITS[COLS[R]]) - 1));
		dst.set(G, (math::f32)g() / ((1 << BITS[COLS[G]]) - 1));
		dst.set(B, (math::f32)b() / ((1 << BITS[COLS[B]]) - 1));
		return dst;
	}

	template<std::array DST_COLS>
	inline constexpr operator vector<math::u8,DST_COLS>() const
	{
		vector<math::f32, DST_COLS> tmp{(vector<math::f32,DST_COLS>)(*this) * UINT8_MAX};
		return (vector<math::u8,DST_COLS>)tmp;
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
