#include "pch.h"
#include "CppUnitTest.h"
#include "D:/VS projects/7.1.1.іт/7.1.1.іт.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest71
{
	TEST_CLASS(UnitTest71)
	{
	public:

		// 1. Тест функції Change (обмін двох рядків місцями)
		TEST_METHOD(Test_Change)
		{
			const int rowCount = 2;
			const int colCount = 3;

			int** q = new int* [rowCount];
			for (int i = 0; i < rowCount; i++)
				q[i] = new int[colCount];

			// Рядок 0: {1, 2, 3}
			q[0][0] = 1; q[0][1] = 2; q[0][2] = 3;
			// Рядок 1: {4, 5, 6}
			q[1][0] = 4; q[1][1] = 5; q[1][2] = 6;

			// Міняємо місцями 0-й та 1-й рядки
			Change(q, 0, 1, colCount);

			// Перевіряємо, чи перемістилися значення
			Assert::AreEqual(4, q[0][0]);
			Assert::AreEqual(5, q[0][1]);
			Assert::AreEqual(6, q[0][2]);

			Assert::AreEqual(1, q[1][0]);
			Assert::AreEqual(2, q[1][1]);
			Assert::AreEqual(3, q[1][2]);

			// Очищення пам'яті
			for (int i = 0; i < rowCount; i++) delete[] q[i];
			delete[] q;
		}

		// 2. Тест функції Calc (сума, кількість та заміщення 0)
		TEST_METHOD(Test_Calc)
		{
			const int rowCount = 2;
			const int colCount = 2;

			int** q = new int* [rowCount];
			for (int i = 0; i < rowCount; i++)
				q[i] = new int[colCount];

			q[0][0] = 4;  // Додатне парне -> ігнорується, залишається 4
			q[0][1] = 3;  // Непарне -> S += 3, k++, стає 0
			q[1][0] = -2; // Від'ємне -> S += (-2), k++, стає 0
			q[1][1] = 5;  // Непарне -> S += 5, k++, стає 0

			int S = 0, k = 0;
			Calc(q, rowCount, colCount, S, k);

			Assert::AreEqual(6, S);
			Assert::AreEqual(3, k);

			Assert::AreEqual(4, q[0][0]); // Не змінилося
			Assert::AreEqual(0, q[0][1]); // Замінено на 0
			Assert::AreEqual(0, q[1][0]); // Замінено на 0
			Assert::AreEqual(0, q[1][1]); // Замінено на 0

			for (int i = 0; i < rowCount; i++) delete[] q[i];
			delete[] q;
		}

		// 3. Тест функції Sort (сортування рядків)
		TEST_METHOD(Test_Sort)
		{
			const int rowCount = 2;
			const int colCount = 4;

			int** q = new int* [rowCount];
			for (int i = 0; i < rowCount; i++)
				q[i] = new int[colCount];

			q[0][0] = 10; q[0][1] = 0; q[0][2] = 0; q[0][3] = 0;
			q[1][0] = 20; q[1][1] = 0; q[1][2] = 0; q[1][3] = 0;

			Sort(q, rowCount, colCount);

			Assert::AreEqual(20, q[0][0]);
			Assert::AreEqual(10, q[1][0]);

			for (int i = 0; i < rowCount; i++) delete[] q[i];
			delete[] q;
		}
	};
}