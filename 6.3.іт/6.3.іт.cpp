// Лабораторна робота № 6.3
// Варіант 22
// Спосіб 1: ітераційні функції (звичайна функція та шаблон)
// Сума від'ємних елементів масиву чисел

#include <iostream>
#include <iomanip>

using namespace std;

int SumNegative(const int* a, const int size);

template <typename T>
T SumNegative(const T* a, const int size);

template <typename T>
void Print(const T* a, const int size);

int main()
{
	const int n = 10;

	int a[n] = { 1, -2, 3, -4, 5, -6, 7, -8, 9, -10 };
	cout << "int array:" << endl;
	Print(a, n);
	int s1 = SumNegative(a, n);
	cout << "SumNegative(a, n) = " << s1 << endl;
	int s2 = SumNegative<int>(a, n);
	cout << "SumNegative<int>(a, n) = " << s2 << endl;

	double b[n] = { 1.5, -2.5, 3.5, -4.5, 5.5, -6.5, 7.5, -8.5, 9.5, -10.5 };
	cout << "double array:" << endl;
	Print(b, n);
	double s3 = SumNegative<double>(b, n);
	cout << "SumNegative<double>(b, n) = " << s3 << endl;

	return 0;
}

int SumNegative(const int* a, const int size)
{
	int s = 0;
	for (int i = 0; i < size; i++)
		if (a[i] < 0)
			s += a[i];
	return s;
}

template <typename T>
T SumNegative(const T* a, const int size)
{
	T s = T(); // присвоїли нульове значення
	for (int i = 0; i < size; i++)
		if (a[i] < T())
			s += a[i];
	return s;
}

template <typename T>
void Print(const T* a, const int size)
{
	for (int i = 0; i < size; i++)
		cout << setw(7) << a[i];
	cout << endl;
}
