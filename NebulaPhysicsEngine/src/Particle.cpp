module Core:Particle;

using namespace std;
using namespace Nebula::Aliases;

namespace Nebula::Core
{
	void Particle::setPosition(real x, real y, real z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}

	void Particle::setPosition(const Vector3& newPosition)
	{
		position = newPosition;
	}

	Vector3 Particle::getPosition() const
	{
		return position;
	}

	void Particle::setVelocity(real x, real y, real z)
	{
		velocity.x = x;
		velocity.y = y;
		velocity.z = z;
	}

	void Particle::setVelocity(const Vector3& newVelocity)
	{
		velocity = newVelocity;
	}

	Vector3 Particle::getVelocity() const
	{
		return velocity;
	}

	void Particle::setAcceleration(real x, real y, real z)
	{
		acceleration.x = x;
		acceleration.y = y;
		acceleration.z = z;
	}

	void Particle::setAcceleration(const Vector3& newAcceleration)
	{
		acceleration = newAcceleration;
	}

	Vector3 Particle::getAcceleration() const
	{
		return acceleration;
	}

	void Particle::setDamping(real newDamping)
	{
		damping = (newDamping >= 0) ? newDamping : static_cast<real>(0.0);
	}

	real Particle::getDamping() const
	{
		return damping;
	}

	real Particle::getMass() const 
	{
		return static_cast<real>(1.0) / inverseMass;
	}

	void Particle::setMass(real newMass) 
	{
		inverseMass = static_cast<real>(1.0) / newMass;
	}

	void Particle::setInverseMass(real newInverseMass)
	{
		inverseMass = newInverseMass;
	}

	real Particle::getInverseMass() const
	{
		return inverseMass;
	}

	void Particle::integrate(real duration)
	{
		if (inverseMass <= 0.0) return;

		if (duration <= 0.0)
		{
			throw invalid_argument{ "duration can't be less or equal to zero" };
		}
		
		position.addScaledVector(velocity, duration);
		
		Vector3 resultingAcceleration = acceleration;

		velocity.addScaledVector(resultingAcceleration, duration);
		velocity *= real_pow(damping, duration);
	}

	real Particle::getKineticEnergy() const
	{
		return getMass() / 2 * velocity.getSquaredMagnitude();
	}
}