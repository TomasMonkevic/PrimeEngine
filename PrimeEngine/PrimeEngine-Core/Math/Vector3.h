#pragma once

#include <DllExport.h>
#include "MathFunc.h"
#include <iostream>

namespace PrimeEngine {	namespace Math {

	class Vector2;

	class PRIMEENGINEAPI Vector3
	{
	public:
		float x, y, z;

		static const Vector3 one()		{ return Vector3(1.0f, 1.0f, 1.0f); }
		static const Vector3 zero()		{ return Vector3(); }
		static const Vector3 back()		{ return Vector3(0.0f, 0.0f, -1.0f); }
		static const Vector3 down()		{ return Vector3(0.0f, -1.0f, 0.0f); }
		static const Vector3 left()		{ return Vector3(-1.0f, 0.0f, 0.0f); }
		static const Vector3 forward()	{ return Vector3(0.0f, 0.0f, 1.0f); }
		static const Vector3 up()		{ return Vector3(0.0f, 1.0f, 0.0f); }
		static const Vector3 right()	{ return Vector3(1.0f, 0.0f, 0.0f); }

		static const float Dot(const Vector3& left, const Vector3& right); //TEST
		static const Vector3 Cross(const Vector3& left, const Vector3& right); //TEST
		static const Vector3 Create(const char* string);

		explicit Vector3();
		explicit Vector3(float _x, float _y, float _z);
		Vector3(const Vector2& vec2);

		inline const float Magnitude() const { return sqrt(SqrMagnitude()); } //TEST
		inline const float SqrMagnitude() const { return x * x + y * y + z * z; } //TEST
		const Vector3 Normalized() const; //TEST

		const Vector3 operator+(const Vector3& right) const;
		const Vector3 operator-(const Vector3& right) const;
		const Vector3 operator*(const float scaler) const;
		const Vector3 operator/(const float scaler) const;
		Vector3& operator+=(const Vector3& right);
		Vector3& operator-=(const Vector3& right);
		Vector3& operator*=(const float scaler);
		Vector3& operator/=(const float scaler);
		float& operator[](unsigned int index);
		const float& operator[](unsigned int index) const;
		bool operator!=(const Vector3& right) const;
		bool operator==(const Vector3& right) const;
		friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}
	};
}}

