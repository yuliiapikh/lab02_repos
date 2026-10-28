#include "pch.h"
#include "CppUnitTest.h"
#include "D:\VS projects\6.2.рек\6.2.рек.cpp"  

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(SumEven_Mixed)
		{
			int a[7] = { 1, 2, 3, 4, -2, 0, 6 };   // 2 + 4 + (-2) + 0 + 6
			Assert::AreEqual(10, SumEven(a, 7, 0));
		}
		TEST_METHOD(SumEven_NoEven)
		{
			int a[3] = { 1, 3, -5 };               // парних немає
			Assert::AreEqual(0, SumEven(a, 3, 0));
		}
		TEST_METHOD(SumEven_NegativeEven)
		{
			int a[3] = { -4, -2, 7 };              // -4 + (-2)
			Assert::AreEqual(-6, SumEven(a, 3, 0));
		}
	};
}