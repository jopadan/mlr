#pragma once

#include <MLR/fixed_valarray.hpp>

namespace math
{
namespace vec
{
	template<size_t N, enum align A = align::adaptive>
	using f32 = fixed_valarray<f32,N,A>;
	template<size_t N, enum align A = align::adaptive>
	using f64 = fixed_valarray<f64,N,A>;

	template<size_t N, enum align A = align::adaptive>
	using i8  = fixed_valarray<i8,N,A>;
	template<size_t N, enum align A = align::adaptive>
	using i16 = fixed_valarray<i16,N,A>;
	template<size_t N, enum align A = align::adaptive>
	using i32 = fixed_valarray<i32,N,A>;
	template<size_t N, enum align A = align::adaptive>
	using i64 = fixed_valarray<i64,N,A>;

	template<size_t N, enum align A = align::adaptive>
	using s8  = fixed_valarray<s8,N,A>;
	template<size_t N, enum align A = align::adaptive>
	using s16 = fixed_valarray<s16,N,A>;
	template<size_t N, enum align A = align::adaptive>
	using s32 = fixed_valarray<s32,N,A>;
	template<size_t N, enum align A = align::adaptive>
	using s64 = fixed_valarray<s64,N,A>;

	template<size_t N, enum align A = align::adaptive>
	using u8  = fixed_valarray<u8,N,A>;
	template<size_t N, enum align A = align::adaptive>
	using u16 = fixed_valarray<u16,N,A>;
	template<size_t N, enum align A = align::adaptive>
	using u32 = fixed_valarray<u32,N,A>;
	template<size_t N, enum align A = align::adaptive>
	using u64 = fixed_valarray<u64,N,A>;
};
};
