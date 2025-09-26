# mlr

mlr - single-header-only [C++23][1] linear algebra math library

## About

mlr implements aligned array [arr : std::array<T,N>][3] based vector [vec::type<T,N,A>][4] type for N-dimensional linear algebra math and Quake C++ vec_t type interface.

# Dependencies

- [C++23][1]

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
#include <mlr/color.hpp>

using namespace math;

int main(int argc, char** argv)
{
	buf::type<vec::f32<3>,3> vv = { vec::f32<3>{0,1,2},vec::f32<3>{3,4,5},vec::f32<3>{6,7,8} };
	vv.print_header(3, "arr of vector");
	vv.print(3);
	vv[0].print(3);
	vv[1].print(3);
	vv[2].print(3);

	col::u8 <{R,G,B            }> RGB888       = {1,2,3  }; // array    type
	col::u8 <{R,G,B,A          }> RGBA8888     = {1,2,3,4}; // array    type
	col::u8 <{B,G,R,A          }> BGRA8888     = {1,2,3,4}; // array    type
	col::u8 <{A,R,G,B          }> ARGB8888     = {1,2,3,4}; // array    type
	col::u8 <{A,B,G,R          }> ABGR8888     = {1,2,3,4}; // array    type

	col::f32<{R,G,B            }> RGBF32       = {1,2,3  }; // array    type
	col::f32<{R,G,B,A          }> RGBAF32      = {1,2,3,4}; // array    type
	col::f32<{A,R,G,B          }> ARGBF32      = {1,2,3,4}; // array    type
	col::f32<{A,B,G,R          }> ABGRF32      = {1,2,3,4}; // array    type
	col::f32<{B,G,R,A          }> BGRAF32      = {1,2,3,4}; // array    type

	col::u16<{R,G,B  },{5,6,5  }> RGB565       = {10,32,20};   // bitfield type
	col::u16<{B,G,R  },{5,6,5  }> BGR565       = {10,32,20};   // bitfield type
	col::u16<{R,G,B,A},{5,5,5,1}> RGBA5551     = {10,15,20,1}; // bitfield type
	col::u16<{R,G,B,A},{4,4,4,4}> RGBA4444     = {5,8,12,15};  // bitfield type

	col::u8 <{R,G,B  },{2,4,2  }> RGB242       = {1,2,3  }; // bitfield type
	col::u8 <{R,G,B,A},{2,2,2,2}> RGBA2222     = {1,2,3,0}; // bitfield type

	col::u16<{R,G,B            }> RGB161616    = {1,2,3  }; // array    type
	col::u16<{R,G,B,A          }> RGBA16161616 = {1,2,3,4}; // array    type

    exit(EXIT_SUCCESS);
}
```
```fortran
|vector                                 | typ|alg|vec|alg|mode           |cnt
|+1.00e+00 +0.00e+00 +0.00e+00 +0.00e+00|   4|  4| 16| 16|adaptive/linear|4
|+0.00e+00 +1.00e+00 +0.00e+00 +0.00e+00|   4|  4| 16| 16|adaptive/linear|4
|cross3                                 | typ|alg|vec|alg|mode           |cnt
|+0.00e+00 +0.00e+00 +1.00e+00 +0.00e+00|   4|  4| 16| 16|adaptive/linear|4
|cross4                                 | typ|alg|vec|alg|mode           |cnt
|-0.00e+00 +0.00e+00 -0.00e+00 +1.00e+00|   4|  4| 16| 16|adaptive/linear|4
|cross2 MLR_CCW/MLR_CW                  | typ|alg|vec|alg|mode           |cnt
|-0.00e+00 +1.00e+00 +0.00e+00 -1.00e+00|   4|  4| 16| 16|adaptive/linear|4
|dot4                                   | typ|alg|vec|alg|mode           |cnt
|+0.00e+00 +0.00e+00 +0.00e+00 +0.00e+00|   4|  4| 16| 16|adaptive/linear|4
|sum                                    | typ|alg|vec|alg|mode           |cnt
|+1.00e+00 +1.00e+00 +1.00e+00 +1.00e+00|   4|  4| 16| 16|adaptive/linear|4

