#include "Vector2.h"
#include "../PrimeException.h"

namespace PrimeEngine
{
	namespace Math
	{
		Vector2::Vector2() : Vector2(0.0f, 0.0f)
		{
		}

		Vector2::Vector2(float _x, float _y) :
			x(_x), y(_y)
		{
		}

		const float Vector2::Dot(const Vector2& left, const Vector2& right)
		{
			return (left.x * right.x + left.y * right.y);
		}

		const Vector2 Vector2::operator+(const Vector2& right) const
		{
			Vector2 result(x + right.x, y + right.y);
			return result;
		}

		const Vector2 Vector2::operator-(const Vector2& right) const
		{
			Vector2 result(x - right.x, y - right.y);
			return result;
		}

		const Vector2 Vector2::operator*(const float scaler) const
		{
			Vector2 result(x * scaler, y * scaler);
			return result;
		}

		const Vector2 Vector2::operator/(const float scaler) const
		{
			Vector2 result(x / scaler, y / scaler);
			return result;
		}

		Vector2& Vector2::operator+=(const Vector2& right)
		{
			x += right.x;
			y += right.y;
			return *this;
		}

		Vector2& Vector2::operator-=(const Vector2& right)
		{
			x -= right.x;
			y -= right.y;
			return *this;
		}

		Vector2& Vector2::operator*=(const float scaler)
		{
			x *= scaler;
			y *= scaler;
			return *this;
		}

		Vector2& Vector2::operator/=(const float scaler)
		{
			x /= scaler;
			y /= scaler;
			return *this;
		}

		float& Vector2::operator[](unsigned int index)
		{
			return const_cast<float&>(static_cast<const Vector2&>(*this)[index]);
		}

		const float& Vector2::operator[](unsigned int index) const
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			default:
				PrimeException indexOutOfRange("Index out of range", -1);
				throw indexOutOfRange;;
			}
		}

		bool Vector2::operator!=(const Vector2& right) const
		{
			return !(*this == right);
		}

		bool Vector2::operator==(const Vector2& right) const
		{
			return (x == right.x && y == right.y);
		}
	}
}