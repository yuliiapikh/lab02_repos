#include <iostream>
#include <string>
#include "students.h"
#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif
using namespace std;

void SetupConsole();                                  
void PrintMenu();                                      // вивід меню
void ReadSearchKeys(string& prizv, int& kurs, Spec& spec);   // ввід ключів пошуку
void PrintSearchResult(const bool found, const int position, const Student* st);

int main()
{
    SetupConsole();

    const int maxN = 1000;
    int N = ReadInt("Введіть кількість студентів N (1-1000): ", 1, maxN);

    Student* s = new Student[N]();   // динамічний масив структур
    bool filled = false;             // чи введено дані

    string prizv;
    int kurs;
    Spec spec;
    int pos;
    int* I;

    int menuItem;
    do {
        PrintMenu();
        menuItem = ReadInt("Введіть значення: ", 0, 6);
        cout << endl;

        if (menuItem >= 2 && menuItem <= 6 && !filled)
        {
            cout << "Спочатку введіть дані (пункт 1)." << endl;
            continue;
        }

        switch (menuItem)
        {
        case 1:
            Create(s, N);
            filled = true;
            break;
        case 2:
            PrintTable(s, N);
            break;
        case 3:
            Sort(s, N);
            cout << "Масив фізично впорядковано." << endl;
            PrintTable(s, N);
            break;
        case 4:
            I = IndexSort(s, N);
            PrintIndexSorted(s, I, N);
            delete[] I;
            break;
        case 5:
            if (!IsSortedPhysically(s, N))
            {
                cout << "Масив не впорядкований фізично за ключами варіанту. "
                    "Спочатку виконайте пункт 3." << endl;
                break;
            }
            ReadSearchKeys(prizv, kurs, spec);
            pos = BinSearch(s, N, prizv, kurs, spec);
            PrintSearchResult(pos != -1, pos + 1, pos != -1 ? &s[pos] : nullptr);
            break;
        case 6:
            ReadSearchKeys(prizv, kurs, spec);
            I = IndexSort(s, N);     // індексний масив – актуальний для поточних даних
            pos = IndexBinSearch(s, I, N, prizv, kurs, spec);
            PrintSearchResult(pos != -1, pos + 1, pos != -1 ? &s[I[pos]] : nullptr);
            delete[] I;
            break;
        case 0:
            break;
        }
    } while (menuItem != 0);

    delete[] s;
    return 0;
}

void SetupConsole()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

void PrintMenu()
{
    cout << endl << endl;
    cout << "Виберіть дію:" << endl << endl;
    cout << " [1] - введення даних з клавіатури" << endl;
    cout << " [2] - вивід даних на екран" << endl;
    cout << " [3] - фізичне впорядкування (курс, спеціальність - за зростанням," << endl;
    cout << "        прізвище - за спаданням)" << endl;
    cout << " [4] - індексне впорядкування та вивід даних (курс, спеціальність," << endl;
    cout << "        прізвище - за зростанням)" << endl;
    cout << " [5] - бінарний пошук студента у фізично впорядкованому масиві" << endl;
    cout << " [6] - бінарний пошук студента в індексно впорядкованому масиві" << endl << endl;
    cout << " [0] - вихід та завершення роботи програми" << endl << endl;
}

void ReadSearchKeys(string& prizv, int& kurs, Spec& spec)
{
    cout << "Введіть ключі пошуку:" << endl;
    prizv = ReadSurname("     прізвище: ");
    kurs = ReadInt("     курс (1-6): ", 1, 6);
    spec = ReadSpec();
    cout << endl;
}

void PrintSearchResult(const bool found, const int position, const Student* st)
{
    if (found)
        cout << "Студент навчається на вказаному курсі та спеціальності: "
        << st->prizv << ", " << st->kurs << " курс, " << SpecName(st->spec)
        << " (позиція у впорядкованому списку: " << position << ")." << endl;
    else
        cout << "Шуканого студента не знайдено." << endl;
}
