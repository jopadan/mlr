# mlr

mlr - single-header-only [C++26][1] linear algebra math library

## About

mlr implements aligned array [arr : std::array<T,N>][3] based vector [vec::type<T,N,A>][4] type for N-dimensional linear algebra math using [OpenGL/KHR][2] scalar types

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
#include <mlr/vector.hpp>

using namespace math;

bool test_cross()
{
	vec::f64<4> src[4] = { vec::f64<4>::identity(0),
	                       vec::f64<4>::identity(1),
			       vec::f64<4>::load3(vec::f64<3, align::vector>::cross3(src[0],src[1]).data(),0),
			       vec::f64<2>::cross4(src[0],src[1],src[2]) };

	vec::f64<2>   a[2] = { vec::f64<2>::cross2(src[0], GL_CCW), vec::f64<2>::cross2(src[0], GL_CW) };

	a[0].print_header(4,"test_cross2");
	a[0].print(4);
	src[2].print(4);
	src[3].print(4);
	return true;
}

bool test_dot()
{
	vec::f64<4> a = {1,2,3,4};
	vec::u64<4> b = {5,6,7,8};
	vec::i64<4> c = {9,10,11,12};
	vec::i32<4> d = {13,14,15,16};
	printf("%-39s\n", "test_dot4");
	printf("%f\n",vec::f64<4>::dot4(a,b,c,d));
	return true;
}

int main(int argc, char** argv)
{
	test_cross();
	vec::f32<4> d = { 5,6,7,8 };
	vec::f32<4, align::scalar> c = { 1,2,3,4 };
	vec::f32<3> a = { 5,6,7 };
	vec::f32<3, align::vector> b = { 1,2,3 };
	a+=b;
	b+=a;
	a.print();
	b.print();
	d.print();
	c.print();
	printf("\n");
	test_dot();
	printf("\n");
	exit(EXIT_SUCCESS);
}

```
```sh
|test_cross2                            | typ|alg|vec|alg|mode           |cnt
|-0.00e+00 +1.00e+00 +0.00e+00 -1.00e+00|   8|  8| 16| 16|adaptive/vector|2
|+0.00e+00 +0.00e+00 +1.00e+00 +0.00e+00|   8|  8| 32| 32|adaptive/vector|4
|-0.00e+00 +0.00e+00 -0.00e+00 +1.00e+00|   8|  8| 32| 32|adaptive/vector|4
|+6.00e+00 +8.00e+00 +1.00e+01 +4.56e-41|   4|  4| 12|  4|adaptive/scalar|3
|+7.00e+00 +1.00e+01 +1.30e+01 +4.56e-41|   4|  4| 16| 16|         vector|3
|+5.00e+00 +6.00e+00 +7.00e+00 +8.00e+00|   4|  4| 16| 16|adaptive/vector|4
|+1.00e+00 +2.00e+00 +3.00e+00 +4.00e+00|   4|  4| 16|  4|         scalar|4

test_dot4                              
11874.000000
```
# Links
## Other C++ Math Libraries
- [ITK][8]
- [vxl/vnl][9]
- [Terathon-Math-Library][10]
- [mr-math][11]
- [versor][12]
## Quake C++ Math Libraries
- [TrenchBroom/vm][5]
- [fakk2-rework][21]
- [Prey2006/neo/idlib/math][22]
## War for the Overworld C++ Math Library 
- [CML][20]
## Math code/tutorials
- [Permutation][13]
- [Parity Theorem for Permutations][14]
- [Levi-Civita symbol][15]
- [Hodge star operator][16]
- [How to Generate a Cube's vertices and tris][17]
- [par][18]
- [RGB565 to RGB888][19]

[1]: https://isocpp.org/
[2]: https://github.com/KhronosGroup/OpenGL-Registry/blob/main/api/GL/glcorearb.h
[3]: https://github.com/jopadan/mlr/blob/main/include/mlr/array.hpp
[4]: https://github.com/jopadan/mlr/blob/main/include/mlr/vector.hpp

[5]: https://github.com/TrenchBroom/TrenchBroom/tree/master/lib/vm
[6]: http://github.com/quakeforge/quakeforge/tree/master/include/QF/simd
[7]: http://github.com/fte-team/fteqw

[8]: https://github.com/InsightSoftwareConsortium/ITK
[9]: https://github.com/vxl/vxl/tree/master/core/vnl
[10]: https://github.com/EricLengyel/Terathon-Math-Library
[11]: https://github.com/4J-company/mr-math/
[12]: https://github.com/wolftype/versor/

[13]: https://en.wikipedia.org/wiki/Permutation
[14]: https://maa.org/book/export/html/115646
[15]: https://en.wikipedia.org/wiki/Levi-Civita_symbol
[16]: https://en.wikipedia.org/wiki/Hodge_star_operator
[17]: https://catonif.github.io/cube/
[18]: https://github.com/prideout/par/
[19]: https://retrocomputing.stackexchange.com/questions/27400/what-is-the-most-accurate-way-to-map-6-bit-vga-palette-to-8-bit
[20]: https://github.com/demianmnave/CML
[21]: https://github.com/Sporesirius/fakk2-rework
[22]: https://github.com/FriskTheFallenHuman/Prey2006/blob/master/neo/idlib/math

