#include "stdafx.h"
#include "CppUnitTest.h"
#include <Math\Vector3.h>
#include <string.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PrimeEngine::Math;

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

	template<>
	static std::wstring ToString<PrimeEngine::Math::Vector3>(const PrimeEngine::Math::Vector3& vector3)
	{
		return L"(" + std::to_wstring(vector3.x) + L", " + std::to_wstring(vector3.y) + L", " + std::to_wstring(vector3.z) + L")";
	}
}}}

namespace Tests
{		
	TEST_CLASS(Vector3Tests)
	{
	public:

		TEST_METHOD(Vector3AdditionTest)
		{
			Vector3 v1(1, 2, 3);
			Vector3 v2(2, 3, 4);
			Vector3 expectedResult(3, 5, 7);
			Vector3 expectedV1(1, 2, 3);
			Vector3 result = v1 + v2;
			Assert::AreEqual(expectedResult, result, L"Vectors addition failed!");
			result.x = 100;
			Assert::AreEqual(expectedV1, v1, L"Vectors aren't equal!");
		}

		TEST_METHOD(Vector3SubtarctionTest)
		{
			Vector3 v1(1, 2, 3);
			Vector3 v2(2, 3, 4);
			Vector3 expectedResult(-1.0f, -1.0f, -1.0f);
			Vector3 result = v1 - v2;
			Assert::AreEqual(expectedResult, result, L"Vectors aren't equal!", LINE_INFO());

			result = v2 - v1;
			Vector3 expectedResult2(1.0f, 1.0f, 1.0f);
			Assert::AreEqual(expectedResult2, result, L"Vectors aren't equal!", LINE_INFO());
		}

		TEST_METHOD(Vector3EqualityTest)
		{
			Vector3 v1(1, 2, 3);
			Vector3 v2(2, 3, 4);
			bool expectedResult = false;
			Assert::AreEqual(expectedResult, v1 == v2, L"Vectors aren't equal!", LINE_INFO());

			Vector3 v3(1, 2, 3);
			expectedResult = true;
			Assert::AreEqual(expectedResult, v1 == v3, L"Vectors aren't equal!", LINE_INFO());
		}

		TEST_METHOD(Vector3ScalerTest)
		{
			float scaler = 2.0f;
			Vector3 vector(1, 2, 3);
			Vector3 expectedResult(2, 4, 6);
			Vector3 expectedVector(1, 2, 3);
			Vector3 result = vector * scaler;
			Assert::AreEqual(expectedResult, result,  L"Vectors aren't equal!", LINE_INFO());
			Assert::AreEqual(expectedVector, vector,  L"Vectors aren't equal!", LINE_INFO());
		}

		TEST_METHOD(Vector3InequalityTest)
		{
			Vector3 v1(1, 2, 3);
			Vector3 v2(2, 3, 4);
			bool expectedResult = true;
			Assert::AreEqual(expectedResult, v1 != v2, L"Vectors aren't equal!", LINE_INFO());

			Vector3 v3(1, 2, 3);
			expectedResult = false;
			Assert::AreEqual(expectedResult, v1 != v3, L"Vectors aren't equal!", LINE_INFO());
		}

	};
}