
	namespace col
	{
		/* RGBA permute swizzle and bit sizes color format type */
		using fmt = std::pair<std::array<typ::idx8, 4>, std::array<typ::idx8, 4>>;

		static constexpr fmt rgb565       = {{0,1,2,3}, {5,6,5,0}};
		static constexpr fmt bgr565       = {{2,1,0,3}, {5,6,5,0}};

		static constexpr fmt rgba4444     = {{0,1,2,3}, {4,4,4,4}};
		static constexpr fmt bgra4444     = {{2,1,0,3}, {4,4,4,4}};
		static constexpr fmt argb4444     = {{3,0,1,2}, {4,4,4,4}};

		static constexpr fmt rgba8888     = {{0,1,2,3}, {8,8,8,8}};
		static constexpr fmt bgra8888     = {{2,1,0,3}, {8,8,8,8}};
		static constexpr fmt argb8888     = {{3,0,1,2}, {8,8,8,8}};

		static constexpr fmt rgba16161616 = {{0,1,2,3}, {16,16,16,16}};
		static constexpr fmt bgra16161616 = {{2,1,0,3}, {16,16,16,16}};
		static constexpr fmt argb16161616 = {{3,0,1,2}, {16,16,16,16}};

		static constexpr fmt rgbaf32      = {{0,1,2,3}, {32,32,32,32}};
		static constexpr fmt bgraf32      = {{2,1,0,3}, {32,32,32,32}};
		static constexpr fmt argbf32      = {{3,0,1,2}, {32,32,32,32}};

		static constexpr fmt rgbaf64      = {{0,1,2,3}, {64,64,64,64}};
		static constexpr fmt bgraf64      = {{2,1,0,3}, {64,64,64,64}};
		static constexpr fmt argbf64      = {{3,0,1,2}, {64,64,64,64}};

		/* integer vector color type */
		template<fmt format = rgba8888, size_t N = 4>
		using u8  = vec::u8<N>;
		/* single precision floating point color type */
		template<fmt format = rgbaf32 , size_t N = 4>
		using f32  = vec::f32<N>;
		/* double precision floating point color type */
		template<fmt format = rgbaf64 , size_t N = 4>
		using f64  = vec::f64<N>;

		enum index : uint8_t
		{
			r    =  0,
			g    =  1,
			b    =  2,
			a    =  3,
			rgba =  8,
		        none = (uint8_t)-1,
		};

		/* bitfield color type with optional last component masked access because of missing zero width named bitfield */
		template<fmt format>
		struct bitfield_color
		{
			static constexpr const std::array<typ::idx8,4> perm = format.first;
			static constexpr const std::array<typ::idx8,4> bits = format.second;
			static constexpr const size_t                  size = std::bit_ceil((unsigned)std::accumulate(bits.begin(), bits.end(), 0));
			static constexpr const size_t            components = std::count_if<bits.begin(), bits.end(), non_zero>;
			using element_type = std::make_unsigned_t<__int_with_sizeof_t<std::bit_ceil((unsigned)*std::max_element(bits.begin(), bits.end()))/8>>;
			using storage_type = std::make_unsigned_t<__int_with_sizeof_t<size/8>>;
			static constexpr std::array<typ::idx8, 4>   shift = {   0  , bits[perm[col::r]], (bits[perm[col::r]] + bits[perm[col::g]]), (bits[perm[col::r]] + bits[perm[col::g]] + bits[perm[col::b]]) };
			static constexpr std::array<storage_type, 4> mask = { ((1 << bits[perm[col::r]]) - 1) << 0,
			                                                      ((1 << bits[perm[col::g]]) - 1) <<  bits[perm[col::r]],
			                                                      ((1 << bits[perm[col::b]]) - 1) << (bits[perm[col::r]] + bits[perm[col::g]]),
			                                                      ((1 << bits[perm[col::a]]) - 1) << (bits[perm[col::r]] + bits[perm[col::g]] + bits[perm[col::b]]) };

			union
			{
				struct
				{
					storage_type c0 : bits[perm[col::r]];
					storage_type c1 : bits[perm[col::g]];
					storage_type c2 : bits[perm[col::b]];
				};
				storage_type c3;
			};
			bitfield_color(element_type r = 0, element_type g = 0, element_type b = 0, element_type a = 0) : c3(0)
			{
				set(col::r, r);
				set(col::g, g);
				set(col::b, b);
				set(col::a, a);
			}
			inline constexpr         void set(size_t i, element_type val)
			{
				if(i == col::none) return;
				if(i >= col::rgba)
				{
					for(uint8_t j = 0; j <= col::a; j++)
						c3 |= (val << shift[perm[j]]) & mask[perm[j]];
					return;
				}
				c3 |= (val << shift[perm[i]]) & mask[perm[i]];
			}

			inline constexpr element_type get(size_t i) const
			{ 
				switch(perm[i])
				{
					case col::r: return c0; 
					case col::g: return c1;
					case col::b: return c2;
					case col::a: return ((c3 & mask[col::a]) >> shift[col::a]);
					default: return c3;
				}
			}
			inline constexpr element_type operator[](size_t i) const { return get(i); }

			inline constexpr element_type r() const { return get(col::r); }
			inline constexpr element_type g() const { return get(col::g); }
			inline constexpr element_type b() const { return get(col::b); }
			inline constexpr element_type a() const { return get(col::a); }

			inline constexpr operator vec::f32<4>() const
			{
				return (vec::f32<4>)
				{
					(typ::f32)r() / ((1 << bits[perm[col::r]]) - 1),
					(typ::f32)g() / ((1 << bits[perm[col::g]]) - 1),
					(typ::f32)b() / ((1 << bits[perm[col::b]]) - 1),
					(typ::f32)a() / ((1 << bits[perm[col::a]]) - 1)
				};
			}
			inline constexpr operator vec::u8<4>() const
			{
				return vec::ubroundf<4>(((vec::f32<4>)(*this)) * UINT8_MAX);
			}
		};

		/* 16-bit bitfield color type */
		template<fmt format = rgb565>
		using u16 = bitfield_color<format>;
		/* 32-bit bitfield color type */
		template<fmt format = rgba8888>
		using u32 = bitfield_color<format>;
		/* 64-bit bitfield color type */
		template<fmt format = rgba16161616>
		using u64 = bitfield_color<format>;

	};
