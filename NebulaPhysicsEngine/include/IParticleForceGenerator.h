#pragma once

import Core;

namespace Nebula::Core 
{
	// An interface to create a force generator, this helps to handle different types of forces,
	// constant forces, forces that change over time, etc... to be applied to a particle
	class IParticleForceGenerator
	{
	public:

		// Updates the force in the particle, some forces may need a duration to be properly updated
		virtual void UpdateForce(Nebula::Core::Particle& particle, Nebula::Aliases::real duration) = 0;
	};
}
