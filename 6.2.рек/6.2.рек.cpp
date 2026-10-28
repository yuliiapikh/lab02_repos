// Лабораторна робота № 6.2
// Варіант 22
// Спосіб 2: рекурсивні функції
// Сума парних елементів одновимірного масиву

#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

void Create(int* a, const int size, const int Low, const int High, int i)
{
	if (i < size)
	{
		a[i] = Low + rand() % (High - Low + 1);
		Create(a, size, Low, High, i + 1);
	}
}

void Print(const int* a, const int size, int i)
{
	if (i < size)
	{
		cout << setw(4) << a[i];
		Print(a, size, i + 1);
	}
	else
		cout << endl;
}

int SumEven(const int* a, const int size, int i)
{
	if (i >= size)
		return 0;
	if (a[i] % 2 == 0)
		return a[i] + SumEven(a, size, i + 1);
	return SumEven(a, size, i + 1);
}

int main()
{
	srand((unsigned)time(NULL));

	const int n = 20;
	const int Low = -10;
	const int High = 20;
	int a[n];

	Create(a, n, Low, High, 0);

	cout << "Array:" << endl;
	Print(a, n, 0);

	cout << "Sum of even elements = " << SumEven(a, n, 0) << endl;

	return 0;
}