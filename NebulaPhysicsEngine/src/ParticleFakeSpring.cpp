#include "ParticleFakeSpring.h"

namespace Nebula
{
	namespace ForceGenerators
	{
		ParticleFakeSpring::ParticleFakeSpring(const Vector3& anchor, real stiffness, real damping)
			: mAnchor{ anchor }
			, mSpringStiffness{ stiffness }
			, mDamping{ damping }
		{}

		void ParticleFakeSpring::UpdateForce(Particle& particle, real duration)
		{
			if (particle.IsStaticBody()) return;

			Vector3 position{ particle.GetPosition() };
			position -= mAnchor;

			real gamma{ 0.5f * RealSqrt(4.0f * mSpringStiffness - mDamping * mDamping) };
			if (gamma == 0.0f) return;

			Vector3 c{ position * (mDamping / (2.0f * gamma)) + particle.GetVelocity() * (1.0f / gamma) };

			Vector3 target{ position * RealCos(gamma * duration) + c * RealSin(gamma * duration) };
			target *= RealExp(-0.5f * duration * mDamping);

			Vector3 acceleration{ (target - position) * (1.0f / duration * duration) - particle.GetVelocity() * duration };
			particle.AddForce(acceleration * particle.GetMass());
		}

		void ParticleFakeSpring::SetAnchor(const Core::Vector3& anchor)
		{
			mAnchor = anchor;
		}

	}
}