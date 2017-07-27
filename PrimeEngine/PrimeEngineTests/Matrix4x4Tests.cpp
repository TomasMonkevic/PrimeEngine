#include "stdafx.h"
#include "CppUnitTest.h"
#include <Math/Matrix4x4.h>
#include <string.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PrimeEngine::Math;

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

	template<>
	static std::wstring ToString<PrimeEngine::Math::Matrix4x4>(const PrimeEngine::Math::Matrix4x4& matrix)
	{
		std::wstring matrixToString = L"\0";
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				matrixToString += std::to_wstring(matrix[i][j]) + L" ";
			}
			matrixToString += L"\n";
		}
		return matrixToString;
	}
}}}

namespace PrimeEngineTests
{
	TEST_CLASS(Matrix4x4Tests)
	{
	public:

		TEST_METHOD(Matrix4x4MultiplicationTest) //anylize more
		{
			Matrix4x4 myMatrix(new float[4][4]{
				{ 4,2,0,0 },
				{ 0,8,1,0 },
				{ 0,1,0,0 },
				{ 0,0,0,0 },
			});
			Matrix4x4 myMatrix2(new float[4][4]{
				{ 4,2,1,0 },
				{ 2,0,4,0 },
				{ 9,4,2,0 },
				{ 0,0,0,0 },
			});
			Matrix4x4 expected(new float[4][4]{
				{ 20,8,12,0 },
				{ 25,4,34,0 },
				{ 2,0,4,0 },
				{ 0,0,0,0 },
			});
			Assert::AreEqual(expected, Matrix4x4::Multiply(myMatrix, myMatrix2), L"Multiplication failed", LINE_INFO());
		}

		TEST_METHOD(Matrix4x4DeterminantTest)
		{
			Matrix4x4 myMatrix(new float[4][4]{
				{  1, 2, 3, 4 },
				{ -2, 1,-4, 3 },
				{  3,-4,-1, 2 },
				{  4, 3,-2,-1 },
			});
			float expectedResult = 900.0f;
			float actualResult = myMatrix.Determinant();
			Assert::AreEqual(expectedResult, actualResult, L"Incorrect determinate", LINE_INFO());
		}

		TEST_METHOD(Matrix4x4InverseTest)
		{
			Matrix4x4 testMatrix(new float[4][4]{
				{  1, 2, 1, 1 },
				{  2, 5, 3, 5 },
				{  2, 5, 4, 7 },
				{  3, 7, 5, 9 },
			});
			Assert::AreEqual(Matrix4x4::identity(), testMatrix * testMatrix.Inverse(), L"Incorrect inverese matrix", LINE_INFO());
		}
	};
}