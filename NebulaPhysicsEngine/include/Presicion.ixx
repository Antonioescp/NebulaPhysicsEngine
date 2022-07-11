export module Core:Precision;

import std.core;
using namespace std;

namespace Nebula
{
	inline namespace Aliases
	{
		export using real = float;
		export const extern function<real(real)> RealSqrt{ sqrtf };
		export const extern function<real(real, real)> RealPow{ powf };
	}
}