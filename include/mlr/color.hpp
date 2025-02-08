#pragma once

namespace math
{
	/* quake color */
	union color4ub_t
	{
		vec::type<u8,4> rgba;
		uint32_t u32;
	};
};
