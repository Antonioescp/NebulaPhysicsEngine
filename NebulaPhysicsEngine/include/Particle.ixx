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
		Vector3 mPosition{};
		Vector3 mVelocity{};
		Vector3 mAcceleration{};
		real mDamping{};
		real mInverseMass{};

	public:

		void SetPosition(real x, real y, real z);
		void SetPosition(const Vector3& newPosition);
		Vector3 GetPosition() const;

		void SetVelocity(real x, real y, real z);
		void SetVelocity(const Vector3& newPosition);
		Vector3 GetVelocity() const;

		void SetAcceleration(real x, real y, real z);
		void SetAcceleration(const Vector3& newPosition);
		Vector3 GetAcceleration() const;

		void SetDamping(real newDamping);
		real GetDamping() const;

		void SetMass(real newMass);
		real GetMass() const;
		void SetInverseMass(real newInverseMass);
		real GetInverseMass() const;

		void Integrate(real duration);

		real GetKineticEnergy() const;
	};
}
