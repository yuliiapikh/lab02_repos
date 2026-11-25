#pragma once
#include <string>

// Спеціальності: КН – «Комп’ютерні науки», IN – «Інформатика»,
// ME – «Математика та економіка», FI – «Фізика та інформатика»,
// TN – «Трудове навчання»
enum Spec { KN, IN, ME, FI, TN };

struct Student
{
    std::string prizv;      // прізвище
    int         kurs;       // курс (ціле число)
    Spec        spec;       // спеціальність (перелік)
    int         fizyka;     // оцінка з фізики
    int         matematyka; // оцінка з математики
    union                   // третя оцінка – залежить від спеціальності
    {
        int prog;           // KN        – оцінка з програмування
        int chysl;          // IN        – оцінка з чисельних методів
        int ped;            // ME, FI, TN – оцінка з педагогіки
    };
};

std::size_t Utf8Length(const std::string& s);                   // довжина в символах
std::string PadRight(const std::string& s, const std::size_t w); // доповнення пробілами справа
std::string PadLeft(const std::string& s, const std::size_t w);  // доповнення пробілами зліва
std::string PadCenter(const std::string& s, const std::size_t w);// центрування

std::string SpecName(const Spec spec);          // назва спеціальності
int         ThirdGrade(const Student& st);      // третя оцінка (з об’єднання)
double      AverageGrade(const Student& st);    // середній бал студента

int         ReadInt(const std::string& prompt, const int lo, const int hi);
std::string ReadSurname(const std::string& prompt);
Spec        ReadSpec();
void        Create(Student* s, const int N);    // формування масиву з клавіатури

void PrintTable(const Student* s, const int N); // таблиця із заголовком і шапкою
void PrintIndexSorted(const Student* s, const int* I, const int N); // вивід за індексним масивом

int CompareUkr(const std::string& a, const std::string& b);
// порівняння за ключами (курс, назва спеціальності, прізвище); результат: -1, 0, 1
int CompareKeys(const int kurs1, const Spec spec1, const std::string& prizv1,
    const int kurs2, const Spec spec2, const std::string& prizv2,
    const bool prizvDescending);
int ComparePhysical(const Student& a, const Student& b); // прізвище – за спаданням
int CompareIndexed(const Student& a, const Student& b);  // прізвище – за зростанням

void Sort(Student* s, const int N);
bool IsSortedPhysically(const Student* s, const int N);

int* IndexSort(const Student* s, const int N);   // повертає новий масив (delete[] – в місці виклику)

int BinSearch(const Student* s, const int N,
    const std::string& prizv, const int kurs, const Spec spec);
int IndexBinSearch(const Student* s, const int* I, const int N,
    const std::string& prizv, const int kurs, const Spec spec);
