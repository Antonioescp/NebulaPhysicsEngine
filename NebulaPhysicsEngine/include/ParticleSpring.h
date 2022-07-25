#pragma once

#include "IParticleForceGenerator.h"


namespace Nebula
{
	namespace ForceGenerators
	{
		class ParticleSpring : public IParticleForceGenerator
		{
		private:

			// One spring end
			Particle& mParticle;

			// How robust the spring is, higher means stronger force for extension and compression
			real mStiffness{};

			// the length at which the spring does not exert any force
			real mRestLength{};

		public:

			ParticleSpring(Particle& particle, real stiffness, real restLength);
			void UpdateForce(Particle& particle, real duration) override;
		};
	}
}
