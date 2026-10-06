// Lab_04_7.cpp
// Піх Юлія
// Лабораторна робота № 4.7
// Обчислення суми ряду Тейлора за допомогою ітераційних циклів та рекурентних співвідношень
// Варіант 22

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	double xp, xk, x, dx, eps, a, R, S;
	int n;
	cout << "xp = "; cin >> xp;
	cout << "xk = "; cin >> xk;
	cout << "dx = "; cin >> dx;
	cout << "eps = "; cin >> eps;
	if (dx <= 0 || eps <= 0)
	{
		cout << "dx i eps must be > 0" << endl;
		return 1;
	}
	cout << fixed;
	cout << string(46, '-') << endl;
	cout << "|" << setw(8) << "x" << " |"
		<< setw(12) << "exp(-x)" << " |"
		<< setw(12) << "S" << " |"
		<< setw(5) << "n" << " |"
		<< endl;
	cout << string(46, '-') << endl;
	x = xp;
	while (x <= xk)
	{
		n = 0;   // номер першого доданка
		a = 1;   // перший доданок: (-1)^0 * x^0 / 0! = 1
		S = a;
		do {
			n++;
			R = -x / n;   // a(n) = a(n-1) * (-x) / n
			a *= R;
			S += a;
		} while (fabs(a) >= eps);
		cout << "|" << setw(8) << setprecision(2) << x << " |"
			<< setw(12) << setprecision(5) << exp(-x) << " |"
			<< setw(12) << setprecision(5) << S << " |"
			<< setw(5) << n + 1 << " |"   // кількість доданків (разом з першим)
			<< endl;
		x += dx;
	}
	cout << string(46, '-') << endl;
	return 0;
}