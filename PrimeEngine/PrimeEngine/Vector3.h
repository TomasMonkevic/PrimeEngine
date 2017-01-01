#ifndef PRIMEENGINE_VECTOR3
#define PRIMEENGINE_VECTOR3

#include "DllExport.h"

namespace PrimeEngine
{
	namespace Math
	{
		class PRIMEENGINEAPI Vector3
		{
		public:
			float x, y, z;
			Vector3();
			Vector3(float _x, float _y, float _z);
			Vector3 operator+(const Vector3& right);
			Vector3 operator-(const Vector3& right);
			Vector3 operator*(float scaler);
			Vector3 operator/(float scaler);
			bool operator!=(const Vector3& right);
			bool operator==(const Vector3& right);
		};
	}
}

#endif // !PRIMEENGINE_VECTOR3

