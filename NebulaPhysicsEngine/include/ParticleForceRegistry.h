#pragma once

#include <vector>

#include "Precision.h"
#include "Particle.h"
#include "Vector3.h"
#include "IParticleForceGenerator.h"

namespace Nebula
{
	namespace ForceGenerators
	{
		// Holds all particle generators and the particles they applied to
		class ParticleForceRegistry
		{
		protected:

			// Keeps track of the generator and the particle it applies to
			struct ParticleForceRegistration
			{
				Particle* particle;
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
			void Add(Particle& particle, IParticleForceGenerator& generator);

			// Removes a the pair from registry, if the pair is not registered it has no effect
			void Remove(Particle& particle, IParticleForceGenerator& generator);

			// Removes all records, it doesn't destroy the particles nor the generators, just
			// their relationship
			void Clear();

			// Calls update on every generator for every particle related to each generator
			void UpdateForces(real duration);
		};
	}
}
