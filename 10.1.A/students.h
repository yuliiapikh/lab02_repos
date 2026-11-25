#pragma once
#include <string>

// Спеціальності: КН – «Комп’ютерні науки», IN – «Інформатика»,
// ME – «Математика та економіка», FI – «Фізика та інформатика»,
// TN – «Трудове навчання»
enum Spec { KN, IN, ME, FI, TN };

struct Student {
    std::string prizv;
    int kurs = 1;
    Spec spec = KN;
    int fizyka = 0;
    int matematyka = 0;
    int informatyka = 0;
};

std::size_t Utf8Length(const std::string& s);                   // довжина в символах
std::string PadRight(const std::string& s, const std::size_t w); // доповнення пробілами справа
std::string PadLeft(const std::string& s, const std::size_t w);  // доповнення пробілами зліва
std::string PadCenter(const std::string& s, const std::size_t w);// центрування

std::string SpecName(const Spec spec);          // назва спеціальності
double      AverageGrade(const Student& st);    // середній бал студента

int         ReadInt(const std::string& prompt, const int lo, const int hi);
std::string ReadSurname(const std::string& prompt);
Spec        ReadSpec();
void        Create(Student* s, const int N);    // формування масиву з клавіатури

void PrintTable(const Student* s, const int N); // таблиця із заголовком і шапкою

bool   HasNoThrees(const Student& st);               // всі оцінки 4 або 5
int    CountNoThrees(const Student* s, const int N); // 1) кількість студентів без трійок
bool   HasAverageBelow4(const Student& st);          // середній бал < 4
double PercentAverageBelow4(const Student* s, const int N); // 2) процент із середнім < 4
