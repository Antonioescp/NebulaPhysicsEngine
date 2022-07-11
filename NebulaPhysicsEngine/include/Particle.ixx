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

		// This helps to simulate any kind of friction, a value in range (1.00f, 0.00f) should be used
		real mDamping{};

		// This helps to identify wether the object is static or not, setting this to 0 is equal to setting the particle
		// to infinite mass so it can't be moved
		real mInverseMass{};

		// This holds the sum of all forces applied to the object and is set to zero after every integration step
		// since the forces need to be processed at the moment they are applied to the object
		Vector3 mForceAccumulator{};

		// This clears the force accumulator, sets it to zero
		void ClearAccumulator();

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

		void AddForce(const Vector3& force);

		bool IsStaticBody() const;
	};
}
