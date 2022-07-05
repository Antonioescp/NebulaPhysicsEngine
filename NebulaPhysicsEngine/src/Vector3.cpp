module Core:Vector3;

using namespace std;
using namespace Nebula::Aliases;

namespace Nebula::Core
{
	void Vector3::makeOrthonormalBasis(Vector3& a, Vector3& b, Vector3& c)
	{
		a.normalize();
		c = a % b;
		if (c.getSquaredMagnitude() == 0.0) return;
		c.normalize();
		b = c % a;
	}

	Vector3::Vector3()
		: x{}, y{}, z{} {}

	Vector3::Vector3(const real x, const real y, const real z)
		: x{ x }, y{ y }, z{ z } { }

	Vector3::Vector3(const Vector3& source)
	{
		x = source.x;
		y = source.y;
		z = source.z;
	}

	void Vector3::invert()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	real Vector3::getMagnitude() const
	{
		return real_sqrt(x * x + y * y + z * z);
	}

	real Vector3::getSquaredMagnitude() const
	{
		return x * x + y * y + z * z;
	}

	Vector3& Vector3::normalize()
	{
		real mag = getMagnitude();
		if (mag > 0)
		{
			(*this) *= (static_cast<real>(1) / mag);
		}
		return *this;
	}

	Vector3 Vector3::getNormalized() const
	{
		return Vector3{ *this }.normalize();
	}

	void Vector3::addScaledVector(const Vector3& rhs, real scale)
	{
		x += rhs.x * scale;
		y += rhs.y * scale;
		z += rhs.z * scale;
	}

	Vector3 Vector3::operator+(const Vector3& rhs) const
	{
		return { x + rhs.x, y + rhs.y, z + rhs.z };
	}

	const Vector3& Vector3::operator+=(const Vector3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3 Vector3::operator-(const Vector3& rhs) const
	{
		return { x - rhs.x, y - rhs.y, z - rhs.z };
	}

	const Vector3& Vector3::operator-=(const Vector3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	const Vector3& Vector3::operator*=(const real scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vector3 Vector3::operator*(const real scalar) const
	{
		return { x * scalar, y * scalar, z * scalar };
	}

	const Vector3& Vector3::operator/=(const real scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	Vector3 Vector3::operator/(const real scalar) const
	{
		return { x / scalar, y / scalar, z / scalar };
	}

	Vector3 Vector3::getComponentProduct(const Vector3& rhs) const
	{
		return { x * rhs.x, y * rhs.y, z * rhs.z };
	}

	const Vector3& Vector3::assignComponentProduct(const Vector3& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	real Vector3::operator*(const Vector3& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}


	real Vector3::getDotProduct(const Vector3& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	Vector3 Vector3::operator%(const Vector3& rhs) const
	{
		return {
			y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x
		};
	}

	Vector3 Vector3::getCrossProduct(const Vector3& rhs) const
	{
		return {
			y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x
		};
	}

	const Vector3& Vector3::assignCrossProduct(const Vector3& rhs)
	{
		x = y * rhs.z - z * rhs.y;
		y = z * rhs.x - x * rhs.z;
		z = x * rhs.y - y * rhs.x;
		return *this;
	}

	Vector3 operator*(const real scalar, const Vector3& vector) {
		return vector * scalar;
	}

	std::ostream& operator<<(std::ostream& outputstream, const Vector3& v) {
		outputstream << "< " << v.x << ", " << v.y << ", " << v.z << " >";
		return outputstream;
	}
}
