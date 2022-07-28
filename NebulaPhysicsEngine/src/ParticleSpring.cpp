#include <ParticleSpring.h>

#include <iostream>

namespace Nebula
{
	namespace ForceGenerators
	{
		ParticleSpring::ParticleSpring(Particle& particle, real stiffness, real restLength)
			: mParticle{ particle }
			, mStiffness{ stiffness }
			, mRestLength{ restLength }
		{}

		void ParticleSpring::UpdateForce(Particle& particle, real duration)
		{
			if (particle.IsStaticBody()) return;
			// Calculating direction
			Vector3 force{ particle.GetPosition() - mParticle.GetPosition() };
			real distance{ force.GetMagnitude() };
			force.Normalize();

			// Getting force magnitude
			real magnitude{ mStiffness * (mRestLength - distance) };
			
			// Getting force and applying it
			force *= magnitude;
			particle.AddForce(force);
		}
	}
}
