#include <iostream>
#include <iomanip>
#include "students.h"
#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif
using namespace std;

void SetupConsole();  // забезпечення відображення кирилиці

int main()
{
    SetupConsole();

    const int maxN = 1000;
    int N = ReadInt("Введіть кількість студентів N (1-1000): ", 1, maxN);
    cout << endl;

    Student* s = new Student[N]();   // динамічний масив структур

    Create(s, N);
    PrintTable(s, N);

    int    k = CountNoThrees(s, N);
    double proc = PercentAverageBelow4(s, N);

    cout << "Кількість студентів, які вчаться без трійок "
        "(на \"відмінно\" і \"добре\"): " << k << endl;
    cout << "Процент студентів, у яких середній бал менший за 4: "
        << fixed << setprecision(2) << proc << "%" << endl;

    delete[] s;
    return 0;
}

void SetupConsole()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);         // кодова сторінка UTF-8 в потік вводу
    SetConsoleOutputCP(CP_UTF8);   // кодова сторінка UTF-8 в потік виводу
#endif
}
