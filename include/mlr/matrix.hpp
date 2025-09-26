#include <mlr/vector.hpp>

namespace math
{
namespace mat
{
template<typename T, size_t ROW, size_t COL,
enum align A = align::adaptive,
size_t ROW_POW2 = VM_BIT_CEIL(ROW),
size_t COL_POW2 = VM_BIT_CEIL(COL),
size_t V_A = alignof(vec::type<T,COL,A>)>
struct alignas((((ROW * COL == ROW_POW2 * COL_POW2) && A != align::scalar) || (A == align::matrix)) ? ROW_POW2 * V_A : V_A) type : std::array<vec::type<T,COL,A>, ROW>
{
	static inline type<T,ROW,COL,A> id()
	{
		type<T,ROW,COL,A> dst;
		for(size_t i = 0; i < ROW; i++)
			dst[i] = vec<T,COL,A>::id(i);
		return dst;
	}
	static inline type<T,ROW,COL,A> ne()
	{
		return type<T,ROW,COL,A>{};
	}

	constexpr inline void set_col(size_t i, const vec::type<T,ROW,A> v)
	{
		for(size_t row = 0; row < ROW; row++)
			(*this)[row][i % COL] = v[row];
	}
	constexpr inline vec::type<T,ROW,A> col(size_t i) const
	{
		vec::type<T,ROW,A> dst;
		for(size_t row = 0; row < ROW; row++)
			dst[row] = (*this)[row][i % COL];
		return dst;
	}
	constexpr inline type<T,COL,ROW,A> transposed() const
	{
		type<T,COL,ROW,A> dst;
		for(size_t row = 0; row < COL; row++)
			dst[row] = col(row);
		return dst;
	}
	constexpr inline type<T,COL,ROW,A>& transpose()
	{
		return ((*this) = transposed());
	}
	constexpr inline type<T,ROW-1,COL-1,A> minor(size_t i, size_t p = 0) const
	{
		static_assert(ROW == COL);

		type<T,ROW-1,COL-1,A> dst{};

		for(size_t j = 0; j < ROW; j++)
		{
			if(j == i) continue;
			dst[p++] = (*this)[j].splice(j);
		}
		return dst;
	}
	constexpr inline T det() const
	{
		return (vec::type<T,COL,A>::id_alt_sign() * (*this)[0] * laplace()).sum();
	}

	constexpr inline vec::type<T,COL,A> laplace() const
	{
		vec::type<T,COL,A> dst;
		for(size_t i = 0; i < COL; i++)
			dst[i] = (*this)[i]->minor(i).det();
		return dst;
	}
};
};
};
