#pragma once

#include <DllExport.h>
#include <iostream>
#include "MathFunc.h"
#include "Vector4.h"

namespace PrimeEngine { namespace Math {
		
	class Vector3;

	class PRIMEENGINEAPI Matrix4x4
	{
	private: //Variables
		float _matrix[4][4];

	public:
		static const Matrix4x4 identity()	{ return Matrix4x4(1.0f); };
		static const Matrix4x4 zero()		{ return Matrix4x4(); }

	private: //Methods
		inline float* Minor(int col, int row, int size, const float elements[]) const;
		float Det(int size, const float elements[]) const;
	public:
		static const Matrix4x4 Multiply(const Matrix4x4& left, const Matrix4x4& right);
		static const Vector4 Multiply(const Matrix4x4& left, const Vector4& right); //TEST
		static const Vector3 Multiply(const Matrix4x4& left, const Vector3& right); //TEST
		static const Matrix4x4 Orthographic(float left, float right, float bottom, float top, float zNear, float zFar);
		static const Matrix4x4 Perspective(float fov, float aspectRatio, float zNear, float zFar); //TODO
		static const Matrix4x4 Transform(const Vector3& translation);
		static const Matrix4x4 Scale(const Vector3& scaler); //TEST
		static const Matrix4x4 Rotate(float angle, const Vector3& axis); //TEST
		static const Matrix4x4 TRS(const Vector3& position, const Matrix4x4& rotationMatrix, const Vector3& scaler); //change to quaternion

		Matrix4x4();
		Matrix4x4(float diagonalValue);
		Matrix4x4(const float matrix[4][4]);

		inline float Determinant() const { return Det(4, GetElements()); }
		Matrix4x4 Transpose() const; //TODO
		Matrix4x4 Scale(float scaler) const;
		Matrix4x4 Inverse() const; //TODO

		Vector4 GetRow(unsigned int row) const; //TODO
		void SetRow(unsigned int row, const Vector4& value); //TODO
		inline const float* GetElements() const { return (float*)_matrix;	}

		const Matrix4x4 operator*(const Matrix4x4& right) const;
		const Vector4 operator*(const Vector4& right) const;
		const Vector3 operator*(const Vector3& right) const;
		Matrix4x4& operator*=(const Matrix4x4& right);
		bool operator==(const Matrix4x4& right) const;
		bool operator!=(const Matrix4x4& right) const;
		Vector4& operator[](unsigned int col);
		const Vector4& operator[](unsigned int col) const; //Gets matrix columns
		friend std::ostream& operator<<(std::ostream& stream, const Matrix4x4& matrix)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					stream << matrix._matrix[j][i] << " ";
				}
				stream << std::endl;
			}
			return stream;
		}
	};
}}


