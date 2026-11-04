#include "pch.h"
#include "CppUnitTest.h"
#include "D:/VS projects/7.1.рек/7.1.рек.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest71Rec
{
	TEST_CLASS(UnitTest71Rec)
	{
	public:

		// 1. Тест рекурсивної функції Change (обмін двох рядків місцями)
		TEST_METHOD(Test_Recursive_Change)
		{
			const int rowCount = 2;
			const int colCount = 3;

			int** q = new int* [rowCount];
			for (int i = 0; i < rowCount; i++)
				q[i] = new int[colCount];

			// Рядок 0: {10, 20, 30}
			q[0][0] = 10; q[0][1] = 20; q[0][2] = 30;
			// Рядок 1: {40, 50, 60}
			q[1][0] = 40; q[1][1] = 50; q[1][2] = 60;

			// Обмін рядків 0 та 1 починаючи з стовпчика j = 0
			Change(q, 0, 1, colCount, 0);

			Assert::AreEqual(40, q[0][0]);
			Assert::AreEqual(50, q[0][1]);
			Assert::AreEqual(60, q[0][2]);

			Assert::AreEqual(10, q[1][0]);
			Assert::AreEqual(20, q[1][1]);
			Assert::AreEqual(30, q[1][2]);

			for (int i = 0; i < rowCount; i++) delete[] q[i];
			delete[] q;
		}

		// 2. Тест рекурсивної функції Calc (сума, кількість та заміна на 0)
		TEST_METHOD(Test_Recursive_Calc)
		{
			const int rowCount = 2;
			const int colCount = 2;

			int** q = new int* [rowCount];
			for (int i = 0; i < rowCount; i++)
				q[i] = new int[colCount];

			// Критерій: обробляються всі, крім додатних парних
			q[0][0] = 4;  // Додатне парне -> ігнорується, залишається 4
			q[0][1] = 3;  // Непарне -> S += 3, k++, стає 0
			q[1][0] = -2; // Від'ємне -> S += (-2), k++, стає 0
			q[1][1] = 5;  // Непарне -> S += 5, k++, стає 0

			int S = 0, k = 0;
			Calc(q, rowCount, colCount, S, k, 0, 0);

			Assert::AreEqual(6, S); // 3 + (-2) + 5 = 6
			Assert::AreEqual(3, k);

			Assert::AreEqual(4, q[0][0]); // Не змінилося
			Assert::AreEqual(0, q[0][1]);
			Assert::AreEqual(0, q[1][0]);
			Assert::AreEqual(0, q[1][1]);

			for (int i = 0; i < rowCount; i++) delete[] q[i];
			delete[] q;
		}

		// 3. Тест рекурсивної функції Sort (сорттування рядків)
		TEST_METHOD(Test_Recursive_Sort)
		{
			const int rowCount = 2;
			const int colCount = 4;

			int** q = new int* [rowCount];
			for (int i = 0; i < rowCount; i++)
				q[i] = new int[colCount];

			// 0-й елемент другого рядка більший (20 > 10), тож вони мають помінятися місцями
			q[0][0] = 10; q[0][1] = 0; q[0][2] = 0; q[0][3] = 0;
			q[1][0] = 20; q[1][1] = 0; q[1][2] = 0; q[1][3] = 0;

			Sort(q, rowCount, colCount, 0, 0);

			Assert::AreEqual(20, q[0][0]);
			Assert::AreEqual(10, q[1][0]);

			for (int i = 0; i < rowCount; i++) delete[] q[i];
			delete[] q;
		}
	};
}