|vector                       | typ|alg|vec|alg|mode           |cnt
|+1.00e+00 +0.00e+00 +0.00e+00|   4|  4| 12|  4|adaptive/scalar|3
|+0.00e+00 +1.00e+00 +0.00e+00|   4|  4| 12|  4|         scalar|3
|+0.00e+00 +0.00e+00 +1.00e+00|   4|  4| 16| 16|         linear|3
|un/aligned add               | typ|alg|vec|alg|mode           |cnt
|+0.00e+00 +1.00e+00 +1.00e+00|   4|  4| 12|  4|adaptive/scalar|3
|+1.00e+00 +0.00e+00 +1.00e+00|   4|  4| 12|  4|         scalar|3
|+1.00e+00 +1.00e+00 +0.00e+00|   4|  4| 16| 16|         linear|3

|array of vector              | typ|alg|vec|alg|mode           |cnt
|container container container|  12|  4| 36|  4|adaptive/scalar|3
|+0.00e+00 +1.00e+00 +2.00e+00|   4|  4| 12|  4|adaptive/scalar|3
|+3.00e+00 +4.00e+00 +5.00e+00|   4|  4| 12|  4|adaptive/scalar|3
|+6.00e+00 +7.00e+00 +8.00e+00|   4|  4| 12|  4|adaptive/scalar|3

|bitfield->vector colors                | typ|alg|vec|alg|mode           |cnt
|+82       +130      +165      +0       |   1|  1|  3|  1|adaptive/scalar|3
|+165      +130      +82       +0       |   1|  1|  3|  1|adaptive/scalar|3
|+255      +85       +136      +204     |   1|  1|  4|  4|adaptive/linear|4
|+85       +136      +204      +255     |   1|  1|  4|  4|adaptive/linear|4
|+1.00e+00 +6.45e-01 +4.84e-01 +3.23e-01|   4|  4| 16| 16|adaptive/linear|4
|+3.23e-01 +4.84e-01 +6.45e-01 +1.00e+00|   4|  4| 16| 16|adaptive/linear|4
```
# Links
## Other C++ Math Libraries
- [ctmd][32]
- [linalg][28]
- [glm][35]
- [ITK][8]
- [vxl/vnl][9]
- [Terathon-Math-Library][10]
- [mr-math][11]
- [versor][12]
- [cutlass][33]
- [eve][34]
- [nicemath][36]
## Other OpenCL/SYCL/CUDA linear algebra vector type implementations
- [OpenGL/KHR][2]
- [SYCL Overview][23]
- [OpenCL][24]
- [CUDA C++ Programming Guide][25]
## Quake C++ Math Libraries
- [TrenchBroom/vm][5]
- [ericwa/ericw-tools][26]
- [a1batross/fakk2-sdk][21]
- [Prey2006/neo/idlib/math][22]
- [andrei-drexler/q321][27]
- [hogsy/chronon][29]
## War for the Overworld C++ Math Library 
- [CML][20]
## Math code/tutorials
- [Let's remove Quaternions from every 3D Engine][31]
- [Rotors: A practical introduction for 3D graphics][30]
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
[26]: https://github.com/ericwa/ericw-tools/blob/main/include/common/qvec.hh
[6]: https://github.com/quakeforge/quakeforge/tree/master/include/QF/simd
[7]: https://github.com/fte-team/fteqw
[27]: https://github.com/andrei-drexler/q321/blob/main/src/engine/math.h
[29]: https://github.com/hogsy/chronon/blob/master/qcommon/include/qcommon/math_vector.h

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
[21]: https://github.com/a1batross/fakk2-sdk/blob/master/source/source/qcommon/vector.h
[22]: https://github.com/FriskTheFallenHuman/Prey2006/blob/master/neo/idlib/math
[23]: https://www.khronos.org/sycl/
[24]: https://www.khronos.org/opencl/
[25]: https://docs.nvidia.com/cuda/cuda-c-programming-guide/
[28]: https://github.com/SideShowBoBGOT/linalg-conan
[30]: https://jacquesheunis.com/post/rotors/
[31]: https://marctenbosch.com/quaternions/
[32]: https://github.com/uomrobotic/ctmd/
[33]: https://github.com/NVIDIA/cutlass/
[34]: https://github.com/jfalcou/eve/
[35]: https://github.com/g-truc/glm/
[36]: https://github.com/nicebyte/nicemath/
