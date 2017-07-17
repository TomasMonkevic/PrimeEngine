#ifndef PRIMEENGINE_VECTOR2
#define PRIMEENGINE_VECTOR2

#include "Vector3.h"
#include "Vector4.h"
#include <DllExport.h>
#include <iostream>

namespace PrimeEngine { namespace Math {

	class PRIMEENGINEAPI Vector2
	{
	public:
		float x, y;

		static const Vector2 one()		{ return Vector2(1.0f, 1.0f); }
		static const Vector2 zero()		{ return Vector2(); }
		static const Vector2 down()		{ return Vector2(0.0f, -1.0f); }
		static const Vector2 left()		{ return Vector2(-1.0f, 0.0f); }
		static const Vector2 up()		{ return Vector2(0.0f, 1.0f); }
		static const Vector2 right()	{ return Vector2(1.0f, 0.0f); }

		static float Dot(const Vector2& left, const Vector2& right); //TEST

		explicit Vector2();
		explicit Vector2(float _x, float _y);

		operator Vector3() const { return Vector3(x, y, 0.0f); }
		operator Vector4() const { return Vector4(x, y, 0.0f, 0.0f); }

		float Magnitude() const; //TODO

		const Vector2 operator+(const Vector2& right);
		const Vector2 operator-(const Vector2& right);
		const Vector2 operator*(const float scaler);
		const Vector2 operator/(const float scaler);
		Vector2& operator+=(const Vector2& right);
		Vector2& operator-=(const Vector2& right);
		Vector2& operator*=(const float scaler);
		Vector2& operator/=(const float scaler);
		float& operator[](unsigned int index);
		bool operator!=(const Vector2& right) const;
		bool operator==(const Vector2& right) const;
		friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ")";
			return stream;
		}
	};
}}

#endif // !PRIMEENGINE_VECTOR2


