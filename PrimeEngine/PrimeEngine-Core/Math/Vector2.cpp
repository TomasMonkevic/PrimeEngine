#include "Vector2.h"
#include "../PrimeException.h"

namespace PrimeEngine
{
	namespace Math
	{
		const Vector2 Vector2::one = Vector2(1, 1);
		const Vector2 Vector2::zero = Vector2();
		const Vector2 Vector2::down = Vector2(0, -1);
		const Vector2 Vector2::left = Vector2(-1, 0);;
		const Vector2 Vector2::up = Vector2(0, 1);
		const Vector2 Vector2::right = Vector2(1, 0);

		Vector2::Vector2() : Vector2(0, 0)
		{
		}

		Vector2::Vector2(float _x, float _y) :
			x(_x), y(_y)
		{
		}

		float Vector2::Magnitude() const
		{
			PrimeException indexOutOfRange("Not impelemnted", -1);
			throw indexOutOfRange;;
		}

		float Vector2::Dot(const Vector2& left, const Vector2& right)
		{
			return (left.x * right.x + left.y * right.y);
		}

		Vector2 Vector2::operator+(const Vector2& right)
		{
			Vector2 result(x + right.x, y + right.y);
			return result;
		}

		Vector2 Vector2::operator-(const Vector2& right)
		{
			Vector2 result(x - right.x, y - right.y);
			return result;
		}

		Vector2 Vector2::operator*(const float scaler)
		{
			Vector2 result(x * scaler, y * scaler);
			return result;
		}

		Vector2 Vector2::operator/(const float scaler)
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