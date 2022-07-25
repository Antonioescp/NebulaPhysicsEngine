#pragma once

#include <IParticleForceGenerator.h>

namespace Nebula
{
	namespace ForceGenerators
	{
		class ParticleBuoyancy : public IParticleForceGenerator
		{
		private:

			real mMaxDepth{};
			real mVolume{};
			real mWaterHeight{};
			real mLiquidDensity{};

		public:

			ParticleBuoyancy(
				real maxDepth,
				real volume,
				real waterHeight,
				real liquidDensity
			);

			void UpdateForce(Particle& particle, real duration) override;

		};
	}
}