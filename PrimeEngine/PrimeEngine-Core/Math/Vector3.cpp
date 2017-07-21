#include "Vector3.h"
#include "../PrimeException.h"
#include "Vector2.h"
#include "Vector4.h"
#include <stdlib.h>

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

		Vector3::Vector3(const Vector2& vec2)
			: Vector3(vec2.x, vec2.y, 0.0f)
		{

		}

		const Vector3 Vector3::Normalized() const
		{
			float length = Magnitude();
			Vector3 normalized = *this / length;
			return normalized;
		}

		const float Vector3::Dot(const Vector3& left, const Vector3& right)
		{
			return (left.x * right.x + left.y * right.y + left.z * right.z);
		}

		const Vector3 Vector3::Cross(const Vector3& left, const Vector3& right)
		{
			return Vector3(left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x);
		}

		const Vector3 Vector3::Create(const char* string)
		{
			char* pEnd;
			float x, y, z;
			x = strtof(++string, &pEnd);
			y = strtof(++pEnd, &pEnd);
			z = strtof(++pEnd, NULL);
			return Vector3(x, y, z);
		}

		const Vector3 Vector3::operator+(const Vector3& right) const
		{
			Vector3 result(x + right.x, y + right.y, z + right.z);
			return result;
		}

		const Vector3 Vector3::operator-(const Vector3& right) const
		{
			Vector3 result(x - right.x, y - right.y, z - right.z);
			return result;
		}

		const Vector3 Vector3::operator*(const float scaler) const
		{
			Vector3 result(x * scaler, y * scaler, z * scaler);
			return result;
		}

		const Vector3 Vector3::operator/(const float scaler) const
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
			return const_cast<float&>(static_cast<const Vector3&>(*this)[index]);
		}

		const float& Vector3::operator[](unsigned int index) const
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
				PrimeException indexOutOfRange("Index out of range", -1);
				throw indexOutOfRange;;
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