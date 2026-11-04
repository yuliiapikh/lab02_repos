// Lab_7_1
// Лабораторна робота № 7.1 (рекурсивний спосіб)
// Пошук заданих елементів та впорядкування рядків матриці.
// Варіант 22

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** q, const int rowCount, const int colCount, const int Low, const int High, int i, int j);
void Print(int** q, const int rowCount, const int colCount, int i, int j);
void Sort(int** q, const int rowCount, const int colCount, int i0, int i1);
void Change(int** q, const int row1, const int row2, const int colCount, int j);
void Calc(int** q, const int rowCount, const int colCount, int& S, int& k, int i, int j);

int main()
{
	srand((unsigned)time(NULL));

	int Low = -26;
	int High = 23;
	int rowCount = 8;
	int colCount = 6;
	int** q = new int* [rowCount];

	for (int i = 0; i < rowCount; i++)
		q[i] = new int[colCount];

	Create(q, rowCount, colCount, Low, High, 0, 0);
	cout << endl;
	Print(q, rowCount, colCount, 0, 0);
	cout << endl;
	Sort(q, rowCount, colCount, 0, 0);
	Print(q, rowCount, colCount, 0, 0);
	cout << endl;

	int S = 0;
	int k = 0;

	Calc(q, rowCount, colCount, S, k, 0, 0);

	cout << "S = " << S << endl;
	cout << "k = " << k << endl;

	cout << endl;
	Print(q, rowCount, colCount, 0, 0);
	cout << endl;

	for (int i = 0; i < rowCount; i++)
		delete[] q[i];
	delete[] q;
	return 0;
}

// i - номер поточного рядка, j - номер поточного стовпчика
void Create(int** q, const int rowCount, const int colCount, const int Low, const int High, int i, int j)
{
	if (i < rowCount)
	{
		if (j < colCount)
		{
			q[i][j] = Low + rand() % (High - Low + 1);
			Create(q, rowCount, colCount, Low, High, i, j + 1);
		}
		else
			Create(q, rowCount, colCount, Low, High, i + 1, 0);
	}
}

void Print(int** q, const int rowCount, const int colCount, int i, int j)
{
	if (i < rowCount)
	{
		if (j < colCount)
		{
			cout << setw(4) << q[i][j];
			Print(q, rowCount, colCount, i, j + 1);
		}
		else
		{
			cout << endl;
			Print(q, rowCount, colCount, i + 1, 0);
		}
	}
}

// i0 - номер проходу "бульбашки", i1 - номер поточної пари рядків
void Sort(int** q, const int rowCount, const int colCount, int i0, int i1)
{
	if (i0 < rowCount - 1)
	{
		if (i1 < rowCount - i0 - 1)
		{
			if ((q[i1][0] < q[i1 + 1][0])
				||
				(q[i1][0] == q[i1 + 1][0] &&
					q[i1][1] > q[i1 + 1][1])
				||
				(q[i1][0] == q[i1 + 1][0] &&
					q[i1][1] == q[i1 + 1][1] &&
					q[i1][3] < q[i1 + 1][3]))
				Change(q, i1, i1 + 1, colCount, 0);
			Sort(q, rowCount, colCount, i0, i1 + 1);
		}
		else
			Sort(q, rowCount, colCount, i0 + 1, 0);
	}
}

// j - номер поточного стовпчика
void Change(int** q, const int row1, const int row2, const int colCount, int j)
{
	if (j < colCount)
	{
		int tmp = q[row1][j];
		q[row1][j] = q[row2][j];
		q[row2][j] = tmp;
		Change(q, row1, row2, colCount, j + 1);
	}
}

// S та k занулюються в main перед першим викликом
void Calc(int** q, const int rowCount, const int colCount, int& S, int& k, int i, int j)
{
	if (i < rowCount)
	{
		if (j < colCount)
		{
			if (!((q[i][j] % 2 == 0) && (q[i][j] > 0)))// критерій: усі, крім додатних парних
			{
				S += q[i][j];
				k++;
				q[i][j] = 0;
			}
			Calc(q, rowCount, colCount, S, k, i, j + 1);
		}
		else
			Calc(q, rowCount, colCount, S, k, i + 1, 0);
	}
}