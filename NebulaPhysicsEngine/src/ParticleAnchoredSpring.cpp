#include <ParticleAnchoredSpring.h>

namespace Nebula
{
	inline namespace ForceGenerators
	{
		ParticleAnchoredSpring::ParticleAnchoredSpring(
			const Core::Vector3& anchor,
			real stiffness,
			real restLength
		)
			: mAnchor{ anchor }
			, mSpringStiffness{ stiffness }
			, mSpringRestLenght{ restLength }
		{}

		void ParticleAnchoredSpring::UpdateForce(Core::Particle& particle, Nebula::real duration)
		{
			Core::Vector3 direction{ particle.GetPosition() - mAnchor };
			real distance{ direction.GetMagnitude() };
			direction.Normalize();

			Core::Vector3 force{ -mSpringStiffness * (distance - mSpringRestLenght) * direction };

			particle.AddForce(force);
		}
	}
}