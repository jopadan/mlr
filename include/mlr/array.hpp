#pragma once
#include <mlr/scalar.hpp>

namespace math
{
bool print_alignment = true;

enum class align : uint8_t
{
	none     = 0 << 0,
	scalar   = 1 << 0,
	vector   = 1 << 1,
	matrix   = 1 << 2,
	adaptive = 1 << 3,
};

template<scalar T, size_t N, enum align A = (std::bit_ceil<size_t>(N) != N ? (uint8_t)align::scalar : (uint8_t)align::vector) | (uint8_t)align::adaptive, size_t N_POW2 = std::bit_ceil<size_t>(N)>
struct alignas((((N == N_POW2) && !((uint8_t)A & (uint8_t)align::scalar)) || (uint8_t)A & (uint8_t)align::vector) ? N_POW2 * std::max<size_t>(alignof(T),sizeof(T)) : std::max<size_t>(alignof(T),sizeof(T))) arr : std::array<T,N>
{
	size_t aligned_size() { return std::max<size_t>(alignof((*this)),(*this).size() * sizeof(T)); }
	void print_header(size_t cnt = N, const char* description = nullptr)
	{
		printf("|%-39s|", description);
		if(print_alignment)
			printf(" %3s|%3s|%3s|%3s|%-15s|%s", "typ", "alg", "vec", "alg", "mode", "cnt");
		std::cout << std::endl;
	}
	void print(size_t cnt = N)
	{
		printf("|%+.2e %+.2e %+.2e %+.2e|", (*this)[0], (*this)[1], (*this)[2], (*this)[3]);
		if(print_alignment)
			printf(" %3zu|%3zu|%3zu|%3zu|%15s|%zu", sizeof(T), alignof(T), sizeof(*this), alignof(*this), ((uint8_t)A == (uint8_t)align::scalar ? "scalar" : (uint8_t)A == (uint8_t)align::vector ? "vector" : (uint8_t)A == (uint8_t)align::adaptive ? (std::filesystem::path("adaptive") / (N == N_POW2 ? "vector" : "scalar")) : "none").c_str(), (*this).size());
		std::cout << std::endl;
	}
};
};
