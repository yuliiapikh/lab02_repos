#include <iostream>
#include <time.h>
#include <iomanip>

using namespace std;

bool Suitable(const int x)// критерій: Всі, крім від'ємних або непарних
{
	return x >= 0 && x % 2 == 0;
}

void Create(int* t, const int size, const int Low, const int High, int i)
{
	if (i < size)
	{
		t[i] = Low + rand() % (High - Low + 1);
		Create(t, size, Low, High, i + 1);
	}
}

void Print(const int* t, const int size, int i)
{
	if (i < size)
	{
		cout << setw(4) << t[i];
		Print(t, size, i + 1);
	}
	else
		cout << endl;
}

int Count(const int* t, const int size, int i)
{
	if (i >= size)
		return 0;
	if (Suitable(t[i]))
		return 1 + Count(t, size, i + 1);
	return Count(t, size, i + 1);
}

int Sum(const int* t, const int size, int i)
{
	if (i >= size)
		return 0;
	if (Suitable(t[i]))
		return t[i] + Sum(t, size, i + 1);
	return Sum(t, size, i + 1);
}

void Replace(int* t, const int size, int i)
{
	if (i < size)
	{
		if (Suitable(t[i]))
			t[i] = 0;
		Replace(t, size, i + 1);
	}
}

int main()
{
	srand((unsigned)time(NULL));

	const int n = 25;
	int t[n];
	int Low = -5;
	int High = 12;
	Create(t, n, Low, High, 0);

	cout << "Started massiv:\n";
	Print(t, n, 0);

	int totalCount = Count(t, n, 0);
	int totalSum = Sum(t, n, 0);
	cout << "Sum of elements = " << totalSum << endl;
	cout << "Count of elements = " << totalCount << endl;

	Replace(t, n, 0);

	cout << "Modified massiv:\n";
	Print(t, n, 0);

	return 0;
}
