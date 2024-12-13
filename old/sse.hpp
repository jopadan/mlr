
/* Transpose the 4x4 matrix composed of row[0-3].  */
#if defined (__SSE__)

#define _MM_TRANSPOSE4_PI(row0, row1, row2, row3)			\
do {									\
  __v4si __r0 = (row0), __r1 = (row1), __r2 = (row2), __r3 = (row3);	\
  __v4si __t0 = __builtin_ia32_unpcklpi (__r0, __r1);			\
  __v4si __t1 = __builtin_ia32_unpcklpi (__r2, __r3);			\
  __v4si __t2 = __builtin_ia32_unpckhpi (__r0, __r1);			\
  __v4si __t3 = __builtin_ia32_unpckhpi (__r2, __r3);			\
  (row0) = __builtin_ia32_movlhpi (__t0, __t1);				\
  (row1) = __builtin_ia32_movhlpi (__t1, __t0);				\
  (row2) = __builtin_ia32_movlhpi (__t2, __t3);				\
  (row3) = __builtin_ia32_movhlpi (__t3, __t2);				\
} while (0)

#endif

#if defined (__AVX__)

#define _MM_TRANSPOSE4_PD(row0, row1, row2, row3)			\
do {									\
  __v4df __r0 = (row0), __r1 = (row1), __r2 = (row2), __r3 = (row3);	\
  __v4df __t0 = __builtin_ia32_unpcklpd256 (__r0, __r1);		\
  __v4df __t1 = __builtin_ia32_unpcklpd256 (__r2, __r3);		\
  __v4df __t2 = __builtin_ia32_unpckhpd256 (__r0, __r1);		\
  __v4df __t3 = __builtin_ia32_unpckhpd256 (__r2, __r3);		\
  (row0) = __builtin_ia32_vperm2f128_pd256 (__t0, __t1, 0x20);		\
  (row1) = __builtin_ia32_vperm2f128_pd256 (__t2, __t3, 0x20);		\
  (row2) = __builtin_ia32_vperm2f128_pd256 (__t0, __t1, 0x31);		\
  (row3) = __builtin_ia32_vperm2f128_pd256 (__t2, __t3, 0x31);		\
} while (0)

#endif

#ifndef __AVX__
extern __inline __m256d __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm256_set_m128d     (__m128d __H, __m128d __L) { return (__m256d){ __L[0], __L[1], __H[0], __H[1] }; }
extern __inline __m128d __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm256_extractf128_pd(__m256d __X, const int __N)   { return _mm_load_pd(&__X[(__N * 2) % 4]); }
extern __inline __m256d __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm256_hadd_pd       (__m256d __X, __m256d __Y) { return (__m256d){ __X[0] + __X[1], __Y[0] + __Y[1], __X[2] + __X[3], __Y[2] + __Y[3] }; }
#endif

/* Component extract permute functions */
extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_select4_ps(__v4sf v, uint8_t i, uint8_t j, uint8_t k, uint8_t l) { return (__v4sf){v[i%4],v[j%4],v[k%4],v[l%4]}; }
extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_select3_ps(__v4sf v, uint8_t i, uint8_t j, uint8_t k) { return (__v4sf){v[i%4],v[j%4],v[k%4], 0}; }
extern __inline __v2sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_select2_ps(__v4sf v, uint8_t i, uint8_t j) { return (__v2sf){v[i%4],v[j%4]}; }
extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_select4_pd(__v4df v, uint8_t i, uint8_t j, uint8_t k, uint8_t l) { return (__v4df){v[i%4],v[j%4],v[k%4],v[l%4]}; }
extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_select3_pd(__v4df v, uint8_t i, uint8_t j, uint8_t k) { return (__v4df){v[i%4],v[j%4],v[k%4], 0}; }
extern __inline __v2df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_select2_pd(__v4df v, uint8_t i, uint8_t j) { return (__v2df){v[i%4],v[j%4]}; }

