#include <ParticleSpring.h>

namespace Nebula
{
	namespace ForceGenerators
	{
		ParticleSpring::ParticleSpring(Nebula::Core::Particle& particle, Nebula::real stiffness, Nebula::real restLength)
			: mParticle{ particle }
			, mStiffness{ stiffness }
			, mRestLength{ restLength }
		{}

		void ParticleSpring::UpdateForce(Nebula::Core::Particle& particle, Nebula::real duration)
		{
			if (particle.IsStaticBody()) return;

			/*Nebula::Core::Vector3 force{};
			force = particle.GetPosition();
			force -= mParticle.GetPosition();

			Nebula::real magnitude{ force.GetMagnitude() };
			magnitude = Nebula::RealAbs(magnitude - mRestLength);
			magnitude *= mStiffness;

			force.Normalize();
			force *= -magnitude;
			particle.AddForce(force);*/

			Nebula::Core::Vector3 force{ particle.GetPosition() - mParticle.GetPosition() };
			Nebula::real magnitude{ -mStiffness * (force.GetMagnitude() - mRestLength) };
			force.Normalize();
			force *= magnitude;

			particle.AddForce(force);
		}
	}
}
