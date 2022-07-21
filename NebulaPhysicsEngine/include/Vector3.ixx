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
		const static Vector3 Gravity;
		const static Vector3 Right;
		const static Vector3 Up;

		real x;
		real y;
		real z;

		static void MakeOrthonormalBasis(Vector3& a, Vector3& b, Vector3& c);

		Vector3();
		Vector3(const real x, const real y, const real z);
		Vector3(const Vector3& source);

		void Invert();
		real GetMagnitude() const;
		real GetSquaredMagnitude() const;
		Vector3& Normalize();
		Vector3 GetNormalized() const;

		void AddScaledVector(const Vector3& rhs, real scale);

		Vector3 operator+(const Vector3& rhs) const;
		const Vector3& operator+=(const Vector3& rhs);

		Vector3 operator-(const Vector3& rhs) const;
		const Vector3& operator-=(const Vector3& rhs);

		Vector3 operator*(const real scalar) const;
		const Vector3& operator*=(const real scalar);

		Vector3 operator/(const real scalar) const;
		const Vector3& operator/=(const real scalar);

		Vector3 GetComponentProduct(const Vector3& rhs) const;
		const Vector3& AssignComponentProduct(const Vector3& rhs);

		real operator*(const Vector3& rhs) const;
		real GetDotProduct(const Vector3& rhs) const;

		Vector3 operator%(const Vector3& rhs) const;
		Vector3 GetCrossProduct(const Vector3& rhs) const;
		const Vector3& AssignCrossProduct(const Vector3& rhs);

		Vector3 operator-() const;
	};

	export Vector3 operator*(const real scalar, const Vector3& vector);
	export std::ostream& operator<<(std::ostream& outputstream, const Vector3& v);
}
