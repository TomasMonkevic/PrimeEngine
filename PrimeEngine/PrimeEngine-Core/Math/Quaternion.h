#pragma once

#include <DllExport.h>
#include "Vector3.h"
#include "Matrix4x4.h"

namespace PrimeEngine { namespace Math {

	class PRIMEENGINEAPI Quaternion 
	{
	public:
		float x, y, z, w;

		static const Quaternion identity() { return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); }

		Quaternion();
		Quaternion(const Vector3& vector, float scalar);
		Quaternion(const Matrix4x4& rotationMatrix);
		Quaternion(float _x, float _y, float _z); //from Euler Angles
		Quaternion(float _x, float _y, float _z, float _w); //raw values

		inline const float Normalized() const { return x * x + y * y + z * z + w * w; }
		const Quaternion Conjugate() const;
		const Vector3 EulerAngles() const;
		const Matrix4x4 RotationMatrix() const;


		const Quaternion operator+(const Quaternion& right) const;
		const Quaternion operator-(const Quaternion& right) const;
		const Quaternion operator*(const Quaternion& right) const;
		const Quaternion Quaternion::operator*(float scalar) const
		{
			return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
		}

		Quaternion& operator+=(const Quaternion& right);
		Quaternion& operator-=(const Quaternion& right);
		Quaternion& operator*=(const Quaternion& right);

		float& operator[](unsigned int index);
		const float& operator[](unsigned int index) const;

		bool operator!=(const Quaternion& right) const;
		bool operator==(const Quaternion& right) const;
	};
}}