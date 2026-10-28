#include "pch.h"
#include "CppUnitTest.h"
#include "D:\VS projects\6.4.іт\6.4.іт.cpp"   

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(SumPositive_Mixed)
		{
			double a[5] = { 1.5, -2, 3, 0, -4 };          // 1.5 + 3, нуль не враховується
			Assert::AreEqual(4.5, SumPositive(a, 5), 1e-9);
		}
		TEST_METHOD(SumPositive_NoPositive)
		{
			double a[3] = { -1, -2, 0 };
			Assert::AreEqual(0.0, SumPositive(a, 3), 1e-9);
		}
		TEST_METHOD(ProductBetween_Normal)
		{
			double a[5] = { 5, 2, 3, 4, 1 };              // між індексами 0 та 4: 2 * 3 * 4
			Assert::AreEqual(24.0, ProductBetween(a, 0, 4), 1e-9);
		}
		TEST_METHOD(ProductBetween_Adjacent)
		{
			double a[4] = { 9, -2, 3, 1 };                // між сусідніми елементами нічого немає
			Assert::AreEqual(1.0, ProductBetween(a, 1, 2), 1e-9);
		}
	};
}
