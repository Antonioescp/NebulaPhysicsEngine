#pragma once

#include <IParticleForceGenerator.h>

namespace Nebula
{
	inline namespace ForceGenerators
	{
		class ParticleAnchoredSpring : public Core::IParticleForceGenerator
		{
		protected:

			Core::Vector3 mAnchor{};
			real mSpringStiffness{};
			real mSpringRestLenght{};

		public:

			ParticleAnchoredSpring(
				const Core::Vector3& anchor,
				real stiffness,
				real restLength
			);

			void UpdateForce(Core::Particle& particle, real duration) override;
		};
	}
}