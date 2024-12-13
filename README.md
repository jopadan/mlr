# mlr

MLR - single-header-only [C++26] linear algebra math library

## About

MLR implements aligned [fixed_valarray : std::array<T,N>] vector math using [GL/glcorearb.h] scalar types

# Dependencies

- [C++26]
- [GL/glcorearb.h]

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

bool test_cross2()
{
	vec::f64<2> src = vec::f64<2>::one(0);
	vec::f64<2, align::element> a = { vec::f64<2>::cross2(src, GL_CCW) };
	vec::f64<2, align::vector>  b = { vec::f64<2>::cross2(src, GL_CW)  };

	printf("%-19s: %3s/%3s/%3s/%3s\n", "test_cross2", "typ", "cnt", "alg", "len");
	printf("%+8f %+8f: %3zu/%3zu/%3zu/%3zu\n", src[0], src[1], sizeof(f64), src.size(), alignof(src), sizeof(src));
	printf("%+8f %+8f: %3zu/%3zu/%3zu/%3zu\n", a[0], a[1], sizeof(f64), a.size(), alignof(a), sizeof(a));
	printf("%+8f %+8f: %3zu/%3zu/%3zu/%3zu\n", b[0], b[1], sizeof(f64), b.size(), alignof(b), sizeof(b));
	return true;
}

bool test_cross3()
{
	vec::f64<4> a = vec::f64<4>::one(0);
	vec::f64<3> b = vec::f64<3>::one(1);;
	vec::f64<3, align::vector> c = vec::f64<3>::cross3(a,b);
	vec::f64<4, align::element> d = b + c;

	printf("%-39s: %3s/%3s/%3s/%3s\n", "test_cross3", "typ", "cnt", "alg", "len");
	printf("%+8f %+8f %+8f %+8f: %3zu/%3zu/%3zu/%3zu\n", a[0], a[1], a[2], a[3], sizeof(f64), a.size(), alignof(a), sizeof(a));
	printf("%+8f %+8f %+8f %+8f: %3zu/%3zu/%3zu/%3zu\n", b[0], b[1], b[2], b[3], sizeof(f64), b.size(), alignof(b), sizeof(b));
	printf("%+8f %+8f %+8f %+8f: %3zu/%3zu/%3zu/%3zu\n", c[0], c[1], c[2], c[3], sizeof(f64), c.size(), alignof(c), sizeof(c));
	printf("%+8f %+8f %+8f %+8f: %3zu/%3zu/%3zu/%3zu\n", d[0], d[1], d[2], d[3], sizeof(f64), d.size(), alignof(d), sizeof(d));
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
```
# Links
- [ITK]
- [TrenchBroom/vm]
- [vxl/vnl]
- [mr-math]
- [versor]
- [Terathon-Math-Library]
- [Terathon Software LLC]
- [Permutation]
- [Parity Theorem for Permutations]
- [Levi-Civita symbol]
- [Hodge star operator]
- [How to Generate a Cube's vertices and tris]
- [par]
- [RGB565 to RGB888]

[C++26]: https://isocpp.org/
[GL/glcorearb.h]: https://github.com/KhronosGroup/OpenGL-Registry/blob/main/api/GL/glcorearb.h
[fixed_valarray : std::array<T,N>]: https://github.com/jopadan/mlr/blob/main/include/MLR/fixed_valarray.hpp
[ITK]: https://github.com/InsightSoftwareConsortium/ITK
[TrenchBroom/vm]: https://github.com/TrenchBroom/TrenchBroom/tree/master/lib/vm
[vxl/vnl]: https://github.com/vxl/vxl/tree/master/core/vnl
[mr-math]: https://github.com/4J-company/mr-math/
[versor]: https://github.com/wolftype/versor/
[Terathon-Math-Library]: https://github.com/EricLengyel/Terathon-Math-Library
[Terathon Software LLC]: https://terathon.com/index.html
[Permutation]: https://en.wikipedia.org/wiki/Permutation
[Parity Theorem for Permutations]: https://maa.org/book/export/html/115646
[Levi-Civita symbol]: https://en.wikipedia.org/wiki/Levi-Civita_symbol
[Hodge star operator]: https://en.wikipedia.org/wiki/Hodge_star_operator
[How to Generate a Cube's vertices and tris]: https://catonif.github.io/cube/
[par]: https://github.com/prideout/par/
[RGB565 to RGB888]: https://retrocomputing.stackexchange.com/questions/27400/what-is-the-most-accurate-way-to-map-6-bit-vga-palette-to-8-bit
