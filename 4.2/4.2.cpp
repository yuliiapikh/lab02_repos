// Lab_04_2.cpp
// Піх Юлія
// Лабораторна робота № 4.2
// Табуляція функції, заданої формулою: функція однієї змінної
// Варіант 22

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
	double x, xp, xk, dx, A, B, y;
	cout << "xp = "; cin >> xp;
	cout << "xk = "; cin >> xk;
	cout << "dx = "; cin >> dx;

	cout << fixed;
	cout << "---------------------------" << endl;
	cout << "|" << setw(5) << "x" << " |"
		<< setw(7) << "y" << " |" << endl;
	cout << "---------------------------" << endl;

	x = xp;
	while (x <= xk)
	{
		A = abs(pow(x,3));
		if (x < -1)
			B = abs(2+x)+sin(x)* sin(x);
		else
			if (x > 0.1)
				B = exp(cos(x))+log10((1/x)+1);
			else
				B = atan(pow(x,3)+1)+1;
		y = A + B;

		cout << "|" << setw(7) << setprecision(2) << x
			<< " |" << setw(10) << setprecision(3) << y
			<< " |" << endl;

		x += dx;
	}
	cout << "---------------------------" << endl;
	return 0;
}
