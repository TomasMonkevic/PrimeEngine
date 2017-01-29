#include "Vector4.h"

namespace PrimeEngine
{
	namespace Math
	{
		Vector4::Vector4() : Vector4(0, 0, 0, 0)
		{
		}

		Vector4::Vector4(float _x, float _y, float _z, float _w) :
			x(_x), y(_y), z(_z), w(_w)
		{
		}

		float Vector4::Magnitude() const
		{
			throw "Not implemented!";
		}

		float Vector4::Dot(const Vector4& left, const Vector4& right)
		{
			return (left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w);
		}

		Vector4 Vector4::operator+(const Vector4& right)
		{
			Vector4 result(x + right.x, y + right.y, z + right.z, w + right.w);
			return result;
		}

		Vector4 Vector4::operator-(const Vector4& right)
		{
			Vector4 result(x - right.x, y - right.y, z - right.z, w + right.w);
			return result;
		}

		Vector4 Vector4::operator*(const float scaler)
		{
			Vector4 result(x * scaler, y * scaler, z * scaler, w * scaler);
			return result;
		}

		Vector4 Vector4::operator/(const float scaler)
		{
			Vector4 result(x / scaler, y / scaler, z / scaler, w * scaler);
			return result;
		}

		float& Vector4::operator[](unsigned int index)
		{
			switch(index)
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
					throw "Index out of range";
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