// Lab_7_2
// Піх Юлія
// Лабораторна робота № 7.2.іт
// Опрацювання багатовимірних масивів ітераційними способами.
// Варіант 22

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** a, const int n, const int Low, const int High);
void Print(int** a, const int n);
void SearchMaxAbove(int** a, const int n, int& maxVal, int& maxI, int& maxJ);
void SearchMinBelow(int** a, const int n, int& minVal, int& minI, int& minJ);
void Swap(int** a, const int i1, const int j1, const int i2, const int j2);
int Sum(const int x, const int y);

int main()
{
	srand((unsigned)time(NULL));

	int Low = -15;
	int High = 25;
	int n;
	cout << "n = "; cin >> n;
	if (n < 2)
	{
		cout << "n must be >= 2" << endl;
		return 0;
	}

	int** a = new int* [n];
	for (int i = 0; i < n; i++)
		a[i] = new int[n];

	Create(a, n, Low, High);
	Print(a, n);

	int maxVal, maxI, maxJ;   // максимум над головною діагоналлю та його індекси
	int minVal, minI, minJ;   // мінімум під головною діагоналлю та його індекси

	SearchMaxAbove(a, n, maxVal, maxI, maxJ);
	SearchMinBelow(a, n, minVal, minI, minJ);

	cout << "max above = " << maxVal << " [" << maxI << "][" << maxJ << "]" << endl;
	cout << "min below = " << minVal << " [" << minI << "][" << minJ << "]" << endl;

	Swap(a, maxI, maxJ, minI, minJ);

	cout << "sum = " << Sum(maxVal, minVal) << endl;
	Print(a, n);

	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[] a;
	return 0;
}

void Create(int** a, const int n, const int Low, const int High)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = Low + rand() % (High - Low + 1);
}

void Print(int** a, const int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(4) << a[i][j];
		cout << endl;
	}
	cout << endl;
}

// пошук максимального елемента над головною діагоналлю (j > i)
void SearchMaxAbove(int** a, const int n, int& maxVal, int& maxI, int& maxJ)
{
	maxI = 0;
	maxJ = 1;
	maxVal = a[0][1];
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (a[i][j] > maxVal)
			{
				maxVal = a[i][j];
				maxI = i;
				maxJ = j;
			}
}

// пошук мінімального елемента під головною діагоналлю (j < i)
void SearchMinBelow(int** a, const int n, int& minVal, int& minI, int& minJ)
{
	minI = 1;
	minJ = 0;
	minVal = a[1][0];
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
			if (a[i][j] < minVal)
			{
				minVal = a[i][j];
				minI = i;
				minJ = j;
			}
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
