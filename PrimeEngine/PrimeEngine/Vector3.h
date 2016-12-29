#ifndef PRIMEENGINE_VECTOR3
#define PRIMEENGINE_VECTOR3

#ifndef _DLL
#define MYLIBAPI __declspec(dllimport)
#else
#define MYLIBAPI __declspec(dllexport)
#endif

namespace PrimeEngine
{
	namespace Math
	{
		class MYLIBAPI Vector3
		{
		public:
			float x, y, z;
			Vector3();
			Vector3(float x, float y, float z);
			Vector3 operator+(const Vector3& right);
			Vector3 operator-(const Vector3& right);
			Vector3 operator*(float scaler);
			Vector3 operator/(float scaler);
			bool operator!=(const Vector3& right);
			bool operator==(const Vector3& right);
		};
	}
}

#endif // !PRIMEENGINE_VECTOR3

