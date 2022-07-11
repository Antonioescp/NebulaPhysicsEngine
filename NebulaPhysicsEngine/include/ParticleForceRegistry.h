#pragma once

#include "IParticleForceGenerator.h"
#include <vector>

import Core;

namespace Nebula::Core
{
	// Holds all particle generators and the particles they applied to
	class ParticleForceRegistry
	{
	protected:

		// Keeps track of the generator and the particle it applies to
		struct ParticleForceRegistration
		{
			Nebula::Core::Particle* particle;
			IParticleForceGenerator* generator;

			bool operator==(const ParticleForceRegistration& rhs)
			{
				return particle == rhs.particle && generator == rhs.generator;
			}
		};

		// Holds the registrations
		std::vector<ParticleForceRegistration> mRegistry;

	public:

		// Registers a generator with a particle
		void Add(Nebula::Core::Particle& particle, IParticleForceGenerator& generator);

		// Removes a the pair from registry, if the pair is not registered it has no effect
		void Remove(Nebula::Core::Particle& particle, IParticleForceGenerator& generator);

		// Removes all records, it doesn't destroy the particles nor the generators, just
		// their relationship
		void Clear();

		// Calls update on every generator for every particle related to each generator
		void UpdateForces(Nebula::Aliases::real duration);
	};
}
