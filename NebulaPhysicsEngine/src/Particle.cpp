module Core:Particle;

using namespace std;
using namespace Nebula::Aliases;

namespace Nebula::Core
{
	void Particle::ClearAccumulator()
	{
		mForceAccumulator.x = 0.0f;
		mForceAccumulator.y = 0.0f;
		mForceAccumulator.z = 0.0f;
	}

	void Particle::SetPosition(real x, real y, real z)
	{
		mPosition.x = x;
		mPosition.y = y;
		mPosition.z = z;
	}

	void Particle::SetPosition(const Vector3& newPosition)
	{
		mPosition = newPosition;
	}

	Vector3 Particle::GetPosition() const
	{
		return mPosition;
	}

	void Particle::SetVelocity(real x, real y, real z)
	{
		mVelocity.x = x;
		mVelocity.y = y;
		mVelocity.z = z;
	}

	void Particle::SetVelocity(const Vector3& newVelocity)
	{
		mVelocity = newVelocity;
	}

	Vector3 Particle::GetVelocity() const
	{
		return mVelocity;
	}

	void Particle::SetAcceleration(real x, real y, real z)
	{
		mAcceleration.x = x;
		mAcceleration.y = y;
		mAcceleration.z = z;
	}

	void Particle::SetAcceleration(const Vector3& newAcceleration)
	{
		mAcceleration = newAcceleration;
	}

	Vector3 Particle::GetAcceleration() const
	{
		return mAcceleration + mForceAccumulator * mInverseMass;
	}

	void Particle::SetDamping(real newDamping)
	{
		mDamping = (newDamping >= 0) ? newDamping : static_cast<real>(0.0);
	}

	real Particle::GetDamping() const
	{
		return mDamping;
	}

	real Particle::GetMass() const 
	{
		return static_cast<real>(1.0) / mInverseMass;
	}

	void Particle::SetMass(real newMass) 
	{
		mInverseMass = static_cast<real>(1.0) / newMass;
	}

	void Particle::SetInverseMass(real newInverseMass)
	{
		mInverseMass = newInverseMass;
	}

	real Particle::GetInverseMass() const
	{
		return mInverseMass;
	}

	void Particle::Integrate(real duration)
	{
		if (mInverseMass <= 0.0) return;

		if (duration <= 0.0)
		{
			throw invalid_argument{ "duration can't be less or equal to zero" };
		}
		
		mPosition.AddScaledVector(mVelocity, duration);
		
		Vector3 resultingAcceleration = mAcceleration;
		resultingAcceleration.AddScaledVector(mForceAccumulator, mInverseMass);

		mVelocity.AddScaledVector(resultingAcceleration, duration);
		mVelocity *= RealPow(mDamping, duration);

		ClearAccumulator();
	}

	real Particle::GetKineticEnergy() const
	{
		return GetMass() / 2 * mVelocity.GetSquaredMagnitude();
	}

	void Particle::AddForce(const Vector3& force)
	{
		mForceAccumulator += force;
	}

	bool Particle::IsStaticBody() const
	{
		return mInverseMass == 0.0f;
	}
}