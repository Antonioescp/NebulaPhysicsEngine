#pragma once

#include "IParticleForceGenerator.h"

import Core;

namespace Nebula
{
	inline namespace ForceGenerators
	{
		class ParticleSpring : public Nebula::Core::IParticleForceGenerator
		{
		private:
			
			// One spring end
			Nebula::Core::Particle& mParticle;

			// How robust the spring is, higher means stronger force for extension and compression
			Nebula::real mStiffness{};

			// the length at which the spring does not exert any force
			Nebula::real mRestLength{};

		public:

			ParticleSpring(Nebula::Core::Particle& particle, Nebula::real stiffness, Nebula::real restLength);
			void UpdateForce(Nebula::Core::Particle& particle, Nebula::real duration) override;
		};
	}
}
