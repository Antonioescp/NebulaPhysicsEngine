export module Core:Precision;

import std.core;
using namespace std;

namespace Nebula
{
	inline namespace Aliases
	{
		export using real = float;
		export const extern function<real(real)> real_sqrt{ sqrtf };
		export const extern function<real(real, real)> real_pow{ powf };
	}
}