#include <ParticleAnchoredSpring.h>

namespace Nebula
{
	namespace ForceGenerators
	{
		ParticleAnchoredSpring::ParticleAnchoredSpring(
			const Vector3& anchor,
			real stiffness,
			real restLength
		)
			: mAnchor{ anchor }
			, mSpringStiffness{ stiffness }
			, mSpringRestLenght{ restLength }
		{}

		void ParticleAnchoredSpring::UpdateForce(Particle& particle, real duration)
		{
			Vector3 direction{ particle.GetPosition() - mAnchor };
			real distance{ direction.GetMagnitude() };
			direction.Normalize();

			Vector3 force{ -mSpringStiffness * (distance - mSpringRestLenght) * direction };

			particle.AddForce(force);
		}
	}
}