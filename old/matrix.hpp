#pragma once

#include <mlr/vector.hpp>

namespace math::mat
{
	template<scalar T, size_t COLS, size_t ROWS = 1, enum align AV = align::adaptive, enum align AM = align::matrix>
	struct type : arr<vec::type<T,ROWS,A>,COLS, A>
	{
	};
	template<typ::sca T, size_t COLS, size_t ROWS = 1>
		using type = std::conditional_t<COLS == 1, vec::type<T,ROWS>, vec::type<T,ROWS>[COLS]>;

	template<size_t COLS, size_t ROWS>
		using f32   = type<typ::f32  , ROWS, COLS>;
	template<size_t COLS, size_t ROWS>
		using f64   = type<typ::f64  , ROWS, COLS>;
	template<size_t COLS, size_t ROWS>
		using i8    = type<typ::  i8 , ROWS, COLS>;
	template<size_t COLS, size_t ROWS>
		using i16   = type<typ::i16  , ROWS, COLS>;
	template<size_t COLS, size_t ROWS>
		using i32   = type<typ::i32  , ROWS, COLS>;
	template<size_t COLS, size_t ROWS>
		using i64   = type<typ::i64  , ROWS, COLS>;
	template<size_t COLS, size_t ROWS>
		using u8    = type<typ:: u8  , ROWS, COLS>;
	template<size_t COLS, size_t ROWS>
		using u16   = type<typ::u16  , ROWS, COLS>;
	template<size_t COLS, size_t ROWS>
		using u32   = type<typ::u32  , ROWS, COLS>;
	template<size_t COLS, size_t ROWS>
		using u64   = type<typ::u64  , ROWS, COLS>;
	template<size_t COLS, size_t ROWS>
		using idx8  = type<typ::idx8 , ROWS, COLS>;
	template<size_t COLS, size_t ROWS>
		using idx16 = type<typ::idx16, ROWS, COLS>;
	template<size_t COLS, size_t ROWS>
		using idx   = type<typ::idx  , ROWS, COLS>;
};
