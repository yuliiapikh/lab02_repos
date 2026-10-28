#include "pch.h"
#include "CppUnitTest.h"
#include "D:\VS projects\6.3.іт\6.3.іт.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(SumNegative_Int_Mixed)
		{
			int a[5] = { 1, -2, 3, -4, 0 };        // -2 + (-4)
			Assert::AreEqual(-6, SumNegative(a, 5));
		}
		TEST_METHOD(SumNegative_Int_NoNegative)
		{
			int a[4] = { 0, 1, 2, 3 };             // від'ємних немає, 0 не враховується
			Assert::AreEqual(0, SumNegative(a, 4));
		}
		TEST_METHOD(SumNegative_Int_AllNegative)
		{
			int a[3] = { -1, -2, -3 };
			Assert::AreEqual(-6, SumNegative(a, 3));
		}
		TEST_METHOD(SumNegative_Template_Double)
		{
			double b[4] = { 1.5, -2.5, -0.5, 4.0 };  // -2.5 + (-0.5)
			Assert::AreEqual(-3.0, SumNegative<double>(b, 4));
		}
	};
}
