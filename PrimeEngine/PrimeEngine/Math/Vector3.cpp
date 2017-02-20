#include "Vector3.h"
#include <stdlib.h>

namespace PrimeEngine
{
	namespace Math
	{
		const Vector3 Vector3::one = Vector3(1, 1, 1);
		const Vector3 Vector3::zero = Vector3();
		const Vector3 Vector3::back = Vector3(0, 0, -1);
		const Vector3 Vector3::down = Vector3(0, -1, 0);
		const Vector3 Vector3::left = Vector3(-1, 0, 0);
		const Vector3 Vector3::forward = Vector3(0, 0, 1);
		const Vector3 Vector3::up = Vector3(0, 1, 0);
		const Vector3 Vector3::right = Vector3(1, 0, 0);

		Vector3::Vector3() : Vector3(0, 0, 0)
		{
		}

		Vector3::Vector3(float _x, float _y, float _z) : 
			x(_x), y(_y), z(_z)
		{
		}

		float Vector3::Magnitude() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		float Vector3::SqrMagnitude() const
		{
			return x * x + y * y + z * z;
		}

		Vector3 Vector3::Normalized() const
		{
			float length = Magnitude();
			Vector3 normalized = *this / length;
			return normalized;
		}

		float Vector3::Dot(const Vector3& left, const Vector3& right)
		{
			return (left.x * right.x + left.y * right.y + left.z * right.z);
		}

		Vector3 Vector3::Cross(const Vector3& left, const Vector3& right)
		{
			return Vector3(left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x);
		}

		Vector3 Vector3::Create(const char* string)
		{
			char* pEnd;
			float x, y, z;
			x = strtof(++string, &pEnd);
			y = strtof(++pEnd, &pEnd);
			z = strtof(++pEnd, NULL);
			return Vector3(x, y, z);
		}

		Vector3 Vector3::operator+(const Vector3& right) const
		{
			Vector3 result(x + right.x, y + right.y, z + right.z);
			return result;
		}

		Vector3 Vector3::operator-(const Vector3& right) const
		{
			Vector3 result(x - right.x, y - right.y, z - right.z);
			return result;
		}

		Vector3 Vector3::operator*(const float scaler) const
		{
			Vector3 result(x * scaler, y * scaler, z * scaler);
			return result;
		}

		Vector3 Vector3::operator/(const float scaler) const 
		{
			Vector3 result(x / scaler, y / scaler, z / scaler);
			return result;
		}

		Vector3& Vector3::operator+=(const Vector3& right)
		{
			x += right.x;
			y += right.y;
			z += right.z;
			return *this;
		}

		Vector3& Vector3::operator-=(const Vector3& right)
		{
			x -= right.x;
			y -= right.y;
			z -= right.z;
			return *this;
		}

		Vector3& Vector3::operator*=(const float scaler)
		{
			x *= scaler;
			y *= scaler;
			z *= scaler;
			return *this;
		}

		Vector3& Vector3::operator/=(const float scaler)
		{
			x /= scaler;
			y /= scaler;
			z /= scaler;
			return *this;
		}

		float& Vector3::operator[](unsigned int index)
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			default:
				throw "Index out of range";
			}
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