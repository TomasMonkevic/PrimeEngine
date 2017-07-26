#pragma once

#include <DllExport.h>
#include "MathFunc.h"
#include <iostream>

namespace PrimeEngine { namespace Math {

	class Vector4;
	class Vector3;

	class PRIMEENGINEAPI Vector2
	{
	public:
		float x, y;

		static const Vector2 one()		{ return Vector2(1.0f, 1.0f); }
		static const Vector2 zero()		{ return Vector2(); }
		static const Vector2 down()		{ return Vector2(0.0f, -1.0f); }
		static const Vector2 left()		{ return Vector2(-1.0f, 0.0f); }
		static const Vector2 up()		{ return Vector2(0.0f, 1.0f); }
		static const Vector2 right()	{ return Vector2(1.0f, 0.0f); }

		static const float Dot(const Vector2& left, const Vector2& right); //TEST

		explicit Vector2();
		explicit Vector2(float _x, float _y);
		Vector2(const Vector3& vec3);
		Vector2(const Vector4& vec4);

		inline const float Magnitude() const { return sqrt(SqrMagnitude()); }
		inline const float SqrMagnitude() const { return x * x + y * y; }

		const Vector2 operator+(const Vector2& right) const;
		const Vector2 operator-(const Vector2& right) const;
		const Vector2 operator*(const float scaler) const;
		const Vector2 operator/(const float scaler) const;
		Vector2& operator+=(const Vector2& right);
		Vector2& operator-=(const Vector2& right);
		Vector2& operator*=(const float scaler);
		Vector2& operator/=(const float scaler);
		float& operator[](unsigned int index);
		const float& operator[](unsigned int index) const;
		bool operator!=(const Vector2& right) const;
		bool operator==(const Vector2& right) const;
		friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ")";
			return stream;
		}
	};
}}