/* vec3<=>vec4 convert */
extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_4to3_ps(__v4sf v, double w = 0)
{
	if(w != 0 && v[3] != 0)
		return (__v4sf){ v[0] / w * v[3], v[1] / w * v[3], v[2] / w * v[3], w };
	return (__v4sf){ v[0], v[1], v[2], w };
}

extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_4to3_pd(__v4df v, double w = 0)
{
	if(w != 0 && v[3] != 0)
		return (__v4df){ v[0] / w * v[3], v[1] / w * v[3], v[2] / w * v[3], w };
	return (__v4df){ v[0], v[1], v[2], w };
}

/* Dot product instructions with mask-defined summing and zeroing parts
   of result.  */
extern __inline __m256d __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm256_dp_pd(__m256d __X, __m256d __Y, const int __M)
{
	__m256d cond  = { (__M & (1 << 4)) >> 4, (__M & (1 << 5)) >> 5, (__M & (1 << 6)) >> 6, (__M & (1 << 7)) >> 7};
	__m256d broad = { (__M & (1 << 0)) >> 0, (__M & (1 << 1)) >> 1, (__M & (1 << 2)) >> 2, (__M & (1 << 3)) >> 3};
	__m256d tmp = __X * __Y * cond;
	tmp = _mm256_hadd_pd(tmp, tmp);
	__m128d sum = _mm256_extractf128_pd(tmp, 0) + _mm256_extractf128_pd(tmp, 1);
	return _mm256_set_m128d(sum, sum) * broad;
}

extern __inline __v2sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_laplace2_ps(__v2sf __X) { return (__v2sf){ __X[1], __X[0] }; }
extern __inline __v2df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_laplace2_pd(__v2df __X) { return (__v2df){ __X[1], __X[0] }; }

extern __inline float __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_det2_ps(__v2sf a, __v2sf b)
{
	__v2sf dst = (__v2sf){ 1, -1 } * a * _mm_laplace2_ps(b);
	return dst[0] + dst[1];
}
extern __inline double __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_det2_pd(__v2df a, __v2df b)
{
	__v2df dst = (__v2df){ 1, -1 } * a * _mm_laplace2_pd(b);
	return dst[0] + dst[1];
}

extern __inline __v2sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_neg2_ps(__v2sf __X, uint8_t mod = 2, uint8_t val = 0)
{
	return (__v2sf){ (0 % mod == val) ? -__X[0] : __X[0],
	                 (1 % mod == val) ? -__X[1] : __X[1] };
}

extern __inline __v2df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_neg2_pd(__v2df __X, uint8_t mod = 2, uint8_t val = 0)
{
	return (__v2df) { (0 % mod == val) ? -__X[0] : __X[0],
	                  (1 % mod == val) ? -__X[1] : __X[1] };
}

extern __inline __v2sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_cross2_ps(__v2sf a, unsigned int winding = GL_CCW)
{
	return _mm_neg2_ps((__v2sf){1, 1}, 2, 1 - (winding % 2)) * _mm_laplace2_ps(a);
}

extern __inline __v2df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_cross2_pd(__v2df a, unsigned int winding = GL_CCW)
{
	return _mm_neg2_pd((__v2df){1, 1}, 2, 1 - (winding % 2)) * _mm_laplace2_pd(a);
}

extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_laplace3_ps(__v4sf __X, __v4sf __Y)
{
	__v4sf dst  = { _mm_det2_ps(_mm_select2_ps(__X,1,2), _mm_select2_ps(__Y,1,2)),
	                _mm_det2_ps(_mm_select2_ps(__X,0,2), _mm_select2_ps(__Y,0,2)),
	                _mm_det2_ps(_mm_select2_ps(__X,0,1), _mm_select2_ps(__Y,0,1)),
		        0
		      };
	return dst;
}

extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_laplace3_pd(__v4df __X, __v4df __Y)
{
	__v4df dst  = { _mm_det2_pd(_mm_select2_pd(__X,1,2), _mm_select2_pd(__Y,1,2)),
	                _mm_det2_pd(_mm_select2_pd(__X,0,2), _mm_select2_pd(__Y,0,2)),
	                _mm_det2_pd(_mm_select2_pd(__X,0,1), _mm_select2_pd(__Y,0,1)),
		        0
		      };
	return dst;
}

extern __inline float __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_det3_ps(__v4sf a, __v4sf b, __v4sf c)
{
	__v4sf dst = (__v4sf){1, -1, 1, 0} * a * _mm_laplace3_ps(b, c);
	return dst[0] + dst[1] + dst[2];
}

extern __inline double __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_det3_pd(__v4df a, __v4df b, __v4df c)
{
	__v4df dst = (__v4df){1, -1, 1, 0} * a * _mm_laplace3_pd(b, c);
	return dst[0] + dst[1] + dst[2];
}

extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_cross3_ps(__v4sf a, __v4sf b)
{
	return (__v4sf){1, -1, 1, 0} * _mm_laplace3_ps(a, b);
}

extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_cross3_pd(__v4df a, __v4df b)
{
	return (__v4df){1, -1, 1, 0} * _mm_laplace3_pd(a, b);
}

extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_laplace4_ps(__v4sf __X, __v4sf __Y, __v4sf __Z)
{
	__v4sf dst  = { _mm_det3_ps(_mm_select3_ps(__X,1,2,3), _mm_select3_ps(__Y,1,2,3), _mm_select3_ps(__Z,1,2,3)), 
	                _mm_det3_ps(_mm_select3_ps(__X,0,2,3), _mm_select3_ps(__Y,0,2,3), _mm_select3_ps(__Z,0,2,3)),
	                _mm_det3_ps(_mm_select3_ps(__X,0,1,3), _mm_select3_ps(__Y,0,1,3), _mm_select3_ps(__Z,0,1,3)),
		        _mm_det3_ps(_mm_select3_ps(__X,0,1,2), _mm_select3_ps(__Y,0,1,2), _mm_select3_ps(__Z,0,1,2))
		      };
	return dst;
}

extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_laplace4_pd(__v4df __X, __v4df __Y, __v4df __Z)
{
	__v4df dst  = { _mm_det3_pd(_mm_select3_pd(__X,1,2,3), _mm_select3_pd(__Y,1,2,3), _mm_select3_pd(__Z,1,2,3)), 
	                _mm_det3_pd(_mm_select3_pd(__X,0,2,3), _mm_select3_pd(__Y,0,2,3), _mm_select3_pd(__Z,0,2,3)),
	                _mm_det3_pd(_mm_select3_pd(__X,0,1,3), _mm_select3_pd(__Y,0,1,3), _mm_select3_pd(__Z,0,1,3)),
		        _mm_det3_pd(_mm_select3_pd(__X,0,1,2), _mm_select3_pd(__Y,0,1,2), _mm_select3_pd(__Z,0,1,2))
		      };
	return dst;
}

extern __inline float __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_det4_ps(__v4sf a, __v4sf b, __v4sf c, __v4sf d)
{
	__v4sf dst = (__v4sf){1, -1, 1, -1} * a * _mm_laplace4_ps(b, c, d);
	return dst[0] + dst[1] + dst[2] + dst[3];
}

extern __inline double __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_det4_pd(__v4df a, __v4df b, __v4df c, __v4df d)
{
	__v4df dst = (__v4df){1, -1, 1, -1} * a * _mm_laplace4_pd(b, c, d);
	return dst[0] + dst[1] + dst[2] + dst[3];
}

extern __inline __v4sf __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_cross4_ps(__v4sf a, __v4sf b, __v4sf c)
{
	return (__v4sf){-1, 1, -1, 1} * _mm_laplace4_ps(a, b, c);
}

extern __inline __v4df __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_cross4_pd(__v4df a, __v4df b, __v4df c)
{ 
	return (__v4df){-1, 1, -1, 1} * _mm_laplace4_pd(a, b, c);
 }

