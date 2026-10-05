// Lab_04_3.cpp
// Піх Юлія
// Лабораторна робота № 4.3
// Табуляція функції, заданої формулою:функція з параметрами
// Варіант 22

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
	double x, xp, xk, dx, a, b, c, F, B;
	cout << "xp = "; cin >> xp;
	cout << "xk = "; cin >> xk;
	cout << "dx = "; cin >> dx;
	cout << "a = "; cin >> a;
	cout << "b = "; cin >> b;
	cout << "c = "; cin >> c;
	cout << fixed;
	cout << "-----------------------" << endl;
	cout << "|" << setw(5) << "x" << " |"
		<< setw(7) << "F" << " |" << endl;
	cout << "-----------------------" << endl;
	x = xp;
	while (x <= xk)
	{
		if (x + 5 < 0 && c == 0)
			B = (1/(a*x))-b;
		else
			if (x + 5 > 0 && c != 0)
				B = (x-a)/x;
			else
				B = (10*x)/(c-4);
		F = B;
		cout << "|" << setw(7) << setprecision(2) << x
			<< " |" << setw(10) << setprecision(3) << F
			<< " |" << endl;
		x += dx;
	}
	cout << "-----------------------" << endl;
	return 0;
}
