#include <mlr/scalar.hpp>
#include <mlr/vector.hpp>
#include <mlr/color.hpp>
#include <mlr/matrix.hpp>
#include <mlr/quaternion.hpp>
#include <mlr/octonion.hpp>
#include <mlr/motor.hpp>

using namespace math;

/* quake scalar type */
using qboolean        = eb32;
const qboolean qfalse = MLR_FALSE;
const qboolean qtrue  = MLR_TRUE;
using qint8_t         = i8;
using quint8_t        = u8;
using qint16_t        = i16;
using quint16_t       = u16;
using qint32_t        = i32;
using quint32_t       = u32;
using qint64_t        = i64;
using quint64_t       = u64;
using qintptr_t       = sptr;
using quintptr_t      = uptr;
using qssize_t        = ssz;
using qsize_t         = usz;
using qutime_ns_t     = utime;
using qstime_ns_t     = stime;
using qtime_ns_t      = qutime_ns_t;
using vecf_t          = f32;
using vecd_t          = f64;
using vec_t           = vecf_t;
using ivec_t          = i32;
using qbyte           = quint8_t;
using qindex          = idx;
using qint            = s32;
using qsizei          = sze;
using qbitfield32_t   = bf32;
using qbitfield16_t   = bf16;

/* quake vec_t default scalar types */
namespace math::vec
{
	template<size_t N, enum align A = align::adaptive>
	using vec_t = type<vec_t, N, A>;
};
namespace math::mat
{
	template<size_t ROW = 3, size_t COL = 3, enum align A = align::adaptive>
	using vec_t = type<vec_t, ROW, COL, A>;
};
namespace math::qut
{
	using vec_t = type<vec_t>;
};
namespace math::ver
{
	using vec_t = type<vec_t>;
};
namespace math::oct
{
	using vec_t = type<vec_t>;
};
namespace math::mot
{
	using vec_t = type<vec_t>;
};

using vec2_t     = vec::vec_t<2                 >;
using vec3_t     = vec::vec_t<3                 >;
using avec3_t    = vec::vec_t<3, align::linear  >;
using vec4_t     = vec::vec_t<4                 >;
using vec5_t     = vec::vec_t<5                 >;
using avec5_t    = vec::vec_t<5, align::linear  >;

using rgba8888_t = col::u8 <{R,G,B,A}           >;
using rgb888_t   = col::u8 <{R,G,B  }           >;
using rgbaf32_t  = col::f32<{R,G,B,A}           >;
using rgbf32_t   = col::f32<{R,G,B  }           >;

using rgba4444_t = col::u16<{R,G,B,A},{4,4,4,4} >;
using rgb565_t   = col::u16<{R,G,B}  ,{5,6,6}   >;
using rgb5551_t  = col::u16<{R,G,B}  ,{5,5,5,1} >;

using mat3_t     = mat::vec_t<3,3               >;
using lamat3_t   = mat::vec_t,3,3, align::linear>;
using amat3_t    = mat::vec_t,3,3, align::matrix>;
using mat4_t     = mat::vec_t,4,4               >;
using lamat3_t   = mat::vec_t,4,4, align::linear>;
using amat4_t    = mat::vec_t,4,4, align::matrix>;

using mat34_t    = mat::vec_t<3,4               >;
using lamat34_t  = mat::vec_t,3,4, align::linear>;
using amat34_t   = mat::vec_t,3,4, align::matrix>;

using mat43_t    = mat::vec_t<4,3               >;
using lamat43_t  = mat::vec_t,4,3, align::linear>;
using amat43_t   = mat::vec_t,4,3, align::matrix>;

using versor     = ver::vec_t;
using quat_t     = qut::vec_t;
using oct_t      = oct::vec_t;
using mot_t      = mot::vec_t;
