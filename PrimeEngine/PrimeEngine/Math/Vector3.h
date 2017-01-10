#ifndef PRIMEENGINE_VECTOR3
#define PRIMEENGINE_VECTOR3

#include "../DllExport.h"
#include <iostream>

namespace PrimeEngine
{
	namespace Math
	{
		//TODO: Derive from Vector4
		class PRIMEENGINEAPI Vector3
		{
		public:
			float x, y, z;

			Vector3();
			Vector3(float _x, float _y, float _z);
			Vector3 operator+(const Vector3& right);
			Vector3 operator-(const Vector3& right);
			Vector3 operator*(const float scaler);
			Vector3 operator/(const float scaler);

			//TODO: more operators

			bool operator!=(const Vector3& right) const;
			bool operator==(const Vector3& right) const;

			friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector)
			{
				stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
				return stream;
			}
		};
	}
}

#endif // !PRIMEENGINE_VECTOR3

