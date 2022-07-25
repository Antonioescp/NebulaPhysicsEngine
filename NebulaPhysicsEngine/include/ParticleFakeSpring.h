#pragma once

#include "Precision.h"
#include "Vector3.h"
#include "Particle.h"
#include "IParticleForceGenerator.h"

namespace Nebula
{
	namespace ForceGenerators
	{
		class ParticleFakeSpring : public IParticleForceGenerator
		{
		private:

			Vector3 mAnchor{};
			real mSpringStiffness{};
			real mDamping{};

		public:

			ParticleFakeSpring(
				const Vector3& anchor,
				real stiffness,
				real damping
			);

			void UpdateForce(Particle& particle, real duration) override;
			void SetAnchor(const Vector3& anchor);

		};
	}
}