// Lab_04_4.cpp
// Піх Юлія
// Лабораторна робота № 4.4
// Табуляція функції, заданої графіком
// Варіант 22

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
	double x, y, R, xp, xk, dx;

	cout << "R = "; cin >> R;
	cout << "xp = "; cin >> xp;
	cout << "xk = "; cin >> xk;
	cout << "dx = "; cin >> dx;
	cout << fixed;
	cout << "-----------------------" << endl;
	cout << "|" << setw(5) << "x" << " |"
		<< setw(7) << "y" << " |" << endl;
	cout << "-----------------------" << endl;
	x = xp;
	while (x <= xk)
	{
		if (x <= -8)
			y = -R;
		else
			if (-8 < x && x <= -R)
				y = R * (x + R) / (8 - R);
			else
				if (-R < x && x <= R)
					y = -sqrt(R * R - x * x);
				else
					if (R < x && x <= 5)
						y = 2 * (x - R) / (5 - R);
					else
						y = 3;
	cout << "|" << setw(7) << setprecision(2) << x
			<< " |" << setw(10) << setprecision(3) << y
			<< " |" << endl;
	x += dx;
	}
	cout << "-----------------------" << endl;
	return 0;
}