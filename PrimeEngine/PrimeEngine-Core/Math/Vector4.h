#pragma once

#include <DllExport.h>
#include <iostream>

namespace PrimeEngine { namespace Math {

	class PRIMEENGINEAPI Vector4
	{
	public:
		float x, y, z, w;

		static const Vector4 one;
		static const Vector4 zero;

		static float Dot(const Vector4& left, const Vector4& right); //TEST
		static Vector4 Create(const char* string);

		Vector4();
		Vector4(float _x, float _y, float _z, float _w);

		float Magnitude() const; //TODO

		Vector4 operator+(const Vector4& right);
		Vector4 operator-(const Vector4& right);
		Vector4 operator*(const float scaler);
		Vector4 operator/(const float scaler);
		Vector4& operator+=(const Vector4& right);
		Vector4& operator-=(const Vector4& right);
		Vector4& operator*=(const float scaler);
		Vector4& operator/=(const float scaler);
		float& operator[](unsigned int index);
		bool operator!=(const Vector4& right) const;
		bool operator==(const Vector4& right) const;
		friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}
	};
}}

