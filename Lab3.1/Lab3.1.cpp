// Lab3.1.cpp
// Піх Юлія
// Лабораторна робота № 3.1
// Розгалуження, задане формулою: функція однієї змінної.
// Варіант 22

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	double x; // вхідний параметр
	double y; // результат обчислення виразу
	double A; // проміжний результат - функціонально стала частина виразу
	double B; // проміжний результат - функціонально змінна частина виразу

	cout << "x= "; cin >> x;

	A = abs(pow(x, 3));

	// спосіб 1: розгалуження в скороченій формі
	if (x < -1)
		B = abs(2 + x) + sin(x) * sin(x);
	if (-1 <= x && x <= 1)
		B = atan(pow(x, 3) + 1) + 1;
	if (x > 1)
		B = exp(cos(x)) + log(1 / x + 1);

	y = A + B;
	cout << endl;
	cout << "1) y = " << y << endl;

	// спосіб 2: розгалуження в повній формі
	if (x < -1)
		B = abs(2 + x) + sin(x) * sin(x);
	else
		if (-1 <= x && x <= 1)
			B = atan(pow(x, 3) + 1) + 1;
		else
			B = exp(cos(x)) + log(1 / x + 1);
	y = A + B;
	cout << endl;
	cout << "2) y = " << y << endl;
	
	cin.get();
	return 0;
}