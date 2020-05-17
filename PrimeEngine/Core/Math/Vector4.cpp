#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"
#include <stdlib.h>
#include "../PrimeException.h"

namespace PrimeEngine
{
	namespace Math
	{
		Vector4::Vector4() 
			: Vector4(0.0f, 0.0f, 0.0f, 0.0f)
		{
		}

		Vector4::Vector4(float _x, float _y, float _z, float _w) 
			: x(_x), y(_y), z(_z), w(_w)
		{
		}

		Vector4::Vector4(const Vector2& vec2)
			: Vector4(vec2.x, vec2.y, 0.0f, 1.0f)
		{
		}

		Vector4::Vector4(const Vector3& vec3)
			: Vector4(vec3.x, vec3.y, vec3.z, 1.0f)
		{
		}

		const float Vector4::Dot(const Vector4& left, const Vector4& right)
		{
			return (left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w);
		}

		const Vector4 Vector4::Create(const char* string)
		{
			char* pEnd;
			float x, y, z, w;
			x = strtof(++string, &pEnd);
			y = strtof(++pEnd, &pEnd);
			z = strtof(++pEnd, &pEnd);
			w = strtof(++pEnd, NULL);
			return Vector4(x, y, z, w);
		}

		const Vector4 Vector4::operator+(const Vector4& right) const
		{
			Vector4 result(x + right.x, y + right.y, z + right.z, w + right.w);
			return result;
		}

		const Vector4 Vector4::operator-(const Vector4& right) const
		{
			Vector4 result(x - right.x, y - right.y, z - right.z, w + right.w);
			return result;
		}

		const Vector4 Vector4::operator*(const float scaler) const
		{
			Vector4 result(x * scaler, y * scaler, z * scaler, w * scaler);
			return result;
		}

		const Vector4 Vector4::operator/(const float scaler) const
		{
			Vector4 result(x / scaler, y / scaler, z / scaler, w * scaler);
			return result;
		}

		Vector4& Vector4::operator+=(const Vector4& right)
		{
			x += right.x;
			y += right.y;
			z += right.z;
			w += right.w;
			return *this;
		}

		Vector4& Vector4::operator-=(const Vector4& right)
		{
			x -= right.x;
			y -= right.y;
			z -= right.z;
			w -= right.w;
			return *this;
		}

		Vector4& Vector4::operator*=(const float scaler)
		{
			x *= scaler;
			y *= scaler;
			z *= scaler;
			w *= scaler;
			return *this;
		}

		Vector4& Vector4::operator/=(const float scaler)
		{
			x /= scaler;
			y /= scaler;
			z /= scaler;
			w /= scaler;
			return *this;
		}

		float& Vector4::operator[](unsigned int index)
		{
			return const_cast<float&>(static_cast<const Vector4&>(*this)[index]);
		}

		const float& Vector4::operator[](unsigned int index) const
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			default:
				PrimeException indexOutOfRange("Index out of range", -1);
				throw indexOutOfRange;;
			}
		}

		bool Vector4::operator!=(const Vector4& right) const
		{
			return !(*this == right);
		}

		bool Vector4::operator==(const Vector4& right) const
		{
			return (x == right.x && y == right.y && z == right.z);
		}
	}
}