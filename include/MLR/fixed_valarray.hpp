#pragma once
#include <MLR/scalar.hpp>
#include <MLR/align.hpp>

namespace math
{
template<scalar T, size_t N, enum align A = align::adaptive, size_t N_POW2 = std::bit_ceil<size_t>(N)>
struct alignas(((N == N_POW2 && A != align::element) || A == align::vector) ? N_POW2 * sizeof(T) : sizeof(T)) fixed_valarray : std::array<T,N>
{
	/* alignment conversion operators */
	template<size_t N_LHS, enum align A_RHS = align::adaptive>
	inline constexpr operator fixed_valarray<T,N_LHS,A_RHS>() { return *reinterpret_cast<fixed_valarray<T,N_LHS,A_RHS>*>(this); }
	template<size_t N_LHS, enum align A_RHS = align::adaptive>
	inline constexpr operator const fixed_valarray<T,N_LHS,A_RHS>() const { return *reinterpret_cast<const fixed_valarray<T,N_LHS,A_RHS>*>(this); }

	/* mixed alignment arithmetic operators */
	template<size_t N_RHS, enum align A_RHS = align::adaptive>
	inline constexpr fixed_valarray<T,N,A>& operator+=(const fixed_valarray<T,N_RHS,A_RHS> rhs)
	{
		std::transform((*this).cbegin(), (*this).cbegin() + std::min((*this).size(), rhs.size()), rhs.cbegin(), (*this).begin(), std::plus<>{});
		return (*this);
	}
	template<size_t N_RHS, enum align A_RHS = align::adaptive>
	inline constexpr fixed_valarray<T,N,A>& operator-=(const fixed_valarray<T,N_RHS,A_RHS> rhs)
	{
		std::transform((*this).cbegin(), (*this).cbegin() + std::min((*this).size(), rhs.size()), rhs.cbegin(), (*this).begin(), std::minus<>{});
		return (*this);
	}
	template<size_t N_RHS, enum align A_RHS = align::adaptive>
	inline constexpr fixed_valarray<T,N,A>& operator*=(const fixed_valarray<T,N_RHS,A_RHS> rhs)
	{
		std::transform((*this).cbegin(), (*this).cbegin() + std::min((*this).size(), rhs.size()), rhs.cbegin(), (*this).begin(), std::multiplies<>{});
		return (*this);
	}
	template<size_t N_RHS, enum align A_RHS = align::adaptive>
	inline constexpr fixed_valarray<T,N,A>& operator/=(const fixed_valarray<T,N_RHS,A_RHS> rhs)
	{
		std::transform((*this).cbegin(), (*this).cbegin() + std::min((*this).size(), rhs.size()), rhs.cbegin(), (*this).begin(), std::divides<>{});
		return (*this);
	}
	inline constexpr fixed_valarray<T,N,A>& operator+=(const T rhs)
	{
		fixed_valarray<T,N,A> dst = fixed_valarray<T,N,A>::fill(rhs);
		std::transform((*this).cbegin(), (*this).cend(), rhs.cbegin(), (*this).begin(), std::plus<>{});
		return (*this);
	}
	inline constexpr fixed_valarray<T,N,A>& operator-=(const T rhs)
	{
		fixed_valarray<T,N,A> dst = fixed_valarray<T,N,A>::fill(rhs);
		std::transform((*this).cbegin(), (*this).cend(), rhs.cbegin(), (*this).begin(), std::minus<>{});
		return (*this);
	}
	inline constexpr fixed_valarray<T,N,A>& operator*=(const T rhs)
	{
		fixed_valarray<T,N,A> dst = fixed_valarray<T,N,A>::fill(rhs);
		std::transform((*this).cbegin(), (*this).cend(), rhs.cbegin(), (*this).begin(), std::multiplies<>{});
		return (*this);
	}
	inline constexpr fixed_valarray<T,N,A>& operator/=(const T rhs)
	{
		fixed_valarray<T,N,A> dst = fixed_valarray<T,N,A>::fill(rhs);
		std::transform((*this).cbegin(), (*this).cend(), rhs.cbegin(), (*this).begin(), std::divides<>{});
		return (*this);
	}
	template<scalar T_RHS, size_t N_RHS, enum align A_RHS = align::adaptive, scalar T_DST=decltype((T)1*(T_RHS)1)>
	friend inline constexpr fixed_valarray<T_DST,N,A> operator+(const fixed_valarray<T,N,A> lhs, const fixed_valarray<T_RHS,N_RHS,A_RHS> rhs)
	{
		fixed_valarray<T_DST,N,A> dst = {};
		std::transform(lhs.cbegin(), lhs.cbegin() + std::min(lhs.size(), rhs.size()), rhs.cbegin(), dst.begin(), std::plus<>{});
		return dst;
	}
	template<scalar T_RHS, size_t N_RHS, enum align A_RHS = align::adaptive, scalar T_DST=decltype((T)1*(T_RHS)1)>
	friend inline constexpr fixed_valarray<T_DST,N,A> operator-(const fixed_valarray<T,N,A> lhs, const fixed_valarray<T_RHS,N_RHS,A_RHS> rhs)
	{
		fixed_valarray<T_DST,N,A> dst = {};
		std::transform(lhs.cbegin(), lhs.cbegin() + std::min(lhs.size(), rhs.size()), rhs.cbegin(), dst.begin(), std::minus<>{});
		return dst;
	}
	template<scalar T_RHS, size_t N_RHS, enum align A_RHS = align::adaptive, scalar T_DST=decltype((T)1*(T_RHS)1)>
	friend inline constexpr fixed_valarray<T_DST,N,A> operator*(const fixed_valarray<T,N,A> lhs, const fixed_valarray<T_RHS,N_RHS,A_RHS> rhs)
	{
		fixed_valarray<T_DST,N,A> dst = {};
		std::transform(lhs.cbegin(), lhs.cbegin() + std::min(lhs.size(), rhs.size()), rhs.cbegin(), dst.begin(), std::multiplies<>{});
		return dst;
	}
	template<scalar T_RHS, size_t N_RHS, enum align A_RHS = align::adaptive, scalar T_DST=decltype((T)1*(T_RHS)1)>
	friend inline constexpr fixed_valarray<T_DST,N,A> operator/(const fixed_valarray<T,N,A> lhs, const fixed_valarray<T_RHS,N_RHS,A_RHS> rhs)
	{
		fixed_valarray<T_DST,N,A> dst = {};
		std::transform(lhs.cbegin(), lhs.cbegin() + std::min(lhs.size(), rhs.size()), rhs.cbegin(), dst.begin(), std::divides<>{});
		return dst;
	}
	friend inline constexpr fixed_valarray<T,N,A> operator+(const fixed_valarray<T,N,A> lhs, const T rhs)
	{
		fixed_valarray<T,N,A> dst = fill(rhs);
		std::transform(lhs.cbegin(), lhs.cend(), dst.cbegin(), dst.begin(), std::plus<>{});
		return dst;
	}
	friend inline constexpr fixed_valarray<T,N,A> operator-(const fixed_valarray<T,N,A> lhs, const T rhs)
	{
		fixed_valarray<T,N,A> dst = fill(rhs);
		std::transform(lhs.cbegin(), lhs.cend(), dst.cbegin(), dst.begin(), std::minus<>{});
		return dst;
	}
	friend inline constexpr fixed_valarray<T,N,A> operator*(const fixed_valarray<T,N,A> lhs, const T rhs)
	{
		fixed_valarray<T,N,A> dst = fill(rhs);
		std::transform(lhs.cbegin(), lhs.cend(), dst.cbegin(), dst.begin(), std::multiplies<>{});
		return dst;
	}
	friend inline constexpr fixed_valarray<T,N,A> operator/(const fixed_valarray<T,N,A> lhs, const T rhs)
	{
		fixed_valarray<T,N,A> dst = fill(rhs);
		std::transform(lhs.cbegin(), lhs.cend(), dst.cbegin(), dst.begin(), std::divides<>{});
		return dst;
	}

