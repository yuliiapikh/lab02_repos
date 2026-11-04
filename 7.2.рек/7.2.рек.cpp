// Lab_7_2
// Піх Юлія
// Лабораторна робота № 7.2.рек
// Опрацювання багатовимірних масивів рекурсивними способами.
// Варіант 22

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void CreateRow(int** a, const int rowNo, const int N, const int Low,
	const int High, int colNo)
{
	a[rowNo][colNo] = Low + rand() % (High - Low + 1);
	if (colNo < N - 1)
		CreateRow(a, rowNo, N, Low, High, colNo + 1);
}

void CreateRows(int** a, const int N, const int Low, const int High, int rowNo)
{
	CreateRow(a, rowNo, N, Low, High, 0);
	if (rowNo < N - 1)
		CreateRows(a, N, Low, High, rowNo + 1);
}

void PrintRow(int** a, const int rowNo, const int N, int colNo)
{
	cout << setw(4) << a[rowNo][colNo];
	if (colNo < N - 1)
		PrintRow(a, rowNo, N, colNo + 1);
	else
		cout << endl;
}

void PrintRows(int** a, const int N, int rowNo)
{
	PrintRow(a, rowNo, N, 0);
	if (rowNo < N - 1)
		PrintRows(a, N, rowNo + 1);
	else
		cout << endl;
}

// пошук максимального елемента в рядку i над головною діагоналлю: j від i+1 до N-1
void SearchMaxAboveRow(int** a, const int N, const int i, int j,
	int& maxVal, int& maxI, int& maxJ)
{
	if (a[i][j] > maxVal)
	{
		maxVal = a[i][j];
		maxI = i;
		maxJ = j;
	}
	if (j < N - 1)
		SearchMaxAboveRow(a, N, i, j + 1, maxVal, maxI, maxJ);
}

// перегляд рядків від i до N-2
void SearchMaxAbove(int** a, const int N, int i,
	int& maxVal, int& maxI, int& maxJ)
{
	SearchMaxAboveRow(a, N, i, i + 1, maxVal, maxI, maxJ);
	if (i < N - 2)
		SearchMaxAbove(a, N, i + 1, maxVal, maxI, maxJ);
}

// пошук мінімального елемента в рядку i під головною діагоналлю: j від 0 до i-1
void SearchMinBelowRow(int** a, const int i, int j,
	int& minVal, int& minI, int& minJ)
{
	if (a[i][j] < minVal)
	{
		minVal = a[i][j];
		minI = i;
		minJ = j;
	}
	if (j < i - 1)
		SearchMinBelowRow(a, i, j + 1, minVal, minI, minJ);
}

// перегляд рядків від i до N-1
void SearchMinBelow(int** a, const int N, int i,
	int& minVal, int& minI, int& minJ)
{
	SearchMinBelowRow(a, i, 0, minVal, minI, minJ);
	if (i < N - 1)
		SearchMinBelow(a, N, i + 1, minVal, minI, minJ);
}

// обмін місцями двох елементів матриці
void Swap(int** a, const int i1, const int j1, const int i2, const int j2)
{
	int tmp = a[i1][j1];
	a[i1][j1] = a[i2][j2];
	a[i2][j2] = tmp;
}

int Sum(const int x, const int y)
{
	return x + y;
}

int main()
{
	srand((unsigned)time(NULL));

	int N;   // розмірність матриці (N x N)
	cout << "N = "; cin >> N;
	cout << endl;
	if (N < 2)
	{
		cout << "N must be >= 2" << endl;
		return 0;
	}

	int** a = new int* [N];
	for (int i = 0; i < N; i++)
		a[i] = new int[N];

	int Low = -15, High = 25;   // межі діапазону значень
	CreateRows(a, N, Low, High, 0);
	PrintRows(a, N, 0);

	// початкові значення: перші елементи над і під головною діагоналлю
	int maxI = 0, maxJ = 1, maxVal = a[0][1];
	int minI = 1, minJ = 0, minVal = a[1][0];

	SearchMaxAbove(a, N, 0, maxVal, maxI, maxJ);
	SearchMinBelow(a, N, 1, minVal, minI, minJ);

	cout << "max above = " << maxVal << " [" << maxI << "][" << maxJ << "]" << endl;
	cout << "min below = " << minVal << " [" << minI << "][" << minJ << "]" << endl;

	Swap(a, maxI, maxJ, minI, minJ);

	cout << "sum = " << Sum(maxVal, minVal) << endl;
	PrintRows(a, N, 0);

	for (int i = 0; i < N; i++)
		delete[] a[i];
	delete[] a;
	return 0;
}
