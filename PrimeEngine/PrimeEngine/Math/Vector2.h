#ifndef PRIMEENGINE_VECTOR2
#define PRIMEENGINE_VECTOR2

#include "../DllExport.h"
#include <iostream>

namespace PrimeEngine { namespace Math {

	class PRIMEENGINEAPI Vector2
	{
	public:
		float x, y;

		static const Vector2 one;
		static const Vector2 zero;
		static const Vector2 down;
		static const Vector2 left;
		static const Vector2 up;
		static const Vector2 right;

		static float Dot(const Vector2& left, const Vector2& right); //TEST

		Vector2();
		Vector2(float _x, float _y);

		float Magnitude() const; //TODO

		Vector2 operator+(const Vector2& right);
		Vector2 operator-(const Vector2& right);
		Vector2 operator*(const float scaler);
		Vector2 operator/(const float scaler);
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


