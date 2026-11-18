//////////////////////////////////////////////////////////////////////////////
// Lab_9_1.cpp
// головний файл проекту – функція main

#include <iostream>
#include <math.h>
#include <iomanip>

#include "dod.h"
#include "sum.h"
#include "var.h"

using namespace std;

using namespace nsDod;
using namespace nsSum;
using namespace nsVar;

int main()
{
    cout << "x_p = "; cin >> x_p;
    cout << "x_k = "; cin >> x_k;
    cout << "dx  = "; cin >> dx;
    cout << "e   = "; cin >> e;
    cout << endl;

    // заголовок і шапка таблиці
    cout << "--------------------------------------------------" << endl;
    cout << "|    Table of values for the function exp(-x)    |" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << setw(11) << "x |"
        << setw(15) << "exp(-x) |"
        << setw(15) << "S |"
        << setw(9) << "n |" << endl;
    cout << "--------------------------------------------------" << endl;

    x = x_p;
    while (x <= x_k) {
        sum();                          // виклик процедури обчислення суми

        cout << fixed << setprecision(6)
            << setw(10) << x << "|"
            << setw(14) << exp(-x) << "|"
            << setw(14) << s << "|"
            << setw(8) << n << "|" << endl;  // форматний вивід

        x += dx;
    }
    cout << "--------------------------------------------------" << endl;

    cin.get(); cin.get();
    return 0;
}