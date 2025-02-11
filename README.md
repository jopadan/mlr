# mlr

mlr - single-header-only [C++26][1] linear algebra math library

## About

mlr implements aligned array [arr : std::array<T,N>][3] based vector [vec::type<T,N,A>][4] type for N-dimensional linear algebra math using [OpenGL/KHR][2] providing a base compatibility type interface for Quake C++ vec_t based types.

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

int main(int argc, char** argv)
{
    vec::f32<3> A = { vec::f32<3>::identity(0),
                      vec::f32<3>::identity(1),
                      vec::f32<3>::identity(2) };

    A[2] = vec::f32<3>::cross3(A[0],A[1]);

    A[2].print_header(3, "cross3");
    A[2].print(3);

	exit(EXIT_SUCCESS);
}
```
```fortran
|vector                                 | typ|alg|vec|alg|mode           |cnt
|+1.00e+00 +0.00e+00 +0.00e+00 +0.00e+00|   4|  4| 16| 16|adaptive/vector|4
|+0.00e+00 +1.00e+00 +0.00e+00 +0.00e+00|   4|  4| 16| 16|adaptive/vector|4
|cross3                                 | typ|alg|vec|alg|mode           |cnt
|+0.00e+00 +0.00e+00 +1.00e+00 +0.00e+00|   4|  4| 16| 16|adaptive/vector|4
|cross4                                 | typ|alg|vec|alg|mode           |cnt
|-0.00e+00 +0.00e+00 -0.00e+00 +1.00e+00|   4|  4| 16| 16|adaptive/vector|4
|cross2 GL_CCW/GL_CW                    | typ|alg|vec|alg|mode           |cnt
|-0.00e+00 +1.00e+00 +0.00e+00 -1.00e+00|   4|  4| 16| 16|adaptive/vector|4
|dot4                                   | typ|alg|vec|alg|mode           |cnt
|+0.00e+00 +0.00e+00 +0.00e+00 +0.00e+00|   4|  4| 16| 16|adaptive/vector|4
|sum                                    | typ|alg|vec|alg|mode           |cnt
|+1.00e+00 +1.00e+00 +1.00e+00 +1.00e+00|   4|  4| 16| 16|adaptive/vector|4

|vector                       | typ|alg|vec|alg|mode           |cnt
|+1.00e+00 +0.00e+00 +0.00e+00|   4|  4| 12|  4|adaptive/scalar|3
|+0.00e+00 +1.00e+00 +0.00e+00|   4|  4| 12|  4|         scalar|3
|+0.00e+00 +0.00e+00 +1.00e+00|   4|  4| 16| 16|         vector|3
|un/aligned add               | typ|alg|vec|alg|mode           |cnt
|+0.00e+00 +1.00e+00 +1.00e+00|   4|  4| 12|  4|adaptive/scalar|3
|+1.00e+00 +0.00e+00 +1.00e+00|   4|  4| 12|  4|         scalar|3
|+1.00e+00 +1.00e+00 +0.00e+00|   4|  4| 16| 16|         vector|3
```
# Links
## Other C++ Math Libraries
- [ITK][8]
- [vxl/vnl][9]
- [Terathon-Math-Library][10]
- [mr-math][11]
- [versor][12]
## Other OpenCL/SYCL/CUDA linear algebra vector type implementations
- [SYCL Overview][23]
- [OpenCL][24]
- [CUDA C++ Programming Guide][25]
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
[23]: https://www.khronos.org/sycl/
[24]: https://www.khronos.org/opencl/
[25]: https://docs.nvidia.com/cuda/cuda-c-programming-guide/
