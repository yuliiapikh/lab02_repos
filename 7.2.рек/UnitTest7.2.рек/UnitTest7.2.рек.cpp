#include "pch.h"
#include "CppUnitTest.h"
#include "D:/VS projects/7.2.рек/7.2.рек.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest72Rec
{
	TEST_CLASS(UnitTest72Rec)
	{
	public:

		// 1. Тест рекурсивного пошуку максимуму над головною діагоналлю
		TEST_METHOD(Test_Recursive_SearchMaxAbove)
		{
			const int N = 3;
			int** a = new int* [N];
			for (int i = 0; i < N; i++)
				a[i] = new int[N];

			a[0][0] = 1;  a[0][1] = 10; a[0][2] = 2;
			a[1][0] = 5;  a[1][1] = 3;  a[1][2] = 15;
			a[2][0] = 7;  a[2][1] = 8;  a[2][2] = 4;

			int maxI = 0, maxJ = 1, maxVal = a[0][1];

			SearchMaxAbove(a, N, 0, maxVal, maxI, maxJ);

			Assert::AreEqual(15, maxVal);
			Assert::AreEqual(1, maxI);
			Assert::AreEqual(2, maxJ);

			for (int i = 0; i < N; i++) delete[] a[i];
			delete[] a;
		}

		// 2. Тест рекурсивного пошуку мінімуму під головною діагоналлю
		TEST_METHOD(Test_Recursive_SearchMinBelow)
		{
			const int N = 3;
			int** a = new int* [N];
			for (int i = 0; i < N; i++)
				a[i] = new int[N];

			a[0][0] = 1;  a[0][1] = 10; a[0][2] = 2;
			a[1][0] = 5;  a[1][1] = 3;  a[1][2] = 15;
			a[2][0] = 7;  a[2][1] = -4; a[2][2] = 4;

			int minI = 1, minJ = 0, minVal = a[1][0];

			SearchMinBelow(a, N, 1, minVal, minI, minJ);

			Assert::AreEqual(-4, minVal);
			Assert::AreEqual(2, minI);
			Assert::AreEqual(1, minJ);

			for (int i = 0; i < N; i++) delete[] a[i];
			delete[] a;
		}

		// 3. Тест функції обміну місцями двох елементів матриці (Swap)
		TEST_METHOD(Test_Swap)
		{
			const int N = 2;
			int** a = new int* [N];
			for (int i = 0; i < N; i++)
				a[i] = new int[N];

			a[0][0] = 10; a[0][1] = 20;
			a[1][0] = 30; a[1][1] = 40;

			// Міняємо місцями a[0][1] та a[1][0]
			Swap(a, 0, 1, 1, 0);

			Assert::AreEqual(30, a[0][1]);
			Assert::AreEqual(20, a[1][0]);

			for (int i = 0; i < N; i++) delete[] a[i];
			delete[] a;
		}

		// 4. Тест функції Sum
		TEST_METHOD(Test_Sum)
		{
			int result = Sum(15, -4);
			Assert::AreEqual(11, result);
		}
	};
}