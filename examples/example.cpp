#include <mlr/vector.hpp>

using namespace math;

bool test_cross()
{
	vec::f64<4> src[4] = { vec::f64<4>::identity(0),
	                       vec::f64<4>::identity(1),
			       vec::f64<4>::load3(vec::f64<3, align::vector>::cross3(src[0],src[1]).data(),0),
			       vec::f64<2>::cross4(src[0],src[1],src[2]) };

	src[0].print_header(2, "vector");
	src[0].print(2);
	vec::f64<2>   a[2] = { vec::f64<2>::cross2(src[0], GL_CCW), vec::f64<2>::cross2(src[0], GL_CW) };
	std::cout << std::endl;
	vec::f64<2>::print_header(2,"cross2 GL_CCW/GL_CW");
	a[0].print(2);
	a[1].print(2);

	std::cout << std::endl;
	print_alignment = false;
	src[2].print_header(4, "print_alignment=false");
	src[2].print(4);
	src[3].print(4);
	print_alignment = true;
	std::cout << std::endl;
	return true;
}

bool test_dot()
{
	vec::f64<4> a = {1,2,3,4};
	vec::u64<4> b = {5,6,7,8};
	vec::i64<4> c = {9,10,11,12};
	vec::i32<4> d = {13,14,15,16};
	a.print_header(4, "vector");
	a.print();
	b.print();
	c.print();
	d.print();
	std::cout << std::endl;
	vec::f64<1> dot = { vec::f64<4>::dot4(a,b,c,d) };
	dot.print_header(1, "dot4");
	dot.print(1);
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
	a.print_header(4, "add different alignment");
	a.print(4);
	b.print(4);
	d.print(4);
	c.print(4);
	std::cout << std::endl;
	test_dot();
	std::cout << std::endl;
	vec4_t q1 = vec4_t::identity(0);
	vec4_t q2 = vec4_t::identity(1);
	vec4_t q3 = vec4_t::identity(2);
	vec4_t q4 = vec4_t::cross4(q1,q2,q3);
	q1.print_header(4, "vector");
	q1.print(4);
	q2.print(4);
	q3.print(4);
	std::cout << std::endl;
	q4.print_header(4, "cross4");
	q4.print(4);
	exit(EXIT_SUCCESS);
}

