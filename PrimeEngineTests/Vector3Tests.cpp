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
			Assert::AreEqual(x, vector.x, L"X value doesn't match", LINE_INFO());
			Assert::AreEqual(y, vector.y, L"Y value doesn't match", LINE_INFO());
			Assert::AreEqual(z, vector.z, L"Z value doesn't match", LINE_INFO());
		}

		TEST_METHOD(Vector3AdditionTest)
		{
			Vector3 v1(1, 2, 3);
			Vector3 v2(2, 3, 4);
			Vector3 result = v1 + v2;
			Assert::AreEqual(3.0f, result.x, L"X value doesn't match", LINE_INFO());
			Assert::AreEqual(5.0f, result.y, L"Y value doesn't match", LINE_INFO());
			Assert::AreEqual(7.0f, result.z, L"Z value doesn't match", LINE_INFO());
		}

		TEST_METHOD(Vector3SubtarctionTest)
		{
			Vector3 v1(1, 2, 3);
			Vector3 v2(2, 3, 4);
			Vector3 result = v1 - v2;
			Assert::AreEqual(-1.0f, result.x, L"X value doesn't match", LINE_INFO());
			Assert::AreEqual(-1.0f, result.y, L"Y value doesn't match", LINE_INFO());
			Assert::AreEqual(-1.0f, result.z, L"Z value doesn't match", LINE_INFO());

			result = v2 - v1;
			Assert::AreEqual(1.0f, result.x, L"X value doesn't match", LINE_INFO());
			Assert::AreEqual(1.0f, result.y, L"Y value doesn't match", LINE_INFO());
			Assert::AreEqual(1.0f, result.z, L"Z value doesn't match", LINE_INFO());
		}

	};
}