#pragma once

#include <IParticleForceGenerator.h>

namespace Nebula
{
	inline namespace ForceGenerators
	{
		class ParticleBungee : public Core::IParticleForceGenerator
		{
		private:

			Core::Particle& mOther;
			real mSpringStiffness{};
			real mSpringRestLength{};

		public:

			ParticleBungee(
				Core::Particle& particle,
				real stiffness,
				real restLength
			);

			void UpdateForce(Core::Particle& particle, real duration) override;

		};
	}
}