	/* aligned component swizzle */
	template<typename... I>
	inline fixed_valarray<T, sizeof...(I)> permute(const I... args) { return (fixed_valarray<T,sizeof...(I)>){ this[args % N]... }; }
	inline constexpr fixed_valarray<T,N> rotl(size_t i = 1)
	{
		fixed_valarray<T,N> dst;
		std::rotate_copy((*this).begin(), (*this).begin() + i, (*this).end(), dst.begin());
		return dst;
	}
	inline constexpr fixed_valarray<T,N> rotr(size_t i = 1)
	{
		fixed_valarray<T,N> dst;
		std::rotate_copy((*this).rbegin(), (*this).rbegin() + i, (*this).rend(), dst.begin());
		return dst;
	}

	inline constexpr fixed_valarray<T,3>& xyz() { return *reinterpret_cast<fixed_valarray<T,3>*>(this); }
	inline constexpr fixed_valarray<T,3> xyz() const { return *reinterpret_cast<const fixed_valarray<T,3>*>(this); }
	inline constexpr fixed_valarray<T,3> xzy() const { return { (*this)[0], (*this)[2], (*this)[1] }; }
	inline constexpr fixed_valarray<T,3> yzx() const { return { (*this)[1], (*this)[2], (*this)[0] }; }
	inline constexpr fixed_valarray<T,3> yxz() const { return { (*this)[1], (*this)[0], (*this)[2] }; }
	inline constexpr fixed_valarray<T,3> zyx() const { return { (*this)[2], (*this)[1], (*this)[0] }; }
	inline constexpr fixed_valarray<T,3> zxy() const { return { (*this)[2], (*this)[0], (*this)[1] }; }
	inline constexpr fixed_valarray<T,3> yzw() const { return { (*this)[1], (*this)[2], (*this)[3] }; }
	inline constexpr fixed_valarray<T,3> xyw() const { return { (*this)[0], (*this)[1], (*this)[3] }; }
	inline constexpr fixed_valarray<T,3> xzw() const { return { (*this)[0], (*this)[2], (*this)[3] }; }

