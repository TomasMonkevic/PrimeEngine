#pragma once

#include <DllExport.h>
#include "MathFunc.h"
#include <iostream>

namespace PrimeEngine { namespace Math {

	class Vector2;
	class Vector3;

	class PRIMEENGINEAPI Vector4
	{
	public:
		float x, y, z, w;

		static const Vector4 one()		{ return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }
		static const Vector4 zero()		{ return Vector4(); }

		static const float Dot(const Vector4& left, const Vector4& right); //TEST
		static const Vector4 Create(const char* string); //DEPRECATED

		explicit Vector4();
		explicit Vector4(float _x, float _y, float _z, float _w);
		Vector4(const Vector2& vec2);
		Vector4(const Vector3& vec3);

		inline const float Magnitude() const { return sqrt(SqrMagnitude()); } //TEST
		inline const float SqrMagnitude() const { return x * x + y * y + z * z + w * w; } //TEST

		const Vector4 operator+(const Vector4& right) const;
		const Vector4 operator-(const Vector4& right) const;
		const Vector4 operator*(const float scaler) const;
		const Vector4 operator/(const float scaler) const;
		Vector4& operator+=(const Vector4& right);
		Vector4& operator-=(const Vector4& right);
		Vector4& operator*=(const float scaler);
		Vector4& operator/=(const float scaler);
		float& operator[](unsigned int index);
		const float& operator[](unsigned int index) const;
		bool operator!=(const Vector4& right) const;
		bool operator==(const Vector4& right) const;
		friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}
	};
}}

