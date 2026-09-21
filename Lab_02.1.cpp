// Lab_02.cpp
// Піх Юлія
// Лабораторна робота № 2.
// Лінійні програми.
// Варіант 22.

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double Pi = 4 * atan(1.); // число пі
    double Alpha; // вхідний параметр
    //double z1; // результат обчислення 1-го виразу
    double z2; // результат обчислення 2-го виразу

    cout << "Alpha = "; cin >> Alpha;

    //z1 = cos(Alpha) + sin(Alpha) + cos(3 * Alpha) + sin(3 * Alpha);
    z2 = 2 * sqrt(2) * cos(Alpha) * sin((Pi / 4) + 2 * Alpha);

    cout << endl;
    //cout << "z1 = " << z1 << endl;
    cout << "z2 = " << z2 << endl;

    cin.get();
    return 0;
}