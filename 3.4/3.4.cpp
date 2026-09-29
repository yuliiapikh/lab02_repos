// Lab_03.4.cpp
// Піх Юлія
// Лабораторна робота № 3.4
// Розгалуження, задане плоскою фігурою.
// Варіант 22

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	double x; // вхідний аргумент
	double y; // вхідний параметр
	double R; // вхідний параметр

	cout << "x = "; cin >> x;
	cout << "y = "; cin >> y;
	cout << "R = "; cin >> R;

	// розгалуження в повній формі
	if ((x*x+y*y==R*R && x<=0 && y>=0 ) ||
		(y <= 0 && y >= -2*x && y >= -2*x-2*R))
		cout << "yes" << endl;
	else
		cout << "no" << endl;
	cin.get();
	return 0;
}