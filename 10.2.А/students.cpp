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

double AverageGrade(const Student& st)
{
    return (st.fizyka + st.matematyka + st.informatyka) / 3.0;
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
        s[i].informatyka = ReadInt("     оцінка з інформатики (1-5): ", 1, 5);
        cout << endl;
    }
}


static void PrintTableCore(const Student* s, const int* I, const int N, const string& title)
{   // I == nullptr – вивід у фізичному порядку; інакше – у порядку, заданому
    // індексним масивом I (елемент s[I[i]]), сам масив s при цьому не змінюється
    const string line(83, '=');
    const string sep(83, '-');

    cout << line << endl;
    cout << "|" << PadCenter(title, 81) << "|" << endl;
    cout << sep << endl;
    cout << "|" << PadCenter("№", 4)
        << "|" << PadCenter("Прізвище", 17)
        << "|" << PadCenter("Курс", 5)
        << "|" << PadCenter("Спеціальність", 25)
        << "|" << PadCenter("Фізика", 8)
        << "|" << PadCenter("Матем.", 8)
        << "|" << PadCenter("Інформ.", 8) << "|" << endl;
    cout << sep << endl;

    for (int i = 0; i < N; i++)
    {
        const Student& st = I == nullptr ? s[i] : s[I[i]];
        cout << "|" << PadLeft(to_string(i + 1), 3) << " "
            << "| " << PadRight(st.prizv, 16)
            << "|" << PadCenter(to_string(st.kurs), 5)
            << "| " << PadRight(SpecName(st.spec), 24)
            << "|" << PadCenter(to_string(st.fizyka), 8)
            << "|" << PadCenter(to_string(st.matematyka), 8)
            << "|" << PadCenter(to_string(st.informatyka), 8) << "|" << endl;
    }
    cout << line << endl << endl;
}


void PrintTable(const Student* s, const int N)
{
    PrintTableCore(s, nullptr, N, "СПИСОК СТУДЕНТІВ ГРУПИ");
}

void PrintIndexSorted(const Student* s, const int* I, const int N)
{
    PrintTableCore(s, I, N, "СПИСОК СТУДЕНТІВ ГРУПИ (індексне впорядкування)");
}


static char32_t ToLowerUkr(const char32_t c)
{   // перетворення великих літер (кирилиця, латиниця) на малі
    if (c >= 0x0410 && c <= 0x042F) return c + 0x20;   // А–Я -> а–я
    switch (c)
    {
    case 0x0401: return 0x0451;   // Ё -> ё
    case 0x0404: return 0x0454;   // Є -> є
    case 0x0406: return 0x0456;   // І -> і
    case 0x0407: return 0x0457;   // Ї -> ї
    case 0x0490: return 0x0491;   // Ґ -> ґ
    }
    if (c >= 'A' && c <= 'Z') return c + 0x20;
    return c;
}

static int LetterRank(const char32_t c)
{   // «вага» символа при порівнянні: розділові знаки < літери української абетки < решта
    const u32string alphabet = U"абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
    if (c == '\'' || c == 0x2019 || c == 0x02BC) return 39;   // усі апострофи однакові
    if (c == ' ' || c == '-') return static_cast<int>(c);
    size_t pos = alphabet.find(ToLowerUkr(c));
    if (pos != u32string::npos) return 1000 + static_cast<int>(pos);
    return 2000 + static_cast<int>(ToLowerUkr(c));
}

int CompareUkr(const string& a, const string& b)
{   // -1: a < b, 0: рівні (без урахування регістру), 1: a > b – в алфавітному порядку
    u32string x = ToCodePoints(a), y = ToCodePoints(b);
    size_t n = x.size() < y.size() ? x.size() : y.size();
    for (size_t i = 0; i < n; i++)
    {
        int rx = LetterRank(x[i]), ry = LetterRank(y[i]);
        if (rx != ry) return rx < ry ? -1 : 1;
    }
    if (x.size() == y.size()) return 0;
    return x.size() < y.size() ? -1 : 1;
}

int CompareKeys(const int kurs1, const Spec spec1, const string& prizv1,
    const int kurs2, const Spec spec2, const string& prizv2,
    const bool prizvDescending)
{   // ключі: 1) курс (за зростанням); 2) назва спеціальності (за зростанням);
    //        3) прізвище (за спаданням чи за зростанням – залежно від prizvDescending)
    if (kurs1 != kurs2)
        return kurs1 < kurs2 ? -1 : 1;
    int c = CompareUkr(SpecName(spec1), SpecName(spec2));
    if (c != 0)
        return c;
    c = CompareUkr(prizv1, prizv2);
    return prizvDescending ? -c : c;
}

int ComparePhysical(const Student& a, const Student& b)
{   // порядок фізичного впорядкування: прізвище – за спаданням
    return CompareKeys(a.kurs, a.spec, a.prizv, b.kurs, b.spec, b.prizv, true);
}

int CompareIndexed(const Student& a, const Student& b)
{   // порядок індексного впорядкування: прізвище – за зростанням
    return CompareKeys(a.kurs, a.spec, a.prizv, b.kurs, b.spec, b.prizv, false);
}


void Sort(Student* s, const int N)
{   // метод «бульбашки»: реально змінює порядок елементів масиву
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if (ComparePhysical(s[i1], s[i1 + 1]) > 0)
            {
                tmp = s[i1];
                s[i1] = s[i1 + 1];
                s[i1 + 1] = tmp;
            }
}

bool IsSortedPhysically(const Student* s, const int N)
{
    for (int i = 1; i < N; i++)
        if (ComparePhysical(s[i - 1], s[i]) > 0)
            return false;
    return true;
}


int* IndexSort(const Student* s, const int N)
{   // метод вставки для формування індексного масиву; масив s не змінюється
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;                       // початкові дані індексного масиву

    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1; j >= 0 && CompareIndexed(s[I[j]], s[value]) > 0; j--)
            I[j + 1] = I[j];
        I[j + 1] = value;
    }
    return I;
}


int BinSearch(const Student* s, const int N,
    const string& prizv, const int kurs, const Spec spec)
{   // бінарний пошук у ФІЗИЧНО впорядкованому масиві (порядок – ComparePhysical);
    // повертає індекс знайденого елемента або -1, якщо такого студента немає
    int L = 0, R = N - 1;
    while (L <= R)
    {
        int m = L + (R - L) / 2;
        int c = CompareKeys(s[m].kurs, s[m].spec, s[m].prizv, kurs, spec, prizv, true);
        if (c == 0) return m;
        if (c < 0)  L = m + 1;
        else        R = m - 1;
    }
    return -1;
}

int IndexBinSearch(const Student* s, const int* I, const int N,
    const string& prizv, const int kurs, const Spec spec)
{   // бінарний пошук в ІНДЕКСНО впорядкованому масиві (порядок – CompareIndexed);
    // повертає позицію в індексному масиві (елемент – s[I[позиція]]) або -1
    int L = 0, R = N - 1;
    while (L <= R)
    {
        int m = L + (R - L) / 2;
        const Student& st = s[I[m]];
        int c = CompareKeys(st.kurs, st.spec, st.prizv, kurs, spec, prizv, false);
        if (c == 0) return m;
        if (c < 0)  L = m + 1;
        else        R = m - 1;
    }
    return -1;
}
