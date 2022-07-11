#include <ParticleDrag.h>

namespace Nebula::Core
{
	ParticleDrag::ParticleDrag(real k1, real k2)
		: mK1{ k1 }
		, mK2{ k2 }
	{
	}

	void ParticleDrag::UpdateForce(Particle& particle, real duration)
	{
		Vector3 force{ particle.GetVelocity() };

		real dragCoefficient = force.GetMagnitude();
		dragCoefficient = mK1 * dragCoefficient + mK2 * dragCoefficient * dragCoefficient;

		force.Normalize();
		force *= -dragCoefficient;

		particle.AddForce(force);
	}
}
