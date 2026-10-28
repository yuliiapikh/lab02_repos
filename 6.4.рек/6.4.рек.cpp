// Лабораторна робота № 6.4
// Варіант 22
// Спосіб 2: рекурсивні функції
// Динамічний масив дійсних чисел: сума додатних, добуток між max|a| і min|a|,
// впорядкування "непарних" елементів за спаданням

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

void Create(double* a, const int size, const double Low, const double High, int i)
{
	if (i < size)
	{
		a[i] = Low + (High - Low) * rand() / RAND_MAX;
		Create(a, size, Low, High, i + 1);
	}
}

void Print(const double* a, const int size, int i)
{
	if (i < size)
	{
		cout << setw(8) << fixed << setprecision(2) << a[i];
		Print(a, size, i + 1);
	}
	else
		cout << endl;
}

double SumPositive(const double* a, const int size, int i)
{
	if (i >= size)
		return 0;
	if (a[i] > 0)
		return a[i] + SumPositive(a, size, i + 1);
	return SumPositive(a, size, i + 1);
}

int IndexMaxAbs(const double* a, const int size, int i)
{
	if (i == size - 1)
		return i;
	int k = IndexMaxAbs(a, size, i + 1);
	return fabs(a[i]) >= fabs(a[k]) ? i : k;
}

int IndexMinAbs(const double* a, const int size, int i)
{
	if (i == size - 1)
		return i;
	int k = IndexMinAbs(a, size, i + 1);
	return fabs(a[i]) <= fabs(a[k]) ? i : k;
}

// добуток елементів, розташованих строго між індексами left та right (left <= right)
double ProductBetween(const double* a, const int left, const int right)
{
	if (left + 1 >= right)
		return 1;
	return a[left + 1] * ProductBetween(a, left + 1, right);
}

void Swap(double& x, double& y)
{
	double t = x;
	x = y;
	y = t;
}

// ставить на позицію i найбільший серед "непарних" елементів a[j], a[j+2], ...
void MoveMaxOddToPosition(double* a, const int size, const int i, int j)
{
	if (j < size)
	{
		if (a[j] > a[i])
			Swap(a[i], a[j]);
		MoveMaxOddToPosition(a, size, i, j + 2);
	}
}

// "непарні" елементи - елементи з непарними номерами (індекси 1, 3, 5, ...)
void SortOddDescending(double* a, const int size, int i)
{
	if (i < size)
	{
		MoveMaxOddToPosition(a, size, i, i + 2);
		SortOddDescending(a, size, i + 2);
	}
}

int main()
{
	srand((unsigned)time(NULL));

	int n;
	cout << "n = "; cin >> n;
	if (n <= 0)
	{
		cout << "n must be > 0" << endl;
		return 0;
	}

	double* a = new double[n];
	Create(a, n, -10, 10, 0);

	cout << "Array:" << endl;
	Print(a, n, 0);

	cout << "Sum of positive elements = " << SumPositive(a, n, 0) << endl;

	int iMax = IndexMaxAbs(a, n, 0);
	int iMin = IndexMinAbs(a, n, 0);
	int left = iMax < iMin ? iMax : iMin;
	int right = iMax < iMin ? iMin : iMax;
	if (right - left > 1)
		cout << "Product between max|a| and min|a| = " << ProductBetween(a, left, right) << endl;
	else
		cout << "There are no elements between max|a| and min|a|" << endl;

	SortOddDescending(a, n, 1);
	cout << "Modified array:" << endl;
	Print(a, n, 0);

	delete[] a;
	return 0;
}
