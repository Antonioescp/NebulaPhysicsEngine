export module Core:Particle;

import :Precision;
import :Vector3;
import std.core;

using namespace std;
using namespace Nebula::Aliases;

namespace Nebula::Core
{
	export class Particle {
	protected:
		Vector3 position{};
		Vector3 velocity{};
		Vector3 acceleration{};
		real damping{};
		real inverseMass{};

	public:

		void setPosition(real x, real y, real z);
		void setPosition(const Vector3& newPosition);
		Vector3 getPosition() const;

		void setVelocity(real x, real y, real z);
		void setVelocity(const Vector3& newPosition);
		Vector3 getVelocity() const;

		void setAcceleration(real x, real y, real z);
		void setAcceleration(const Vector3& newPosition);
		Vector3 getAcceleration() const;

		void setDamping(real newDamping);
		real getDamping() const;

		void setMass(real newMass);
		real getMass() const;
		void setInverseMass(real newInverseMass);
		real getInverseMass() const;

		void integrate(real duration);

		real getKineticEnergy() const;
	};
}
