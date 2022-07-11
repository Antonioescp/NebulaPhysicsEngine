#pragma once

#include "IParticleForceGenerator.h"

import Core;

namespace Nebula::Core
{
	class ParticleDrag : public IParticleForceGenerator
	{
	private:
		// Holds the velocity drag coefficient
		real mK1;

		// Holds the velocity squared drag coefficient
		real mK2;

	public:

		// Creates the generator with the given coefficients
		ParticleDrag(real k1, real k2);

		// Applies the drag force to the given particle
		virtual void UpdateForce(Particle& particle, real duration);
	};
}
