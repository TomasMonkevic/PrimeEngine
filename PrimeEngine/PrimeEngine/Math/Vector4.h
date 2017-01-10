#ifndef PRIMEENGINE_VECTOR4
#define PRIMEENGINE_VECTOR4

#include "../DllExport.h"
#include <iostream>

namespace PrimeEngine
{
	namespace Math
	{
		//TODO: Derive from Vector4
		class PRIMEENGINEAPI Vector4
		{
		public:
			float x, y, z, w;

			Vector4();
			//destructos
			Vector4(float _x, float _y, float _z, float _w);
			Vector4 operator+(const Vector4& right);
			Vector4 operator-(const Vector4& right);
			Vector4 operator*(const float scaler);
			Vector4 operator/(const float scaler);

			//TODO: more operators

			bool operator!=(const Vector4& right) const;
			bool operator==(const Vector4& right) const;

			friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
			{
				stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
				return stream;
			}
		};
	}
}

#endif // !PRIMEENGINE_VECTOR4

