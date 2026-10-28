// Лабораторна робота № 6.3
// Варіант 22
// Спосіб 2: рекурсивні функції (звичайна функція та шаблон)
// Сума від'ємних елементів масиву чисел

#include <iostream>
#include <iomanip>

using namespace std;

int SumNegative(const int* a, const int size, int i);

template <typename T>
T SumNegative(const T* a, const int size, int i);

template <typename T>
void Print(const T* a, const int size, int i);

int main()
{
	const int n = 10;

	int a[n] = { 1, -2, 3, -4, 5, -6, 7, -8, 9, -10 };
	cout << "int array:" << endl;
	Print(a, n, 0);
	int s1 = SumNegative(a, n, 0);
	cout << "SumNegative(a, n) = " << s1 << endl;
	int s2 = SumNegative<int>(a, n, 0);
	cout << "SumNegative<int>(a, n) = " << s2 << endl;

	double b[n] = { 1.5, -2.5, 3.5, -4.5, 5.5, -6.5, 7.5, -8.5, 9.5, -10.5 };
	cout << "double array:" << endl;
	Print(b, n, 0);
	double s3 = SumNegative<double>(b, n, 0);
	cout << "SumNegative<double>(b, n) = " << s3 << endl;

	return 0;
}

int SumNegative(const int* a, const int size, int i)
{
	if (i >= size)
		return 0;
	if (a[i] < 0)
		return a[i] + SumNegative(a, size, i + 1);
	return SumNegative(a, size, i + 1);
}

template <typename T>
T SumNegative(const T* a, const int size, int i)
{
	if (i >= size)
		return T();
	if (a[i] < T())
		return a[i] + SumNegative<T>(a, size, i + 1);
	return SumNegative<T>(a, size, i + 1);
}

template <typename T>
void Print(const T* a, const int size, int i)
{
	if (i < size)
	{
		cout << setw(7) << a[i];
		Print(a, size, i + 1);
	}
	else
		cout << endl;
}