	inline constexpr fixed_valarray<T,2>& xy() { return *reinterpret_cast<fixed_valarray<T,2>*>(this); }
	inline constexpr fixed_valarray<T,2> xy() const { return *reinterpret_cast<const fixed_valarray<T,2>*>(this); }
	inline constexpr fixed_valarray<T,2> yx() const { return { (*this)[1], (*this)[0] }; }
	inline constexpr fixed_valarray<T,2> xz() const { return { (*this)[0], (*this)[2] }; }
	inline constexpr fixed_valarray<T,2> zx() const { return { (*this)[2], (*this)[0] }; }
	inline constexpr fixed_valarray<T,2> yz() const { return { (*this)[1], (*this)[2] }; }
	inline constexpr fixed_valarray<T,2> zy() const { return { (*this)[2], (*this)[1] }; }

	inline constexpr T& x() { return this[0]; }
	inline constexpr T& y() { return this[1]; }
	inline constexpr T& z() { return this[2]; }

	/* constants */
	static inline constexpr  fixed_valarray<T,N> identity(ssize_t i = -1) { fixed_valarray<T,N> dst = { 0 }; if(i < 0) dst.fill((T)1); else dst[i % N] = (T)1; return dst; }
	static inline constexpr  fixed_valarray<T,N> neutral() { return (fixed_valarray<T,N>){ 0 }; }
	inline constexpr fixed_valarray<T,N> one(ssize_t i = -1) { if(i < 0) (*this).fill((T)1); else (*this)[i % N] = (T)1; return (*this);  } 
	inline constexpr fixed_valarray<T,N> zero(ssize_t i = -1) { if(i < 0) (*this).fill((T)0); else (*this)[i % N] = (T)0; return (*this);  }

	/* load/store */
	static inline fixed_valarray<T,N> load3(T src[3], T w) { return (fixed_valarray<T,N>){ src[0], src[1], src[2], w }; }
	static inline fixed_valarray<T,3> store3(fixed_valarray<T, N> src, T w = 1) requires (N > 2)
	{
		w *= src[3];
		if(w != 0 && w != 1)
			src /= w;
		return (fixed_valarray<T,3>){ src[0], src[1], src[2] };
	}

	inline constexpr fixed_valarray<T,2> neg2(uint8_t mod, uint8_t val = 0)
	{
		return (fixed_valarray<T,2>) { (0 % mod == val) ? - (*this)[0] : (*this)[0],
		                               (1 % mod == val) ? - (*this)[1] : (*this)[1] };
	}

