#include "Vector3.h"

namespace PrimeEngine
{
	namespace Math
	{
		Vector3::Vector3() : Vector3(0, 0, 0)
		{
		}

		Vector3::Vector3(float _x, float _y, float _z) : 
			x(_x), y(_y), z(_z)
		{
		}

		Vector3 Vector3::operator+(const Vector3& right)
		{
			Vector3 result(x + right.x, y + right.y, z + right.z);
			return result;
		}

		Vector3 Vector3::operator-(const Vector3& right)
		{
			Vector3 result(x - right.x, y - right.y, z - right.z);
			return result;
		}

		Vector3 Vector3::operator*(const float scaler)
		{
			Vector3 result(x * scaler, y * scaler, z * scaler);
			return result;
		}

		Vector3 Vector3::operator/(const float scaler)
		{
			Vector3 result(x / scaler, y / scaler, z / scaler);
			return result;
		}

		bool Vector3::operator!=(const Vector3& right) const
		{
			return !(*this == right);
		}

		bool Vector3::operator==(const Vector3& right) const
		{
			return (x == right.x && y == right.y && z == right.z);
		}
	}
}