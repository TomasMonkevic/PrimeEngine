#include "Vector2.h"

namespace PrimeEngine
{
	namespace Math
	{
		Vector2::Vector2() : Vector2(0, 0)
		{
		}

		Vector2::Vector2(float _x, float _y) :
			x(_x), y(_y)
		{
		}

		float Vector2::Magnitude() const
		{
			throw "Not implemented!";
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

		float& Vector2::operator[](unsigned int index)
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			default:
				throw "Index out of range";
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