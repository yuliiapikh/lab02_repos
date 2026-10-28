// Лабораторна робота № 6.4
// Варіант 22
// Спосіб 1: ітераційні функції
// Динамічний масив дійсних чисел: сума додатних, добуток між max|a| і min|a|,
// впорядкування "непарних" елементів за спаданням

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

void Create(double* a, const int size, const double Low, const double High)
{
	for (int i = 0; i < size; i++)
		a[i] = Low + (High - Low) * rand() / RAND_MAX;
}

void Print(const double* a, const int size)
{
	for (int i = 0; i < size; i++)
		cout << setw(8) << fixed << setprecision(2) << a[i];
	cout << endl;
}

double SumPositive(const double* a, const int size)
{
	double s = 0;
	for (int i = 0; i < size; i++)
		if (a[i] > 0)
			s += a[i];
	return s;
}

int IndexMaxAbs(const double* a, const int size)
{
	int imax = 0;
	for (int i = 1; i < size; i++)
		if (fabs(a[i]) > fabs(a[imax]))
			imax = i;
	return imax;
}

int IndexMinAbs(const double* a, const int size)
{
	int imin = 0;
	for (int i = 1; i < size; i++)
		if (fabs(a[i]) < fabs(a[imin]))
			imin = i;
	return imin;
}

// добуток елементів, розташованих строго між індексами left та right (left <= right)
double ProductBetween(const double* a, const int left, const int right)
{
	double p = 1;
	for (int i = left + 1; i < right; i++)
		p *= a[i];
	return p;
}

void Swap(double& x, double& y)
{
	double t = x;
	x = y;
	y = t;
}

// "непарні" елементи - елементи з непарними номерами
void SortOddDescending(double* a, const int size)
{
	for (int i = 1; i < size; i += 2)
		for (int j = i + 2; j < size; j += 2)
			if (a[j] > a[i])
				Swap(a[i], a[j]);
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
	Create(a, n, -10, 10);

	cout << "Array:" << endl;
	Print(a, n);

	cout << "Sum of positive elements = " << SumPositive(a, n) << endl;

	int iMax = IndexMaxAbs(a, n);
	int iMin = IndexMinAbs(a, n);
	int left = iMax < iMin ? iMax : iMin;
	int right = iMax < iMin ? iMin : iMax;
	if (right - left > 1)
		cout << "Product between max|a| and min|a| = " << ProductBetween(a, left, right) << endl;
	else
		cout << "There are no elements between max|a| and min|a|" << endl;

	SortOddDescending(a, n);
	cout << "Modified array:" << endl;
	Print(a, n);

	delete[] a;
	return 0;
}
