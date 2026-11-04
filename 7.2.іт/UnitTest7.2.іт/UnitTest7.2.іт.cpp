#include "pch.h"
#include "CppUnitTest.h"
#include "D:/VS projects/7.2.іт/7.2.іт.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest72Iter
{
	TEST_CLASS(UnitTest72Iter)
	{
	public:

		// 1. Тест пошуку максимуму над головною діагоналлю (j > i)
		TEST_METHOD(Test_SearchMaxAbove)
		{
			const int n = 3;
			int** a = new int* [n];
			for (int i = 0; i < n; i++)
				a[i] = new int[n];

			a[0][0] = 1;  a[0][1] = 10; a[0][2] = 2;
			a[1][0] = 5;  a[1][1] = 3;  a[1][2] = 15;
			a[2][0] = 7;  a[2][1] = 8;  a[2][2] = 4;

			int maxVal, maxI, maxJ;
			SearchMaxAbove(a, n, maxVal, maxI, maxJ);

			Assert::AreEqual(15, maxVal);
			Assert::AreEqual(1, maxI);
			Assert::AreEqual(2, maxJ);

			for (int i = 0; i < n; i++) delete[] a[i];
			delete[] a;
		}

		// 2. Тест пошуку мінімуму під головною діагоналлю (j < i)
		TEST_METHOD(Test_SearchMinBelow)
		{
			const int n = 3;
			int** a = new int* [n];
			for (int i = 0; i < n; i++)
				a[i] = new int[n];

			a[0][0] = 1;  a[0][1] = 10; a[0][2] = 2;
			a[1][0] = 5;  a[1][1] = 3;  a[1][2] = 15;
			a[2][0] = 7;  a[2][1] = -4; a[2][2] = 4;

			int minVal, minI, minJ;
			SearchMinBelow(a, n, minVal, minI, minJ);

			Assert::AreEqual(-4, minVal);
			Assert::AreEqual(2, minI);
			Assert::AreEqual(1, minJ);

			for (int i = 0; i < n; i++) delete[] a[i];
			delete[] a;
		}

		// 3. Тест обміну місцями двох елементів матриці (Swap)
		TEST_METHOD(Test_Swap)
		{
			const int n = 2;
			int** a = new int* [n];
			for (int i = 0; i < n; i++)
				a[i] = new int[n];

			a[0][0] = 10; a[0][1] = 20;
			a[1][0] = 30; a[1][1] = 40;

			// Міняємо місцями a[0][1] та a[1][0]
			Swap(a, 0, 1, 1, 0);

			Assert::AreEqual(30, a[0][1]);
			Assert::AreEqual(20, a[1][0]);

			for (int i = 0; i < n; i++) delete[] a[i];
			delete[] a;
		}

		// 4. Тест обчислення суми (Sum)
		TEST_METHOD(Test_Sum)
		{
			int result = Sum(15, -4);
			Assert::AreEqual(11, result);
		}
	};
}