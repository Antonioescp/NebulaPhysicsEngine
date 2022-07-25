#pragma once

#include <cmath>
#include <functional>

namespace Nebula
{
	inline namespace Aliases
	{
		using real = float;

		const std::function<real(real)> RealSqrt{sqrtf};
		const std::function<real(real, real)> RealPow{ powf };
		const std::function<real(real)> RealAbs{ fabsf };
		const std::function<real(real)> RealSin{ sinf };
		const std::function<real(real)> RealCos{ cosf };
		const std::function<real(real)> RealExp{ expf };
	}
}