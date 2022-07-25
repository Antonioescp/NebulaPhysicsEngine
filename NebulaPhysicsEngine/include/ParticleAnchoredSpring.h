#pragma once

#include <IParticleForceGenerator.h>

namespace Nebula
{
	namespace ForceGenerators
	{
		class ParticleAnchoredSpring : public IParticleForceGenerator
		{
		protected:

			Vector3 mAnchor{};
			real mSpringStiffness{};
			real mSpringRestLenght{};

		public:

			ParticleAnchoredSpring(
				const Vector3& anchor,
				real stiffness,
				real restLength
			);

			void UpdateForce(Particle& particle, real duration) override;
		};
	}
}