	inline constexpr fixed_valarray<T,2> swap2() const
	{
		return (fixed_valarray<T,2>){ (*this)[1], (*this)[0] };
	}
	/* determinants */
	static inline constexpr T det2(const fixed_valarray<T,2> a, const fixed_valarray<T,2> b)
	{
		fixed_valarray<T,2> dst = (fixed_valarray<T,2>){ 1, -1 } * a * b.swap2();
		return dst[0] + dst[1];
	}
	static inline constexpr T det3(const fixed_valarray<T,3> a, const fixed_valarray<T,3> b, const fixed_valarray<T,3> c)
	{
		const fixed_valarray<T,3> dst = (const fixed_valarray<T,3>){ 1, -1, 1 } * a * laplace3(b,c);
		return dst[0] + dst[1] + dst[2];
	}
	static inline constexpr T det4(const fixed_valarray<T,4> a, const fixed_valarray<T,4> b, const fixed_valarray<T,4> c, const fixed_valarray<T,4> d)
	{
		fixed_valarray<T,3> dst = (fixed_valarray<T,3>){ 1, -1, 1, -1 } * a * laplace4(b,c,d);
		return dst[0] + dst[1] + dst[2] + dst[3];
	}
	/* laplace */
	static inline constexpr fixed_valarray<T,3> laplace3(const fixed_valarray<T,3> a, const fixed_valarray<T,4> b)
	{
		return (fixed_valarray<T,3>){ det2(a.yz(), b.yz()),
		                              det2(a.xz(), b.xz()),
		                              det2(a.xy(), b.xy()) };
	}
	static inline constexpr fixed_valarray<T,4> laplace4(const fixed_valarray<T,4> a, const fixed_valarray<T,4> b, const fixed_valarray<T,4> c)
	{
		return (fixed_valarray<T,4>){ det3(a.yzw(), b.yzw(), c.yzw()),
		                              det3(a.xzw(), b.xzw(), c.xzw()),
		                              det3(a.xyw(), b.xyw(), c.xyw()),
			                      det3(a.xyz(), b.xyz(), c.xyz()) };
	}
	/* scalar products dot */
	template<scalar T_A, scalar T_B, size_t N_A, size_t N_B, scalar T_DST = decltype((T_A)1 * (T_B)1)>
	static inline constexpr T_DST dot2(const fixed_valarray<T_A,N_A> a, const fixed_valarray<T_B,N_B> b)
	{
		fixed_valarray<T_DST,std::max(N_A,N_B)> dst = a*b;
		return std::accumulate(dst.cbegin(), dst.cend(), 0);
	}
	template<scalar T_A, scalar T_B, scalar T_C, size_t N_A, size_t N_B, size_t N_C, scalar T_DST = decltype((T_A)1 * (T_B)1 * (T_C)1)>
	static inline constexpr T_DST dot3(const fixed_valarray<T_A,N_A> a, const fixed_valarray<T_B,N_B> b, const fixed_valarray<T_C,N_C> c)
	{
		fixed_valarray<T_DST,std::max(std::max(N_A,N_B),N_C)> dst = a*b*c;
		return std::accumulate(dst.cbegin(), dst.cend(), 0);
	}
	template<scalar T_A, scalar T_B, scalar T_C, scalar T_D, size_t N_A, size_t N_B, size_t N_C, size_t N_D, scalar T_DST = decltype((T_A)1 * (T_B)1 * (T_C)1 * (T_D)1)>
	static inline constexpr T_DST dot4(const fixed_valarray<T_A,N_A> a, const fixed_valarray<T_B,N_B> b, const fixed_valarray<T_C,N_C> c, const fixed_valarray<T_D,N_D> d)
	{
		fixed_valarray<T_DST,std::max(std::max(N_A,N_B),std::max(N_C,N_D))> dst = a*b*c*d;
		return std::accumulate(dst.cbegin(), dst.cend(), 0);
	}
	/* vector products hodge/cross/laplace */
	static inline constexpr fixed_valarray<T,2,align::vector> cross2(const fixed_valarray<T,2> src, unsigned int winding = GL_CCW)
	{
		return identity().neg2(2,1 - (winding % 2)) * src.swap2();
	}
	static inline constexpr fixed_valarray<T,3,align::vector> cross3(const fixed_valarray<T,3,align::vector> a, const fixed_valarray<T,3,align::vector> b)
	{
		return (b.yzx() * a.xyz() - a.yzx() * b.xyz()).yzx();
	}
	static inline constexpr fixed_valarray<T,4> cross4(const fixed_valarray<T,4> a, const fixed_valarray<T,4> b, const fixed_valarray<T,4> c)
	{
		return fixed_valarray<T,4>{-1,1,-1,1} * laplace4(a,b,c);
	}
	/* rounding */
	template<iscalar DST = T>
	inline constexpr fixed_valarray<DST,N> roundf()
	{
		fixed_valarray<DST,N> dst;
		for(size_t i = 0; i < N; i++)
			dst[i] = static_cast<DST>(lroundf(static_cast<float>((*this)[i])));
		return dst;
	}

};
};
