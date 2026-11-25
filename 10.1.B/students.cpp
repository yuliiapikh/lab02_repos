#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef IN        // Windows.h визначає макрос IN, який конфліктує з елементом переліку IN
#endif
#include "students.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

size_t Utf8Length(const string& s)
{   // рахуємо всі байти, крім «продовжуючих» (10xxxxxx) – тобто символи UTF-8
    size_t n = 0;
    for (unsigned char c : s)
        if ((c & 0xC0) != 0x80)
            n++;
    return n;
}

string PadRight(const string& s, const size_t w)
{
    size_t len = Utf8Length(s);
    return len >= w ? s : s + string(w - len, ' ');
}

string PadLeft(const string& s, const size_t w)
{
    size_t len = Utf8Length(s);
    return len >= w ? s : string(w - len, ' ') + s;
}

string PadCenter(const string& s, const size_t w)
{
    size_t len = Utf8Length(s);
    if (len >= w) return s;
    size_t left = (w - len) / 2;
    return string(left, ' ') + s + string(w - len - left, ' ');
}

static string Trim(const string& s)
{   // вилучає пробіли та табуляції на початку й в кінці рядка
    size_t b = s.find_first_not_of(" \t");
    if (b == string::npos) return "";
    size_t e = s.find_last_not_of(" \t");
    return s.substr(b, e - b + 1);
}

static u32string ToCodePoints(const string& s)
{   // декодує рядок UTF-8 в послідовність кодів символів Unicode
    u32string r;
    for (size_t i = 0; i < s.size(); )
    {
        unsigned char c = s[i];
        int extra = c < 0x80 ? 0 : (c >> 5) == 6 ? 1 : (c >> 4) == 14 ? 2 : (c >> 3) == 30 ? 3 : -1;
        if (extra < 0 || i + extra >= s.size())   // некоректна послідовність
        {
            r.push_back(0xFFFD); i++; continue;
        }
        char32_t cp = extra == 0 ? c : (c & (0x3F >> extra));
        for (int k = 1; k <= extra; k++)
            cp = (cp << 6) | (static_cast<unsigned char>(s[i + k]) & 0x3F);
        r.push_back(cp);
        i += extra + 1;
    }
    return r;
}

string SpecName(const Spec spec)
{
    switch (spec)
    {
    case KN: return "Комп’ютерні науки";
    case IN: return "Інформатика";
    case ME: return "Математика та економіка";
    case FI: return "Фізика та інформатика";
    case TN: return "Трудове навчання";
    }
    return "";
}

int ThirdGrade(const Student& st)
{   // поле об’єднання, яке використовується, визначає спеціальність
    switch (st.spec)
    {
    case KN: return st.prog;
    case IN: return st.chysl;
    default: return st.ped;
    }
}

double AverageGrade(const Student& st)
{
    return (st.fizyka + st.matematyka + ThirdGrade(st)) / 3.0;
}

static bool GetInputLine(string& line)
{   // зчитує рядок в UTF-8. Для консолі Windows використовується ReadConsoleW,
    // бо cin/getline некоректно читають кирилицю при кодовій сторінці UTF-8
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(h, &mode))          // ввід з вікна консолі
    {
        wchar_t buf[1024];
        DWORD n = 0;
        if (!ReadConsoleW(h, buf, 1024, &n, NULL) || n == 0) return false;
        if (buf[0] == 0x1A) return false;  // Ctrl+Z – кінець вводу
        while (n > 0 && (buf[n - 1] == L'\r' || buf[n - 1] == L'\n')) n--;
        int len = WideCharToMultiByte(CP_UTF8, 0, buf, (int)n, NULL, 0, NULL, NULL);
        line.assign(len, '\0');
        if (len > 0)
            WideCharToMultiByte(CP_UTF8, 0, buf, (int)n, &line[0], len, NULL, NULL);
        return true;
    }
#endif
    return static_cast<bool>(getline(cin, line));   // ввід з файлу / каналу
}

static string ReadLine(const string& prompt)
{   // зчитує рядок; при завершенні потоку вводу завершує програму
    string line;
    cout << prompt << flush;
    if (!GetInputLine(line))
    {
        cout << endl << "Введення завершено. Роботу програми припинено." << endl;
        exit(0);
    }
    if (!line.empty() && line.back() == '\r') line.pop_back();
    return Trim(line);
}

int ReadInt(const string& prompt, const int lo, const int hi)
{   // повторює запит, доки не буде введено ціле число з діапазону [lo; hi]
    while (true)
    {
        string line = ReadLine(prompt);
        size_t pos = 0;
        int value = 0;
        bool ok = !line.empty();
        if (ok)
        {
            try { value = stoi(line, &pos); }
            catch (...) { ok = false; }
        }
        if (ok && pos != line.size()) ok = false;

        if (!ok)
            cout << "   Помилка: слід ввести ціле число." << endl;
        else if (value < lo || value > hi)
            cout << "   Помилка: число має бути в межах від " << lo
            << " до " << hi << "." << endl;
        else
            return value;
    }
}

