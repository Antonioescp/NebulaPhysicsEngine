#include <ParticleBungee.h>

namespace Nebula
{
	namespace ForceGenerators
	{
		ParticleBungee::ParticleBungee(
			Particle& particle,
			real stiffness,
			real restLength
		)
			: mOther{ particle }
			, mSpringStiffness{ stiffness }
			, mSpringRestLength{ restLength }
		{}

		void ParticleBungee::UpdateForce(Particle& particle, real duration)
		{
			if (particle.IsStaticBody()) return;

			Vector3 direction{ particle.GetPosition() - mOther.GetPosition() };
			real distance{ direction.GetMagnitude() };
			direction.Normalize();

			// Skip compression force 
			if (distance <= mSpringRestLength) return;

			Vector3 force{ -mSpringStiffness * (distance - mSpringRestLength) * direction };
			particle.AddForce(force);
		}
	}
}