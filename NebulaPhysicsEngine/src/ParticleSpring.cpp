#include <ParticleSpring.h>

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

			Vector3 force{ particle.GetPosition() - mParticle.GetPosition() };
			real distance{ force.GetMagnitude() };
			force.Normalize();

			force *= mStiffness * (mRestLength - distance);
			particle.AddForce(force);
		}
	}
}
