#ifndef PRIMEENGINE_VECTOR3
#define PRIMEENGINE_VECTOR3

#include "..\DllExport.h"
#include "MathFunc.h"
#include <iostream>

namespace PrimeEngine {	namespace Math {

	class PRIMEENGINEAPI Vector3
	{
	public:
		float x, y, z;

		static const Vector3 one;
		static const Vector3 zero;
		static const Vector3 back;
		static const Vector3 down;
		static const Vector3 left;
		static const Vector3 forward;
		static const Vector3 up;
		static const Vector3 right;

		static float Dot(const Vector3& left, const Vector3& right); //TEST
		static Vector3 Cross(const Vector3& left, const Vector3& right); //TEST
		static Vector3 Create(const char* string);

		Vector3();
		Vector3(float _x, float _y, float _z);

		float Magnitude() const; //TEST
		float SqrMagnitude() const; //TEST
		Vector3 Normalized() const; //TEST

		Vector3 operator+(const Vector3& right) const;
		Vector3 operator-(const Vector3& right) const;
		Vector3 operator*(const float scaler) const;
		Vector3 operator/(const float scaler) const;
		Vector3& operator+=(const Vector3& right);
		Vector3& operator-=(const Vector3& right);
		Vector3& operator*=(const float scaler);
		Vector3& operator/=(const float scaler);
		float& operator[](unsigned int index);
		bool operator!=(const Vector3& right) const;
		bool operator==(const Vector3& right) const;
		friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}
	};
}}

#endif // !PRIMEENGINE_VECTOR3