static bool IsValidSurname(const string& s)
{   // 1..16 символів: літери (кирилиця/латиниця), пробіл, дефіс, апостроф
    size_t len = Utf8Length(s);
    if (len < 1 || len > 16) return false;
    for (char32_t c : ToCodePoints(s))
    {
        bool cyr = (c >= 0x0410 && c <= 0x044F) || c == 0x0401 || c == 0x0451 ||
            c == 0x0404 || c == 0x0454 || c == 0x0406 || c == 0x0456 ||
            c == 0x0407 || c == 0x0457 || c == 0x0490 || c == 0x0491;
        bool lat = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
        bool oth = c == ' ' || c == '-' || c == '\'' || c == 0x2019 || c == 0x02BC;
        if (!(cyr || lat || oth)) return false;
    }
    return true;
}

string ReadSurname(const string& prompt)
{
    while (true)
    {
        string s = ReadLine(prompt);
        if (IsValidSurname(s)) return s;
        cout << "   Помилка: прізвище має містити від 1 до 16 літер "
            "(допускаються пробіл, дефіс, апостроф)." << endl;
    }
}

Spec ReadSpec()
{
    cout << "     спеціальність:" << endl;
    for (int i = KN; i <= TN; i++)
        cout << "        " << i << " - " << SpecName((Spec)i) << endl;
    return (Spec)ReadInt("     виберіть номер спеціальності (0-4): ", 0, 4);
}

void Create(Student* s, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        s[i].prizv = ReadSurname("     прізвище: ");
        s[i].kurs = ReadInt("     курс (1-6): ", 1, 6);
        s[i].spec = ReadSpec();
        s[i].fizyka = ReadInt("     оцінка з фізики (1-5): ", 1, 5);
        s[i].matematyka = ReadInt("     оцінка з математики (1-5): ", 1, 5);
        switch (s[i].spec)
        {
        case KN:
            s[i].prog = ReadInt("     оцінка з програмування (1-5): ", 1, 5);
            break;
        case IN:
            s[i].chysl = ReadInt("     оцінка з чисельних методів (1-5): ", 1, 5);
            break;
        default:
            s[i].ped = ReadInt("     оцінка з педагогіки (1-5): ", 1, 5);
            break;
        }
        cout << endl;
    }
}

void PrintTable(const Student* s, const int N)
{
    const string line(101, '=');
    const string sep(101, '-');

    cout << line << endl;
    cout << "|" << PadCenter("СПИСОК СТУДЕНТІВ ГРУПИ", 99) << "|" << endl;
    cout << sep << endl;
    cout << "|" << PadCenter("№", 4)
        << "|" << PadCenter("Прізвище", 17)
        << "|" << PadCenter("Курс", 5)
        << "|" << PadCenter("Спеціальність", 25)
        << "|" << PadCenter("Фізика", 8)
        << "|" << PadCenter("Матем.", 8)
        << "|" << PadCenter("Прогр.", 8)
        << "|" << PadCenter("Чис.м.", 8)
        << "|" << PadCenter("Педаг.", 8) << "|" << endl;
    cout << sep << endl;

    for (int i = 0; i < N; i++)
    {   // клітинка третьої оцінки заповнена лише в одному з трьох стовпців
        string prog, chysl, ped;
        switch (s[i].spec)
        {
        case KN: prog = to_string(s[i].prog);  break;
        case IN: chysl = to_string(s[i].chysl); break;
        default: ped = to_string(s[i].ped);   break;
        }
        cout << "|" << PadLeft(to_string(i + 1), 3) << " "
            << "| " << PadRight(s[i].prizv, 16)
            << "|" << PadCenter(to_string(s[i].kurs), 5)
            << "| " << PadRight(SpecName(s[i].spec), 24)
            << "|" << PadCenter(to_string(s[i].fizyka), 8)
            << "|" << PadCenter(to_string(s[i].matematyka), 8)
            << "|" << PadCenter(prog, 8)
            << "|" << PadCenter(chysl, 8)
            << "|" << PadCenter(ped, 8) << "|" << endl;
    }
    cout << line << endl << endl;
}

bool HasNoThrees(const Student& st)
{   // «без трійок» – лише оцінки «5» та «4» з усіх трьох предметів
    return st.fizyka >= 4 && st.matematyka >= 4 && ThirdGrade(st) >= 4;
}

int CountNoThrees(const Student* s, const int N)
{   // послідовний пошук: кількість студентів, які вчаться на «відмінно» і «добре»
    int k = 0;
    for (int i = 0; i < N; i++)
        if (HasNoThrees(s[i]))
            k++;
    return k;
}

bool HasAverageBelow4(const Student& st)
{   // (ф + м + т) / 3 < 4  <=>  ф + м + т < 12 (цілочисельне порівняння)
    return st.fizyka + st.matematyka + ThirdGrade(st) < 12;
}

double PercentAverageBelow4(const Student* s, const int N)
{   // послідовний пошук: процент студентів, у яких середній бал менший за 4
    if (N <= 0) return 0.0;
    int k = 0;
    for (int i = 0; i < N; i++)
        if (HasAverageBelow4(s[i]))
            k++;
    return 100.0 * k / N;
}
