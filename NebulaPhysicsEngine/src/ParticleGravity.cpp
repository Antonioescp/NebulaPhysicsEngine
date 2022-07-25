#include <ParticleGravity.h>

namespace Nebula
{
	namespace ForceGenerators
	{
		ParticleGravity::ParticleGravity(const Vector3& gravity)
			: mGravity{ gravity }
		{}

		void ParticleGravity::UpdateForce(Particle& particle, real duration)
		{
			// Dont do processing in static bodies
			if (particle.IsStaticBody()) return;

			// Apply the mass-scaled force to the particle
			particle.AddForce(mGravity * particle.GetMass());

		}
	}
}
