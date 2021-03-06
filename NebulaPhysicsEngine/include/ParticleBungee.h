#pragma once

#include "Precision.h"
#include "Vector3.h"
#include "Particle.h"
#include <IParticleForceGenerator.h>

namespace Nebula
{
	namespace ForceGenerators
	{
		class ParticleBungee : public IParticleForceGenerator
		{
		private:

			Particle& mOther;
			real mSpringStiffness{};
			real mSpringRestLength{};

		public:

			ParticleBungee(
				Particle& particle,
				real stiffness,
				real restLength
			);

			void UpdateForce(Particle& particle, real duration) override;

		};
	}
}