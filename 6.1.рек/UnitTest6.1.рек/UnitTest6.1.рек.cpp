#include "pch.h"
#include "CppUnitTest.h"
#include "D:\VS projects\6.1.рек\6.1.рек.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(Count_Mixed)
		{
			int a[7] = { 1, 2, 3, 4, -2, 0, 6 };   // придатні: 2, 4, 0, 6
			Assert::AreEqual(4, Count(a, 7, 0));
		}
		TEST_METHOD(Count_NoSuitable)
		{
			int b[5] = { -5, -4, 3, 5, 7 };        // придатних немає
			Assert::AreEqual(0, Count(b, 5, 0));
		}
		TEST_METHOD(Sum_Mixed)
		{
			int a[7] = { 1, 2, 3, 4, -2, 0, 6 };   // 2 + 4 + 0 + 6
			Assert::AreEqual(12, Sum(a, 7, 0));
		}
		TEST_METHOD(Sum_NoSuitable)
		{
			int b[5] = { -5, -4, 3, 5, 7 };
			Assert::AreEqual(0, Sum(b, 5, 0));
		}
	};
}
