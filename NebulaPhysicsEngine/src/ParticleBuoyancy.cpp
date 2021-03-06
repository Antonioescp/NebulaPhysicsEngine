#include <ParticleBuoyancy.h>

namespace Nebula
{
	namespace ForceGenerators
	{
		ParticleBuoyancy::ParticleBuoyancy(
			real maxDepth,
			real volume,
			real waterHeight,
			real liquidDensity
		)
			: mMaxDepth{ maxDepth }
			, mVolume{ volume }
			, mWaterHeight{ waterHeight }
			, mLiquidDensity{ liquidDensity }
		{}

		void ParticleBuoyancy::UpdateForce(Particle& particle, real duration)
		{
			if (particle.IsStaticBody()) return;

			real depth{ particle.GetPosition().y };

			if (depth >= mWaterHeight + mMaxDepth) return;

			Vector3 force{};

			if (depth <= mWaterHeight - mMaxDepth)
			{
				force.y = mLiquidDensity * mVolume;
				particle.AddForce(force);
				return;
			}

			force.y = mLiquidDensity * mVolume * (depth - mMaxDepth - mWaterHeight) / 2.0f * mMaxDepth;
			particle.AddForce(force);
		}

	}
}