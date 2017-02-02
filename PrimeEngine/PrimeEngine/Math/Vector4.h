#ifndef PRIMEENGINE_VECTOR4
#define PRIMEENGINE_VECTOR4

#include "..\DllExport.h"
#include <iostream>

namespace PrimeEngine { namespace Math {

	class PRIMEENGINEAPI Vector4
	{
	public:
		float x, y, z, w;

		static float Dot(const Vector4& left, const Vector4& right); //TEST

		Vector4();
		Vector4(float _x, float _y, float _z, float _w);

		float Magnitude() const; //TODO

		Vector4 operator+(const Vector4& right);
		Vector4 operator-(const Vector4& right);
		Vector4 operator*(const float scaler);
		Vector4 operator/(const float scaler);
		float& operator[](unsigned int index);
		//more operators
		bool operator!=(const Vector4& right) const;
		bool operator==(const Vector4& right) const;
		friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}
	};
}}

#endif // !PRIMEENGINE_VECTOR4

