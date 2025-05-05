#pragma once

#include <mlr/vector.hpp>

namespace math
{

namespace id
{
	/* quake color */
	union color4ub_t
	{
		vec::type<u8,4> rgba;
		uint32_t u32;
	};
};

namespace col
{
	const static u8 R = 0;
	const static u8 G = 1;
	const static u8 B = 2;
	const static u8 A = 3;

	template<scalar T, int... C> 
	struct type : arr<T, sizeof...(C),align::adaptive>
	{
	};

	template<int... C>
	using u8 = type<u8, C...>;

	template<int... C>
	using f32 = type<f32, C...>;
/*
	template<std::array COLS, std::array BITS, size_t CHANNELS = COLS.size()>
	struct bitfield : arr<T,1,align::scalar> requires (COLS.size() == BITS.size())
	{
		const static size_t storage_size = std::accumulate(BITS.begin(), BITS.end(), 0);
		const static std::array<u8,4> SHIFT = { 0, BITS[0], BITS[0] + BITS[1], BITS[0] + BITS[1] + BITS[2]};
		const static std::array<T,4> MASK = { BITS[0] - 1, BITS[1] - 1, BITS[2] - 2, BITS[3] - 1};
		using storage_type = std::make_unsigned_t<__int_with_sizeof_t<storage_size/8>>;
		using channel_type = std::make_unsigned_t<__int_with_sizeof_t<std::bit_ceil((unsigned)*std::max_element(BITS.begin(), BITS.end()))/8>>;
		constexpr CHANNEL_TYPE r() requires(BITS[COLS[R]] > 0) { return CHANNEL_TYPE(front() >> SHIFT[COLS[R]] & MASK[COLS[R]]); }
		constexpr CHANNEL_TYPE g() requires(BITS[COLS[G]] > 0) { return CHANNEL_TYPE(front() >> SHIFT[COLS[G]] & MASK[COLS[G]]); }
		constexpr CHANNEL_TYPE b() requires(BITS[COLS[B]] > 0) { return CHANNEL_TYPE(front() >> SHIFT[COLS[B]] & MASK[COLS[B]]); }
		constexpr CHANNEL_TYPE a() requires(BITS[COLS[A]] > 0) { return CHANNEL_TYPE(front() >> SHIFT[COLS[A]] & MASK[COLS[A]]); } 
	};
*/
};
};
