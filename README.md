# mlr

MLR - single-header-only [C++26][1] linear algebra math library

## About

MLR implements aligned [fixed_valarray : std::array<T,N>][3] vector math using [OpenGL/KHR][2] scalar types

# Dependencies

- [C++26][1]
- [OpenGL/KHR][2]

## Building

```sh
cmake . --install-prefix=/usr
make install
```

### Optimization

Change `CMakeLists.txt` compile flags to fit your needs:
```sh
add_compile_options(-march=native -mfpmath=[your SIMD instruction set] -O3)
```

## Usage

```c++
#include <MLR/mlr.hpp>

using namespace math;

bool test_cross()
{
	vec::f64<4> src[4] = { vec::f64<4>::identity(0),
	                       vec::f64<4>::identity(1),
			       vec::f64<4>::load3(vec::f64<3, align::vector>::cross3(src[0],src[1]).data(),0),
			       vec::f64<2>::cross4(src[0],src[1],src[2]) };

	vec::f64<2>   a[2] = { vec::f64<2>::cross2(src[0], GL_CCW), vec::f64<2>::cross2(src[0], GL_CW) };

	printf("%-39s: %3s/%3s/%3s/%3s\n", "test_cross", "typ", "cnt", "alg", "len");
	printf("%+8f %+8f %+8f %+8f: %3zu/%3zu/%3zu/%3zu\n", a[0][0], a[0][1], a[1][0], a[1][1], sizeof(f64), a[0].size(), alignof(a[0]), sizeof(a[0]));
	printf("%+8f %+8f %+8f %+8f: %3zu/%3zu/%3zu/%3zu\n", src[2][0], src[2][1], src[2][2], src[2][3], sizeof(f64), (size_t)3, alignof(src[2]), sizeof(src[2]));
	printf("%+8f %+8f %+8f %+8f: %3zu/%3zu/%3zu/%3zu\n", src[3][0], src[3][1], src[3][2], src[3][3], sizeof(f64), src[3].size(), alignof(src[3]), sizeof(src[3]));
	return true;
}

bool test_dot()
{
	vec::f64<4> a = {1,2,3,4};
	vec::u64<4> b = {5,6,7,8};
	vec::i64<4> c = {9,10,11,12};
	vec::i32<4> d = {13,14,15,16};
	printf("%f\n",vec::f64<4>::dot4(a,b,c,d));
	return true;
}
```
```sh
test_cross2        : typ/cnt/alg/len
+1.000000 +0.000000:   8/  2/ 16/ 16
-0.000000 +1.000000:   8/  2/  8/ 16
+0.000000 -1.000000:   8/  2/ 16/ 16

test_cross3                            : typ/cnt/alg/len
+1.000000 +0.000000 +0.000000 +0.000000:   8/  4/ 32/ 32
+0.000000 +1.000000 +0.000000 -0.000000:   8/  3/  8/ 24
+0.000000 +0.000000 +1.000000 -0.000000:   8/  3/ 32/ 32
+0.000000 +1.000000 +1.000000 -0.000000:   8/  4/  8/ 32


test_cross2                            : typ/cnt/alg/len
-0.000000 +1.000000 +0.000000 -1.000000:   8/  2/ 16/ 16
test_cross3                            : typ/cnt/alg/len
+0.000000 +0.000000 +1.000000 +0.000000:   8/  3/ 32/ 32
test_cross4                            : typ/cnt/alg/len
-0.000000 +0.000000 -0.000000 +1.000000:   8/  4/ 32/ 32

test_dot4                              
11874.000000
```
# Links
## Other Math Libraries
- [ITK][7]
- [vxl/vnl][8]
- [Terathon-Math-Library][9]
- [mr-math][10]
- [versor][11]
## Quake Math Libraries
- [TrenchBroom/vm][4]
- [QF/simd][5]
- [fte-team/fteqw][6]
## Math code/tutorials
- [Permutation][12]
- [Parity Theorem for Permutations][13]
- [Levi-Civita symbol][14]
- [Hodge star operator][15]
- [How to Generate a Cube's vertices and tris][16]
- [par][17]
- [RGB565 to RGB888][18]

[1]: https://isocpp.org/
[2]: https://github.com/KhronosGroup/OpenGL-Registry/blob/main/api/GL/glcorearb.h
[3]: https://github.com/jopadan/mlr/blob/main/include/MLR/fixed_valarray.hpp

[4]: https://github.com/TrenchBroom/TrenchBroom/tree/master/lib/vm
[5]: http://github.com/quakeforge/quakeforge/tree/master/include/QF/simd
[6]: http://github.com/fte-team/fteqw

[7]: https://github.com/InsightSoftwareConsortium/ITK
[8]: https://github.com/vxl/vxl/tree/master/core/vnl
[9]: https://github.com/EricLengyel/Terathon-Math-Library
[10]: https://github.com/4J-company/mr-math/
[11]: https://github.com/wolftype/versor/

[12]: https://en.wikipedia.org/wiki/Permutation
[13]: https://maa.org/book/export/html/115646
[14]: https://en.wikipedia.org/wiki/Levi-Civita_symbol
[15]: https://en.wikipedia.org/wiki/Hodge_star_operator
[16]: https://catonif.github.io/cube/
[17]: https://github.com/prideout/par/
[18]: https://retrocomputing.stackexchange.com/questions/27400/what-is-the-most-accurate-way-to-map-6-bit-vga-palette-to-8-bit
