#ifndef PRIMEENGINE_VECTOR3
#define PRIMEENGINE_VECTOR3

namespace PrimeEngine
{
	namespace Math
	{
		class __declspec(dllexport) Vector3
		{
		public:
			float x, y, z;
			Vector3();
			Vector3(float x, float y, float z);
			Vector3 operator+(const Vector3& right);
		};
	}
}

#endif // !PRIMEENGINE_VECTOR3

