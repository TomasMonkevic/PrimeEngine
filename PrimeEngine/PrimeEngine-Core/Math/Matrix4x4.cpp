#include "Matrix4x4.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "../PrimeException.h"

namespace PrimeEngine { namespace Math {

	Matrix4x4::Matrix4x4()
	{
		for (int col = 0; col < 4; col++)
		{
			for (int row = 0; row < 4; row++)
			{
				_matrix[col][row] = 0;
			}
		}
	}

	Matrix4x4::Matrix4x4(float diagonalValue) 
		: Matrix4x4()
	{
		_matrix[0][0] = diagonalValue;
		_matrix[1][1] = diagonalValue;
		_matrix[2][2] = diagonalValue;
		_matrix[3][3] = diagonalValue;
	}

	Matrix4x4::Matrix4x4(const float matrix[4][4])
	{
		for (int col = 0; col < 4; col++)
		{
			for (int row = 0; row < 4; row++)
			{
				_matrix[col][row] = matrix[row][col];
			}
		}
	}

	inline float* Matrix4x4::Minor(int col, int row, int size, const float elements[]) const
	{
		float* temp = new float[(size - 1) * (size - 1)];
		int tempI = 0;
		for (int j = 0; j < size * size; j++)
		{
			if (j % size != row && (col * size > j || (col + 1) * size <= j))
			{
				temp[tempI] = elements[j];
				tempI++;
			}
		}
		return temp;
	}

	float Matrix4x4::Det(int size, const float elements[]) const
	{
		if (size == 1)
		{
			return elements[0];
		}
		else if (size == 2)
		{
			return elements[0 * size + 0] * elements[1 * size + 1] - elements[0 * size + 1] * elements[1 * size + 0];
		}
		else
		{
			float sum = 0;
			for (int i = 0; i < size; i++)
			{
				float* temp = Minor(0, i, size, elements);
				float adjunktas = elements[0 * size + i] * (float)pow(-1, 0 + i) * Det(size - 1, temp);
				delete[] temp;
				sum += adjunktas;
			}
			return sum;
		}
	}

	Matrix4x4 Matrix4x4::Transpose() const
	{
		return Matrix4x4::zero();
	}

	Matrix4x4 Matrix4x4::Scale(float scaler) const
	{
		Matrix4x4 temp;
		for (int col = 0; col < 4; col++)
		{
			for (int row = 0; row < 4; row++)
			{
				temp[col][row] = (*this)[col][row] * scaler;
			}
		}
		return temp;
	}

	Matrix4x4 Matrix4x4::Inverse() const
	{
		//TODO check if determinant not 0
		Matrix4x4 temp;
		for (int col = 0; col < 4; col++)
		{
			for (int row = 0; row < 4; row++)
			{
				float* minor = Minor(col, row, 4, GetElements());
				temp[row][col] = (float)pow(-1, col+row) * Det(3, minor);
				delete[] minor;
			}
		}
		return temp.Scale(1 / Det(4, GetElements()));
	}

	Vector4 Matrix4x4::GetRow(unsigned int row) const
	{
		if (row >= 4)
		{
			PrimeException indexOutOfRange("Index out of range", -1);
			throw indexOutOfRange;
		}
		return Vector4(_matrix[0][row], _matrix[1][row], _matrix[2][row], _matrix[3][row]);
	}

	void Matrix4x4::SetRow(unsigned int row, const Vector4& value)
	{
		if (row >= 4)
		{
			PrimeException indexOutOfRange("Index out of range", -1);
			throw indexOutOfRange;
		}
		_matrix[0][row] = value.x;
		_matrix[1][row] = value.y;
		_matrix[2][row] = value.z;
		_matrix[3][row] = value.w;
	}

	const Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& left, const Matrix4x4& right)
	{
		Matrix4x4 result = left;
		for (int i = 0; i < 4; i++)
		{
			const Vector4& row = result.GetRow(i); //think about this;
			for (int j = 0; j < 4; j++)
			{
				const Vector4& column = right[j];
				result._matrix[j][i] = Vector4::Dot(row, column);
			}
		}
		return result;
	}

	const Vector4 Matrix4x4::Multiply(const Matrix4x4& left, const Vector4& right)
	{
		Vector4 result = right;
		for (int i = 0; i < 4; i++)
		{
			const Vector4& row = left.GetRow(i);
			result[i] = Vector4::Dot(row, right);
		}
		return result;
	}

