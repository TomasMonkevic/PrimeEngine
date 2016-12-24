#include "Vector3.h"

namespace PrimeEngine
{
	namespace Math
	{
		Vector3::Vector3() : Vector3(0.0f, 0.0f, 0.0f)
		{
		}

		Vector3::Vector3(float _x, float _y, float _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		Vector3 Vector3::operator+(const Vector3& right)
		{
			Vector3 result(x + right.x, y + right.y, z + right.z);
			return result;
		}
	}
}