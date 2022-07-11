#pragma once

#include "IParticleForceGenerator.h"

import Core;

namespace Nebula::Core
{
	class ParticleGravity : public IParticleForceGenerator
	{
	private:
		// Holds the acceleration due to gravity
		Vector3 mGravity;
	
	public:
		
		ParticleGravity(const Vector3& gravity);
		virtual void UpdateForce(Particle& particle, real duration);
	};
}
