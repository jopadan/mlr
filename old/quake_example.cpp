#include <idlib/math.hpp>

template<iscalar T, vec<uint8_t, 4> bits = { 4,4,4,4 }, vec<uint8_t, 4> perm = {0,1,2,3}, vec<uint8_t , 4> shift = { 0, bits[perm[0]], bits[perm[0]] + bits[perm[1]], bits[perm[0]] + bits[perm[1]] + bits[perm[2]] }, vec<T, 4> mask  = { ((1 << bits[perm[0]]) - 1) << shift[0], ((1 << bits[perm[1]]) - 1) << shift[1], ((1 << bits[perm[2]]) - 1) << shift[2], ((1 << bits[perm[3]]) - 1) << shift[3] } >
union bitfield_color
{
	T v = 0;
	bitfield_color() = default;
	bitfield_color(std::initializer_list<T> list) : v(0)
	{
		size_t i = 0;
		for(T c : list)
			set(i++, c);
	}
	void inline set(size_t i, T val) { v |= (val << shift[i]) & mask[i]; }
	T inline get(size_t i) { return (v & mask[i]) >> shift[i]; }
	T inline r(T val = (T)-1) { if(val != (T)-1) set(0, val); return get(0); }
	T inline g(T val = (T)-1) { if(val != (T)-1) set(1, val); return get(1); }
	T inline b(T val = (T)-1) { if(val != (T)-1) set(2, val); return get(2); }
	T inline a(T val = (T)-1) { if(val != (T)-1) set(3, val); return get(3); }

	operator col<uint8_t, 4>()
	{
		col<uint8_t, 4> dst;
		for(size_t i = 0; i < std::min<size_t>(bits.size(),dst.size()); i++)
			dst[i] = (uint8_t)lroundf(((float)get(i) / ((1 << bits[perm[i]]) - 1) * UINT8_MAX));

		if(bits[perm[3]] == 0)
			dst += (col<uint8_t,4>::set1(UINT8_MAX) - dst) * (1 - (uint8_t)lroundf(((float)a() / ((1 << bits[perm[3]]) - 1) * UINT8_MAX)));

		return dst;
	}
	operator col<float, 4>()
	{
		col<uint8_t, 4> tmp = ((col<uint8_t, 4>)(*this));
		return (col<float, 4>){ (float)tmp[0]/(UINT8_MAX), (float)tmp[1]/(UINT8_MAX), (float)tmp[2]/(UINT8_MAX), (float)tmp[3]/(UINT8_MAX) };
	}
};

int main(int argc, char** argv)
{
	bitfield_color<uint16_t, {4,4,4,4}, {0,1,2,3}> foo;
	foo.r(0);
	foo.g(4);
	foo.b(8);
	foo.a(15);
	col<uint8_t, 4> f = (col<uint8_t,4>)foo;
	col<float, 4> g = (col<float,4>)foo;
	printf("%f %f %f %f\n", g[0], g[1], g[2], g[3]);
	printf("%hhu %hhu %hhu %hhu\n", f[0], f[1], f[2], f[3]);
	printf("%hhu %hhu %hhu %hhu\n", foo.r(), foo.g(), foo.b(), foo.a());
/*
	mat<vecd_t, 5, 4> a = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{14,15,16,17}};
	vec4d_t v4 = load3<vecd_t>(&a[0][0], 5);
	vec3d_t v3 = store3<vecd_t>(v4);

	v4 = permute<vecd_t,4>(v4, 3,1,2,0);
	v3 = permute<vecd_t,3>(v3, 2,1,0);
	col::u16<col::rgb565> c = { 23, 34, 12 };
	vec4f_t cf = (vec4f_t)c;
	byte_vec4_t cfb = (byte_vec4_t)c;
	printf("color: [%f %f %f %f]: %zu/%zu\n", cf[0], cf[1], cf[2], cf[3], sizeof(v4), alignof(v4));
	printf("color: [%hhu %hhu %hhu %hhu]: %zu/%zu\n", cfb[0], cfb[1], cfb[2], cfb[3], sizeof(v4), alignof(v4));
	printf("color: [%hhu %hhu %hhu]: %zu/%zu\n", c[0], c[1], c[2], sizeof(c), alignof(c));
	
	printf("v3: [%f %f %f]: %zu/%zu\n", v3[0], v3[1], v3[2], sizeof(v3), alignof(v3));
	printf("v4: [%f %f %f %f]: %zu/%zu\n", v4[0], v4[1], v4[2], v4[3], sizeof(v4), alignof(v4));
	exit(EXIT_SUCCESS);
*/
}
