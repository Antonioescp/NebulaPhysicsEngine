export module Core:Vector3;

import :Precision;
import std.core;

using namespace std;
using namespace Nebula::Aliases;

namespace Nebula::Core
{
	export class Vector3
	{
	public:
		static Vector3 Gravity;

		real x;
		real y;
		real z;

		static void makeOrthonormalBasis(Vector3& a, Vector3& b, Vector3& c);

		Vector3();
		Vector3(const real x, const real y, const real z);
		Vector3(const Vector3& source);

		void invert();
		real getMagnitude() const;
		real getSquaredMagnitude() const;
		Vector3& normalize();
		Vector3 getNormalized() const;

		void addScaledVector(const Vector3& rhs, real scale);

		Vector3 operator+(const Vector3& rhs) const;
		const Vector3& operator+=(const Vector3& rhs);

		Vector3 operator-(const Vector3& rhs) const;
		const Vector3& operator-=(const Vector3& rhs);

		Vector3 operator*(const real scalar) const;
		const Vector3& operator*=(const real scalar);

		Vector3 operator/(const real scalar) const;
		const Vector3& operator/=(const real scalar);

		Vector3 getComponentProduct(const Vector3& rhs) const;
		const Vector3& assignComponentProduct(const Vector3& rhs);

		real operator*(const Vector3& rhs) const;
		real getDotProduct(const Vector3& rhs) const;

		Vector3 operator%(const Vector3& rhs) const;
		Vector3 getCrossProduct(const Vector3& rhs) const;
		const Vector3& assignCrossProduct(const Vector3& rhs);
	};

	export Vector3 operator*(const real scalar, const Vector3& vector);
	export std::ostream& operator<<(std::ostream& outputstream, const Vector3& v);
}
