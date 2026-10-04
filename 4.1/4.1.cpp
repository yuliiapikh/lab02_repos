// Lab_04_1.cpp
// Піх Юлія
// Лабораторна робота № 4.1
// Цикли.
// Варіант 22

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int N, i;
	double S;
	cout << "N = "; cin >> N;
	S = 0;
	i = N;
	while (i <= 20)
	{
		S += (cos(1. * i) + sin(1. * i)) / (1 + cos(1. * i) * sin(1. * i));
		i++;
	}
	cout << S << endl;
	S = 0;
	i = N;
	if (N <= 20)
	{
		do {
			S += (cos(1. * i) + sin(1. * i)) / (1 + cos(1. * i) * sin(1. * i));
			i++;
		} while (i <= 20);
	}
	cout << S << endl;
	S = 0;
	for (i = N; i <= 20; i++)
	{
		S += (cos(1. * i) + sin(1. * i)) / (1 + cos(1. * i) * sin(1. * i));
	}
	cout << S << endl;
	S = 0;
	for (i = 20; i >= N; i--)
	{
		S += (cos(1. * i) + sin(1. * i)) / (1 + cos(1. * i) * sin(1. * i));
	}
	cout << S << endl;
	return 0;
}
