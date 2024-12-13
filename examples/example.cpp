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
int main(int argc, char** argv)
{
	test_cross();
	printf("\n");
	test_dot();
	printf("\n");
	exit(EXIT_SUCCESS);
}

