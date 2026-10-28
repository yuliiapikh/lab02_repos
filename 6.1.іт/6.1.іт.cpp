#include <iostream>
#include <time.h>
#include <iomanip>

using namespace std;

void Create(int* t, const int size, const int Low, const int High)
{
	for (int i = 0; i < size; i++)
		t[i] = Low + rand() % (High - Low + 1);
}

void Print(int* t, const int size)
{
	for (int i = 0; i < size; i++)
		cout << setw(4) << t[i];
	cout << endl;
}

int Count(const int t[], const int size)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		// Всі, крім від'ємних або непарних
		if (t[i] >= 0 && t[i] % 2 == 0)
		{
			count++;
		}
	}
	return count;
}

int Sum(int* t, const int size)
{
	int S = 0;
	for (int i = 0; i < size; i++) {
		if (t[i] >= 0 && t[i] % 2 == 0) {
			S += t[i];
		}
	}
	return S;
}

void Replace(int t[], const int size)
{
	for (int i = 0; i < size; i++)
	{
		if (t[i] >= 0 && t[i] % 2 == 0)
		{
			t[i] = 0;
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));

	const int n = 25;
	int t[n];
	int Low = -5;
	int High = 12;
	Create(t, n, Low, High);

	cout << "Started massiv:\n";
	Print(t, n);

	int totalCount = Count(t, n);
	int totalSum = Sum(t, n);
	cout << "Sum of elements = " << totalSum << endl;
	cout << "Count of elements = " << totalCount << endl;

	Replace(t, n);

	cout << "Modified massiv:\n";
	Print(t, n);

	return 0;
}