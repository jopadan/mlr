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

	std::cout << std::endl;
	col::u8<0,1,2,3> rgba8888 = { 23, 123, 53, 222 };
	rgba8888.print_header(4, "color RGBA8888");
	rgba8888.print(4);
	col::u8<0,1,2> rgb888 = { 23, 123, 53 };
	rgb888.print_header(3, "color RGB888");
	rgb888.print(3);
	exit(EXIT_SUCCESS);
}

