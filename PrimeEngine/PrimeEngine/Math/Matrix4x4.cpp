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
		for (int col = 0; col < 4; col++)
		{
			for (int row = 0; row < 4; row++)
			{
				_matrix[row][col] = matrix[col][row]; //are you fucking seroius?
			}
		}
	}

	Vector4 Matrix4x4::GetRow(unsigned int row) const
	{
		if (row > 4)
		{
			throw "Index out of range";
		}
		return Vector4(_matrix[0][row], _matrix[1][row], _matrix[2][row], _matrix[3][row]);
	}

	Vector4& Matrix4x4::GetColumn(unsigned int column) const //construct a new vector - not good. better to pass reference use union
	{
		if (column > 4)
		{
			throw "Index out of range";
		}
		Vector4 result = (Vector4&)_matrix[column];
		//return Vector4(_matrix[column][0], _matrix[column][1], _matrix[column][2], _matrix[column][3]);
		return result;
	}

	Matrix4x4& Matrix4x4::Multiply(Matrix4x4 left, const Matrix4x4& right)
	{
		for (int i = 0; i < 4; i++)
		{
			Vector4 row = left.GetRow(i); //think about this;
			for (int j = 0; j < 4; j++)
			{
				Vector4 column = right.GetColumn(j);
				left._matrix[j][i] = Vector4::Dot(row, column);
			}
		}
		return left;
	}

	Matrix4x4 Matrix4x4::Orthographic(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		Matrix4x4 result(new float[4][4]{
			{ 2.0f / (right - left), 0, 0, (right + left) / (left - right)},
			{ 0, 2.0f / (top - bottom), 0, (top + bottom) / (bottom - top) },
			{ 0, 0, -2.0f / (zFar - zNear), (zFar + zNear) / (zFar - zNear) },
			{ 0, 0, 0, 1 }
		});
		return result;
	}

	//TODO
	Matrix4x4 Matrix4x4::Perspective(float fov, float aspectRatio, float zNear, float zFar)
	{
		Matrix4x4 result(new float[4][4]{
			{ 0, 0, 0, 1 },
			{ 0, 0, 0, 1 },
			{ 0, 0, 0, 1 },
			{ 0, 0, 0, 1 }
		});
		return result;
	}

	Matrix4x4 Matrix4x4::Transform(const Vector3& translation)
	{
		Matrix4x4 result = Matrix4x4::identity;
		//TODO set column;
		result._matrix[3][0] = translation.x;
		result._matrix[3][1] = translation.y;
		result._matrix[3][2] = translation.z;
		return result;
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& right)
	{
		return Matrix4x4::Multiply(*this, right);
	}

	Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& right)
	{
		*this = Matrix4x4::Multiply(*this, right);
		return *this;
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