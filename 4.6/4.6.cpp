// Lab_04_6.cpp
// Піх Юлія
// Лабораторна робота № 4.6
// Вкладені цикли
// Варіант 22

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	double P1, P2, B;
	int n, k;

	cout << setprecision(12);

	// 1) while
	P1 = 1;
	k = 1;
	while (k <= 20)
	{
		P2 = 1;
		n = 1;
		while (n <= 25 - k)
		{
			B = (double)(k - n) / (k + n) + 1;
			P2 *= B;
			n++;
		}
		P1 *= P2;
		k++;
	}
	cout << "while      : " << P1 << endl;

	// 2) do-while
	P1 = 1;
	k = 1;
	do
	{
		P2 = 1;
		n = 1;
		do
		{
			B = (double)(k - n) / (k + n) + 1;
			P2 *= B;
			n++;
		} while (n <= 25 - k);
		P1 *= P2;
		k++;
	} while (k <= 20);
	cout << "do-while   : " << P1 << endl;

	// 3) for (і++)
	P1 = 1;
	for (k = 1; k <= 20; k++)
	{
		P2 = 1;
		for (n = 1; n <= 25 - k; n++)
		{
			B = (double)(k - n) / (k + n) + 1;
			P2 *= B;
		}
		P1 *= P2;
	}
	cout << "for (++)   : " << P1 << endl;

	// 4) for (і--)
	P1 = 1;
	for (k = 20; k >= 1; k--)
	{
		P2 = 1;
		for (n = 25 - k; n >= 1; n--)
		{
			B = (double)(k - n) / (k + n) + 1;
			P2 *= B;
		}
		P1 *= P2;
	}
	cout << "for (--)   : " << P1 << endl;

	return 0;
}