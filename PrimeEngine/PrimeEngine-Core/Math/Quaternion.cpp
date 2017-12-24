#include "Quaternion.h"

namespace PrimeEngine { namespace Math {
	
	Quaternion::Quaternion()
		: Quaternion(0.0f, 0.0f, 0.0f, 0.0f)
	{

	}

	Quaternion::Quaternion(const Vector3& vector, float scalar)
		: Quaternion(vector.x, vector.y, vector.z, scalar)
	{

	}

	Quaternion::Quaternion(const Matrix4x4& rotationMatrix)
	{

	}

	Quaternion::Quaternion(float _x, float _y, float _z)
	{
		float cr, cp, cy, sr, sp, sy, cpcy, spsy;
		// calculate trig identities
		cr = cos(_x * (PI / 180.0f) / 2);
		cp = cos(_y * (PI / 180.0f) / 2);
		cy = cos(_z * (PI / 180.0f) / 2);
		sr = sin(_x * (PI / 180.0f) / 2);
		sp = sin(_y * (PI / 180.0f) / 2);
		sy = sin(_z * (PI / 180.0f) / 2);
		cpcy = cp * cy;
		spsy = sp * sy;

		w = cr * cpcy + sr * spsy;
		x = sr * cpcy - cr * spsy;
		y = cr * sp * cy + sr * cp * sy;
		z = cr * cp * sy - sr * sp * cy;
	}

	Quaternion::Quaternion(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{

	}

	const Vector3 Quaternion::EulerAngles() const
	{
		//return Vector3(atan2(2 * x * w - 2 * y * z, 1 - 2 * x * x - 2 * z * z),
		//	atan2(2 * y * w - 2 * x * z, 1 - 2 * y * y - 2 * z * z),
		//	asin(2 * x * y + 2 * z * w));
		float ysqr = y * y;

		// roll (x-axis rotation)
		float t0 = +2.0f * (w * x + y * z);
		float t1 = +1.0f - 2.0f * (x * x + ysqr);

		// pitch (y-axis rotation)
		float t2 = +2.0f * (w * y - z * x);
		t2 = ((t2 > 1.0f) ? 1.0f : t2);
		t2 = ((t2 < -1.0f) ? -1.0f : t2);

		// yaw (z-axis rotation)
		float t3 = +2.0f * (w * z + x * y);
		float t4 = +1.0f - 2.0f * (ysqr + z * z);

		return Vector3(std::atan2(t0, t1), std::asin(t2), std::atan2(t3, t4));
	}

	const Matrix4x4 Quaternion::RotationMatrix() const
	{
		//TODO fix the dataShit
		float mat1Data[4][4] = {
			{ w, -z,   y, -x },
			{ z,  w,  -x, -y },
			{ -y, x,   w, -z },
			{ x,  y,   z,  w } };

		float mat2Data[4][4] = {
			{ w, -z,   y,  x },
			{ z,  w,  -x,  y },
			{ -y, x,   w,  z },
			{ -x,-y,  -z,  w } };

		Matrix4x4 mat1(mat1Data);

		Matrix4x4 mat2(mat2Data);

		return mat1 * mat2;
	}

	const Quaternion Quaternion::operator+(const Quaternion& right) const
	{
		return Quaternion(x + right.x, y + right.y, z + right.z, w + right.w);
	}

	const Quaternion Quaternion::operator-(const Quaternion& right) const
	{
		return Quaternion(x - right.x, y - right.y, z - right.z, w - right.w);
	}

	const Quaternion Normalize(const Quaternion& quaternion)
	{
		float lenSqr, lenInv;
		lenSqr = quaternion.Normalized();
		lenInv = rsqrt(lenSqr);
		return quaternion * lenInv;
	}

	const Quaternion Quaternion::Rotation(float radians, const Vector3& unitVec)
	{
		float angle = radians * 0.5f;
		return Quaternion((unitVec * sin(angle)), cos(angle));
	}

	//qq� = [ww� - v � v�, v x v� + wv� + w�v]
	const Quaternion Quaternion::operator*(const Quaternion& right) const
	{
		return Normalize(Quaternion(
			(((w * right.x) + (x * right.w)) + (y * right.z)) - (z * right.y),
			(((w * right.y) + (y * right.w)) + (z * right.x)) - (x * right.z),
			(((w * right.z) + (z * right.w)) + (x * right.y)) - (y * right.x),
			(((w * right.w) - (x * right.x)) - (y * right.y)) - (z * right.z)
		));
	}

	Quaternion& Quaternion::operator+=(const Quaternion& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		w += right.w;
		return *this;
	}

	Quaternion& Quaternion::operator-=(const Quaternion& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		w -= right.w;
		return *this;
	}

	Quaternion& Quaternion::operator*=(const Quaternion& right)
	{
		*this = *this * right;
		return *this;
	}

	float& Quaternion::operator[](unsigned int index)
	{
		return const_cast<float&>(static_cast<const Quaternion&>(*this)[index]);
	}

	const float& Quaternion::operator[](unsigned int index) const
	{
		return *(&x + index);
	}

	bool Quaternion::operator!=(const Quaternion& right) const
	{
		return !(*this == right);
	}

	bool Quaternion::operator==(const Quaternion& right) const
	{
		if (x == right.x && y == right.y && z == right.z && w == right.w)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}}