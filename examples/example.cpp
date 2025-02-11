#include <mlr/vector.hpp>

using namespace math;

bool test()
{
	vec::f32<4> v1[4] = { vec::f32<4>::identity(0),
	                      vec::f32<4>::identity(1),
			      vec::f32<4>::load3(vec::f32<3, align::vector>::cross3(v1[0],v1[1]).data(),0),
			      vec::f32<2>::cross4(v1[0],v1[1],v1[2]) };
	vec::f32<2> v2[2] = { vec::f32<2>::cross2(v1[0], GL_CCW), vec::f32<2>::cross2(v1[0], GL_CW) };
	v1[0].print_header(4, "vector");
	v1[0].print(4);
	v1[1].print(4);
	v1[2].print_header(4, "cross3");
	v1[2].print(4);
	v1[3].print_header(4, "cross4");
	v1[3].print(4);
	vec::f32<4> v3 = v2[0];
	v3.print_header(4, "cross2 GL_CCW/GL_CW");
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
	exit(EXIT_SUCCESS);
}

