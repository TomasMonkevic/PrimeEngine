#ifndef MATRIX_4X4
#define MATRIX_4X4

#include "../DllExport.h"
#include <iostream>
#include "Vector4.h" //temp, might need to add all math

namespace PrimeEngine { namespace Math {
		
	class PRIMEENGINEAPI Matrix4x4
	{
	private:
		Vector4 GetRow(unsigned int row) const;
		Vector4 GetColumn(unsigned int column) const;
	public:
		static Matrix4x4 identity();
		static Matrix4x4& Multiply(Matrix4x4 left, const Matrix4x4& right); //write test

		float _matrix[4][4]; //make only get?

		Matrix4x4(const float matrix[4][4]);

		Matrix4x4 operator*(const Matrix4x4& right);
		Matrix4x4& operator*=(const Matrix4x4& right);
		bool operator==(const Matrix4x4& right) const;
		bool operator!=(const Matrix4x4& right) const;

		friend std::ostream& operator<<(std::ostream& stream, const Matrix4x4& matrix)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					stream << matrix._matrix[i][j] << " ";
				}
				stream << std::endl;
			}
			return stream;
		}
	};
}}

#endif // !MATRIX_4X4

