#include <mlr/vector.hpp>
#include <mlr/color.hpp>

using namespace math;

bool test()
{
	vec::f32<4> v1[4] = { vec::f32<4>::identity(0),
	                      vec::f32<4>::identity(1),
			      vec::f32<4>::load3(vec::f32<3, align::vector>::cross3(v1[0],v1[1]).data(),0),
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
	vec::f32<3, align::vector> v6 = { 0,0,1 };
	v4.print(3);
	v5.print(3);
	v6.print(3);
	v3.print_header(3, "un/aligned add");
	vec::f32<3> v7 = v5 + v6;
	v7.print(3);
	vec::f32<3, align::scalar> v8 = v4 + v6;
	v8.print(3);
	vec::f32<3, align::vector> v9 = v4 + v5;
	v9.print(3);
	std::cout << std::endl;
	return true;
}

int main(int argc, char** argv)
{
	test();
	arr<vec::f32<3>,3> vv = { vec::f32<3>{0,1,2},vec::f32<3>{3,4,5},vec::f32<3>{6,7,8} };
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

	col::f32<{R,G,B            }> RGB32        = {1,2,3  }; // array    type
	col::f32<{R,G,B,A          }> RGBA32       = {1,2,3,4}; // array    type
	col::f32<{A,R,G,B          }> ARGB32       = {1,2,3,4}; // array    type
	col::f32<{A,B,G,R          }> ABGR32       = {1,2,3,4}; // array    type
	col::f32<{B,G,R,A          }> BGRA32       = {1,2,3,4}; // array    type

	col::u16<{R,G,B  },{5,6,5  }> RGB565       = {1,2,3  }; // bitfield type
	col::u16<{R,G,B,A},{4,4,4,4}> RGBA4444     = {1,2,3,4}; // bitfield type

	col::u8 <{R,G,B  },{2,4,2  }> RGB242       = {1,2,3  }; // bitfield type
	col::u8 <{R,G,B,A},{2,2,2,2}> RGBA2222     = {1,2,3,0}; // bitfield type

	col::u16<{R,G,B            }> RGB161616    = {1,2,3  }; // array    type
	col::u16<{R,G,B,A          }> RGBA16161616 = {1,2,3,4}; // array    type

	exit(EXIT_SUCCESS);
}

