// Лабораторна робота № 6.2
// Варіант 22
// Спосіб 1: ітераційні функції
// Сума парних елементів одновимірного масиву

#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

void Create(int* a, const int size, const int Low, const int High)
{
	for (int i = 0; i < size; i++)
		a[i] = Low + rand() % (High - Low + 1);
}

void Print(const int* a, const int size)
{
	for (int i = 0; i < size; i++)
		cout << setw(4) << a[i];
	cout << endl;
}

int SumEven(const int* a, const int size)
{
	int S = 0;
	for (int i = 0; i < size; i++)
		if (a[i] % 2 == 0)
			S += a[i];
	return S;
}

int main()
{
	srand((unsigned)time(NULL));

	const int n = 20;
	const int Low = -10;
	const int High = 20;
	int a[n];

	Create(a, n, Low, High);

	cout << "Array:" << endl;
	Print(a, n);

	cout << "Sum of even elements = " << SumEven(a, n) << endl;

	return 0;
}
