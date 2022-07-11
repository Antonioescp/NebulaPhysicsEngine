#include <ParticleForceRegistry.h>

namespace Nebula::Core
{
	// Registers a generator with a particle
	void ParticleForceRegistry::Add(Nebula::Core::Particle& particle, IParticleForceGenerator& generator)
	{
		ParticleForceRegistration newRecord{
			.particle = &particle,
			.generator = &generator
		};
		mRegistry.push_back(newRecord);
	}

	// Removes a the pair from registry, if the pair is not registered it has no effect
	void ParticleForceRegistry::Remove(Nebula::Core::Particle& particle, IParticleForceGenerator& generator)
	{
		std::erase_if(mRegistry, [&particle, &generator](const ParticleForceRegistration& element) -> bool {
			return element.particle == &particle && element.generator == &generator;
		});
	}

	// Removes all records, it doesn't destroy the particles nor the generators, just
	// their relationship
	void ParticleForceRegistry::Clear()
	{
		mRegistry.clear();
	}

	// Calls update on every generator for every particle related to each generator
	void ParticleForceRegistry::UpdateForces(Nebula::Aliases::real duration)
	{
		for (auto& record : mRegistry)
		{
			record.generator->UpdateForce(*record.particle, duration);
		}
	}
}