	const Vector3 Matrix4x4::Multiply(const Matrix4x4& left, const Vector3& right)
	{
		Vector3 result = right;
		const Vector4& col = right;
		for (int i = 0; i < 3; i++)
		{
			const Vector4& row = left.GetRow(i);
			result[i] = Vector4::Dot(row, col);
		}
		return result;
	}

	const Matrix4x4 Matrix4x4::Orthographic(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		Matrix4x4 result(new float[4][4]{
			{ 2.0f / (right - left), 0, 0, -(right + left) / (right - left)},
			{ 0, 2.0f / (top - bottom), 0, -(top + bottom) / (top - bottom) },
			{ 0, 0, -2.0f / (zFar - zNear), -(zFar + zNear) / (zFar - zNear) },
			{ 0, 0, 0, 1 }
		});
		return result;
	}

	const Matrix4x4 Matrix4x4::Perspective(float fov, float aspectRatio, float zNear, float zFar)
	{
		Matrix4x4 result(new float[4][4]{
			{ (1 / (float)tan(ToRadians(fov) / 2)) / aspectRatio, 0, 0, 0 },
			{ 0, 1 / (float)tan(ToRadians(fov) / 2), 0, 0 },
			{ 0, 0, -zFar / (zFar - zNear), - (zNear * zFar) / (zFar - zNear)},
			{ 0, 0, -1, 0 }
		});
		return result;
	}

	const Matrix4x4 Matrix4x4::Transform(const Vector3& translation)
	{
		Matrix4x4 result = Matrix4x4::identity();
		result[3][0] = translation.x;
		result[3][1] = translation.y;
		result[3][2] = translation.z;
		return result;
	}

	const Matrix4x4 Matrix4x4::Scale(const Vector3& scaler)
	{
		Matrix4x4 result = Matrix4x4::identity();
		result[0][0] = scaler.x;
		result[1][1] = scaler.y;
		result[2][2] = scaler.z;
		return result;
	}

	//const Matrix4x4 Matrix4x4::Rotate(float angle, const Vector3& axis)
	//{
	//	Matrix4x4 result = Matrix4x4::identity();
	//	float angleCos = cos(angle);
	//	float angleSin = sin(angle);
	//	float angleCos1 = 1 - cos(angle);
	//	result[0][0] = angleCos + axis.x * axis.x * angleCos1;
	//	result[0][1] = axis.y * axis.x * angleCos1 + axis.z * angleSin;
	//	result[0][2] = axis.z * axis.x * angleCos1 - axis.y * angleSin;

	//	result[1][0] = axis.x * axis.y * angleCos1 - axis.z * angleSin;
	//	result[1][1] = angleCos + axis.y * axis.y * angleCos1;
	//	result[1][2] = axis.z * axis.y * angleCos1 + axis.x * angleSin;

	//	result[2][0] = axis.x * axis.z * angleCos1 + axis.y * angleSin;
	//	result[2][1] = axis.y * axis.z * angleCos1 - axis.x * angleSin;
	//	result[2][2] = angleCos + axis.z * axis.z * angleCos1;
	//	return result;
	//}

	const Matrix4x4 Matrix4x4::TRS(const Vector3& position, const Quaternion& rotation, const Vector3& scaler)
	{
		Matrix4x4 result = Matrix4x4::identity();
		result = Matrix4x4::Transform(position) * rotation.RotationMatrix() * Matrix4x4::Scale(scaler);
		return result;
	}

	const Matrix4x4 Matrix4x4::operator*(const Matrix4x4& right) const
	{
		return Multiply(*this, right);
	}

	const Vector4 Matrix4x4::operator*(const Vector4& right) const
	{
		return Multiply(*this, right);
	}

	const Vector3 Matrix4x4::operator*(const Vector3& right) const
	{
		return Multiply(*this, right);
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
				if (_matrix[i][j] != right._matrix[i][j]) //add marginal float comperer
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

	Vector4& Matrix4x4::operator[](unsigned int col)
	{
		return const_cast<Vector4&>(static_cast<const Matrix4x4&>(*this)[col]);
	}

	const Vector4& Matrix4x4::operator[](unsigned int col) const
	{
		if (col >= 4)
		{
			PrimeException indexOutOfRange("Index out of range", -1);
			throw indexOutOfRange;
		}
		return (Vector4&)_matrix[col];
	}

}}