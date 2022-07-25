#pragma once

#include "Precision.h"
#include "Vector3.h"
#include "IParticleForceGenerator.h"

namespace Nebula
{
	namespace ForceGenerators
	{
		class ParticleGravity : public IParticleForceGenerator
		{
		private:
			// Holds the acceleration due to gravity
			Vector3 mGravity;

		public:

			ParticleGravity(const Vector3& gravity);
			virtual void UpdateForce(Particle& particle, real duration);

		};
	}
}
