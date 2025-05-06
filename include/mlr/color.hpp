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

template<typename T, std::array COLS, std::array BITS>
struct alignas(alignof(T)) bf4
{
	T r : BITS[0];
	T g : BITS[1];
	T b : BITS[2];
	T a : BITS[3];
	void print() { std::cout << BITS.size() << std::endl; }
};

template<typename T, std::array COLS, std::array BITS>
struct alignas(alignof(T)) bf3
{
	T r : BITS[0];
	T g : BITS[1];
	T b : BITS[2];
	void print() { std::cout << BITS.size() << std::endl; }
};

template<typename T, std::array COLS, std::array BITS> requires(COLS.size() == BITS.size())
using bitfield = std::conditional_t<(COLS.size() > 3), bf4<T,COLS,BITS>, bf3<T,COLS,BITS>>;

template<typename T, std::array COLS>
struct alignas(std::bit_ceil<size_t>(COLS.size()) == COLS.size() ? COLS.size() * alignof(T) : alignof(T)) array : std::array<T, COLS.size()>
{
};

template<std::array COLS, std::array BITS = std::array<int,COLS.size()>{0}>
using u16 = std::conditional_t<(BITS[0] == 0), array<math::u16,COLS>, bitfield<math::u16, COLS, BITS>>;

template<std::array COLS, std::array BITS = std::array<int,COLS.size()>{0}>
using u8  = std::conditional_t<(BITS[0] == 0), array<math::u8 ,COLS>, bitfield<math::u8 , COLS, BITS>>;

template<std::array COLS, std::array BITS = std::array<int,COLS.size()>{0}>
using f32 = array<math::f32,COLS>;

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
