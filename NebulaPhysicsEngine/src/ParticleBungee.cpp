#include <ParticleBungee.h>

namespace Nebula
{
	inline namespace ForceGenerators
	{
		ParticleBungee::ParticleBungee(
			Core::Particle& particle,
			real stiffness,
			real restLength
		)
			: mOther{ particle }
			, mSpringStiffness{ stiffness }
			, mSpringRestLength{ restLength }
		{}

		void ParticleBungee::UpdateForce(Core::Particle& particle, real duration)
		{
			if (particle.IsStaticBody()) return;

			Core::Vector3 direction{ particle.GetPosition() - mOther.GetPosition() };
			real distance{ direction.GetMagnitude() };
			direction.Normalize();

			// Skip compression force 
			if (distance <= mSpringRestLength) return;

			Core::Vector3 force{ -mSpringStiffness * (distance - mSpringRestLength) * direction };
			particle.AddForce(force);
		}
	}
}