#include "stdafx.h"
#include "CppUnitTest.h"
#include <Vector3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PrimeEngine::Math;

namespace PrimeEngineTests
{		
	TEST_CLASS(Vector3Test)
	{
	public:
		
		TEST_METHOD(Vector3ConstructorTest)
		{
			float x = 1, y = 2, z = 3;
			Vector3 vector(x, y, z);
			Assert::AreEqual(vector.x, x);
			Assert::AreEqual(vector.y, y);
			Assert::AreEqual(vector.z, z);
		}

	};
}