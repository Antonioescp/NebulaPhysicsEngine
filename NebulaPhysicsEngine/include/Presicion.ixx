export module Core:Precision;

import std.core;
using namespace std;

namespace Nebula
{
	inline namespace Aliases
	{

		// A floating-point number
		export using real = float;

		export const extern function<real(real)> RealSqrt{ sqrtf };
		export const extern function<real(real, real)> RealPow{ powf };
		export const extern function<real(real)> RealAbs{ fabsf };
	}
}