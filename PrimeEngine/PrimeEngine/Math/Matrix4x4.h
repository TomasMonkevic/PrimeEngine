#ifndef MATRIX_4X4
#define MATRIX_4X4

#include "../DllExport.h"
#include <iostream>
#include "Vector4.h"
#include "Vector3.h"
#include "MathFunc.h"

namespace PrimeEngine { namespace Math {
		
	class PRIMEENGINEAPI Matrix4x4
	{
	private: //Variables
		float _matrix[4][4];

	public:
		static const Matrix4x4 identity;
		static const Matrix4x4 zero;

	private: //Methods

	public:
		static Matrix4x4& Multiply(Matrix4x4 left, const Matrix4x4& right);
		static Matrix4x4 Orthographic(float left, float right, float bottom, float top, float zNear, float zFar);
		static Matrix4x4 Perspective(float fov, float aspectRatio, float zNear, float zFar); //TODO
		static Matrix4x4 Transform(const Vector3& translation);
		static Matrix4x4 Scale(const Vector3& scaler); //TEST
		static Matrix4x4 Rotate(float angle, const Vector3& axis); //TEST
		static Matrix4x4 TRS(const Vector3& position, const Matrix4x4& rotationMatrix, const Vector3& scaler); //change to quaternion

		Matrix4x4();
		Matrix4x4(float diagonalValue);
		Matrix4x4(const float matrix[4][4]);

		float* GetElements() const;
		Vector4 GetRow(unsigned int row) const; //TODO
		void SetRow(unsigned int row, const Vector4& value); //TODO

		Matrix4x4 operator*(const Matrix4x4& right);
		Matrix4x4& operator*=(const Matrix4x4& right);
		bool operator==(const Matrix4x4& right) const;
		bool operator!=(const Matrix4x4& right) const;
		Vector4& operator[](unsigned int col) const; //Gets matrix columns
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

#endif // !MATRIX_4X4

