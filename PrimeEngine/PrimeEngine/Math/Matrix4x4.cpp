#include "Matrix4x4.h"

namespace PrimeEngine { namespace Math {

	const Matrix4x4 Matrix4x4::identity = Matrix4x4(new float[4][4]{
		{ 1,0,0,0 },
		{ 0,1,0,0 },
		{ 0,0,1,0 },
		{ 0,0,0,1 },
	});

	Matrix4x4::Matrix4x4(const float matrix[4][4])
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				_matrix[i][j] = matrix[i][j];
			}
		}
	}

	Vector4 Matrix4x4::GetRow(unsigned int row) const
	{
		if (row > 4)
		{
			throw "Index out of range";
		}
		return Vector4(_matrix[row][0], _matrix[row][1], _matrix[row][2], _matrix[row][3]);
	}

	Vector4 Matrix4x4::GetColumn(unsigned int column) const
	{
		if (column > 4)
		{
			throw "Index out of range";
		}
		return Vector4(_matrix[0][column], _matrix[1][column], _matrix[2][column], _matrix[3][column]);
	}

	Matrix4x4& Matrix4x4::Multiply(Matrix4x4 left, const Matrix4x4& right)
	{
		for (int i = 0; i < 4; i++)
		{
			Vector4 row = left.GetRow(i);
			for (int j = 0; j < 4; j++)
			{
				Vector4 column = right.GetColumn(j);
				left._matrix[i][j] = Vector4::Dot(row, column);
			}
		}
		return left;
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& right)
	{
		return Matrix4x4::Multiply(*this, right);
	}

	Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& right)
	{
		return Matrix4x4::Multiply(*this, right);
	}

	bool Matrix4x4::operator==(const Matrix4x4& right) const
	{
		for (int i = 0; i < 4; i++) //change to while?
		{
			for (int j = 0; j < 4; j++)
			{
				if (_matrix[i][j] != right._matrix[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}

	bool Matrix4x4::operator!=(const Matrix4x4& right) const
	{
		return !(*this == right);
	}

}}