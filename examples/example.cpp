#include <mlr/vector.hpp>
#include <mlr/color.hpp>

using namespace math;

bool test()
{
	vec::f32<4> v1[4] = { vec::f32<4>::identity(0),
	                      vec::f32<4>::identity(1),
			      vec::f32<4>::load3(vec::f32<3, align::linear>::cross3(v1[0],v1[1]).data(),0),
			      vec::f32<2>::cross4(v1[0],v1[1],v1[2]) };
	vec::f32<2> v2[2] = { vec::f32<2>::cross2(v1[0], MLR_CCW), vec::f32<2>::cross2(v1[0], MLR_CW) };
	v1[0].print_header(4, "vector");
	v1[0].print(4);
	v1[1].print(4);
	v1[2].print_header(4, "cross3");
	v1[2].print(4);
	v1[3].print_header(4, "cross4");
	v1[3].print(4);
	vec::f32<4> v3 = v2[0];
	v3.print_header(4, "cross2 MLR_CCW/MLR_CW");
	v3.print(4);
	v3 = { vec::f32<4>::dot4(v1[0],v1[1],v1[2],v2[3]) };
	v3.print_header(4, "dot4");
	v3.print(4);
	v3 = v1[0] + v1[1] + v1[2] + v1[3];
	v3.print_header(4, "sum");
	v3.print(4);
	std::cout << std::endl;
	v3.print_header(3, "vector");
	vec::f32<3>                v4 = { 1,0,0 };
	vec::f32<3, align::scalar> v5 = { 0,1,0 };
	vec::f32<3, align::linear> v6 = { 0,0,1 };
	v4.print(3);
	v5.print(3);
	v6.print(3);
	v3.print_header(3, "un/aligned add");
	vec::f32<3> v7 = v5 + v6;
	v7.print(3);
	vec::f32<3, align::scalar> v8 = v4 + v6;
	v8.print(3);
	vec::f32<3, align::linear> v9 = v4 + v5;
	v9.print(3);
	std::cout << std::endl;
	return true;
}

int main(int argc, char** argv)
{
	test();
	buf::type<vec::f32<3>,3> vv = { vec::f32<3>{0,1,2},vec::f32<3>{3,4,5},vec::f32<3>{6,7,8} };
	vv.print_header(3, "array of vector");
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

	std::cout << std::endl;
	col::u8<{R,G,B}>   dst0 = (col::u8<{R,G,B}>)RGB565;
	dst0.print_header(4, "bitfield->vector colors");
	dst0.print(4);
	col::u8<{B,G,R}>   dst3 = (col::u8<{B,G,R}>)RGB565;
	dst3.print(4);
	col::u8<math::col::argb> dst4 = (col::u8<math::col::argb>)RGBA4444;
	dst4.print(4);
	col::u8<math::col::rgba> dst1 = (col::u8<math::col::rgba>)RGBA4444;
	dst1.print(4);
	col::f32<math::col::rgba> dst5 = (col::f32<math::col::rgba>)RGBA5551;
	col::f32<math::col::abgr> dst2 = (col::f32<math::col::abgr>)RGBA5551;
	dst2.print(4);
	dst5.print(4);
	exit(EXIT_SUCCESS);
}

