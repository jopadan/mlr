#pragma once
#include <mlr/scalar.hpp>

/* aligned fixed length static array buffer type         *
 * Usage:                                                *
 *                                                       *
 * using aligned_buffer = buf::f32<3,align::linear>;     *
 * using buffer         = buf::f32<3>;                   *
 * aligned_buffer     a = { 0,1,2 }; a.print();          *
 * buffer             b = { 0,1,2 }; b.print();          *
 *                                                       */

namespace math
{
bool print_alignment = true;

enum class align
{
	none     = 0 << 0,
	scalar   = 1 << 0,
	linear   = 1 << 1,
	matrix   = 1 << 2,
	adaptive = 1 << 3,
};

namespace buf
{
template<typename T, size_t N, enum align A = align::adaptive, size_t N_POW2 = std::bit_ceil<size_t>(N), size_t T_S = std::min<size_t>(alignof(T), sizeof(T))>
struct alignas((((N == N_POW2) && A != align::scalar) || ((A == align::linear) || (A == align::matrix))) ? N_POW2 * T_S : T_S) type : std::array<T,N>
{
	constexpr size_t aligned_size() { return std::max<size_t>(alignof((*this)),(*this).size() * sizeof(T)); }
	static constexpr void print_header(size_t cnt = N, const char* description = "")
	{
		std::string str;
		str.resize(cnt * 10 + 2);
		std::copy(description, description + strlen(description), &str.front() + 1);
		str.front() = '|';
		std::fill(&str[strlen(str.c_str())], &str.back(), (char)' ');
		*(char*)(&str.back() - 1) = (char)'|';
		std::cout << str.c_str();
		if(print_alignment)
			printf(" %3s|%3s|%3s|%3s|%-15s|%s", "typ", "alg", "vec", "alg", "mode", "cnt");
		std::cout << std::endl;
	}
	void print(size_t cnt = N)
	{
		std::cout << "|";
		if(container<T>)
		{
			for(size_t i = 0; i < cnt; i++)
			{
				printf("%9s", "container");
				if(i < std::min<size_t>(cnt - 1, (*this).size()))
					std::cout << " ";
			}
		}
		else
		{
			for(size_t i = 0; i < cnt; i++)
			{
				printf(std::floating_point<T> ? "%+-9.2e" : "%+-9d", ((*this)[i]));
				if(i < std::min<size_t>(cnt - 1, (*this).size()))
					std::cout << " ";
			}
		}
		std::cout << "|";
		if(print_alignment)
			printf(" %3zu|%3zu|%3zu|%3zu|%15s|%zu", sizeof(T), alignof(T), sizeof(*this), alignof(*this), ((uint8_t)A == (uint8_t)align::scalar ? "scalar" : (uint8_t)A == (uint8_t)align::linear ? "linear" : (uint8_t)A == (uint8_t)align::adaptive ? (std::filesystem::path("adaptive") / (N == N_POW2 ? "linear" : "scalar")) : "none").c_str(), (*this).size());
		std::cout << std::endl;
	}
};

/* unsigned integer aligned array buffer types */
template<size_t N, enum align A = align::adaptive>
using u64   = type<math::u64, N, A>;
template<size_t N, enum align A = align::adaptive>
using u32   = type<math::u32, N, A>;
template<size_t N, enum align A = align::adaptive>
using u16   = type<math::u16, N, A>;
template<size_t N, enum align A = align::adaptive>
using u8    = type<math::u8 , N, A>;

/* signed integer aligned array buffer types */
template<size_t n, enum align a = align::adaptive>
using s64   = type<math::s64, n, a>;
template<size_t n, enum align a = align::adaptive>
using s32   = type<math::s32, n, a>;
template<size_t n, enum align a = align::adaptive>
using s16   = type<math::s16, n, a>;
template<size_t n, enum align a = align::adaptive>
using s8    = type<math::s8 , n, a>;

/* integer aligned array buffer types */
template<size_t n, enum align a = align::adaptive>
using i64   = type<math::i64, n, a>;
template<size_t n, enum align a = align::adaptive>
using i32   = type<math::i32, n, a>;
template<size_t n, enum align a = align::adaptive>
using i16   = type<math::i16, n, a>;
template<size_t n, enum align a = align::adaptive>
using i8    = type<math::i8 , n, a>;
template<size_t N, enum align A = align::adaptive>
using usz   = type<math::usz, N, A>;
template<size_t N, enum align A = align::adaptive>
using ssz   = type<math::ssz, N, A>;

/* index aligned array buffer types */
template<size_t N, enum align A = align::adaptive>
using idx   = type<unsigned int, N, A>;

template<size_t N, enum align A = align::adaptive>
using idx8  = type<math::u8 , N, A>;
template<size_t N, enum align A = align::adaptive>
using idx16 = type<math::u16, N, A>;
template<size_t N, enum align A = align::adaptive>
using idx32 = type<math::u32, N, A>;
template<size_t N, enum align A = align::adaptive>
using idx64 = type<math::u64, N, A>;

/* floating-point aligned array buffer types */
template<size_t N, enum align A = align::adaptive>
using f32   = type<math::f32, N, A>;
template<size_t N, enum align A = align::adaptive>
using f64   = type<math::f64, N, A>;

};
};
