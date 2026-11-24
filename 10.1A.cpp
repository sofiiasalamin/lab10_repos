#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#ifdef _WIN32
#include <Windows.h>
#endif
using namespace std;

// спеціальності (перелік)
enum Spec { KOMP_NAUKY, INFORMATYKA, MAT_EKON, FIZ_INF, TRUD_NAV };

// Рівень А: три оцінки – звичайні поля (без об'єднання)
struct Student
{
    string   prizv;
    unsigned kurs;
    Spec     spec;
    int      fizyka;
    int      matematyka;
    int      informatyka;
};

string SpecToString(const Spec spec);
void Create(Student* s, const int N);
void Print(const Student* s, const int N);
size_t TextLength(const string& text);
string FitToWidth(const string& text, const size_t width, const bool alignLeft);
void PrintRow(const vector<string>& cells, const vector<int>& widths);
bool HasNoThrees(const Student& s);
double CalcPercentWithoutThrees(const Student* s, const int N);
vector<string> FindSurnamesPhysics5or4(const Student* s, const int N);
void PrintSurnames(const vector<string>& surnames);

int main()
{
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    int N;
    cout << "Введіть кількість студентів N: "; cin >> N;

    Student* s = new Student[N];

    Create(s, N);
    Print(s, N);

    double percent = CalcPercentWithoutThrees(s, N);
    cout << "Процент студентів, які вчаться без трійок: "
        << fixed << setprecision(2) << percent << " %" << endl << endl;

    vector<string> surnames = FindSurnamesPhysics5or4(s, N);
    cout << "Студенти, які отримали з фізики оцінки \"5\" або \"4\":" << endl;
    PrintSurnames(surnames);

    delete[] s;
    return 0;
}

// Повертає назву спеціальності
string SpecToString(const Spec spec)
{
    switch (spec)
    {
    case KOMP_NAUKY: return "Комп'ютерні науки";
    case INFORMATYKA: return "Інформатика";
    case MAT_EKON: return "Математика та економіка";
    case FIZ_INF: return "Фізика та інформатика";
    case TRUD_NAV: return "Трудове навчання";
    default: return "";
    }
}

// Формування масиву: введення даних про студентів з клавіатури
void Create(Student* s, const int N)
{
    int spec;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        cin.get();   // очищуємо буфер клавіатури
        cin.sync();

        cout << "     прізвище: "; getline(cin, s[i].prizv);
        cout << "     курс: "; cin >> s[i].kurs;
        cout << "     спеціальність (0 - Комп'ютерні науки, 1 - Інформатика,\n"
            << "                    2 - Математика та економіка, 3 - Фізика та інформатика,\n"
            << "                    4 - Трудове навчання): ";
        cin >> spec;
        s[i].spec = (Spec)spec;

        cout << "     оцінка з фізики: "; cin >> s[i].fizyka;
        cout << "     оцінка з математики: "; cin >> s[i].matematyka;
        cout << "     оцінка з інформатики: "; cin >> s[i].informatyka;
        cout << endl;
    }
}

// Повертає кількість символів у рядку (кирилиця в UTF-8 займає по 2 байти)
size_t TextLength(const string& text)
{
    size_t length = 0, i = 0;
    while (i < text.size())
    {
        unsigned char c = text[i];
        size_t bytes = 1;
        if ((c & 0xE0) == 0xC0) bytes = 2;
        else if ((c & 0xF0) == 0xE0) bytes = 3;
        else if ((c & 0xF8) == 0xF0) bytes = 4;

        bool valid = (i + bytes <= text.size());
        for (size_t k = 1; valid && k < bytes; k++)
            valid = ((unsigned char)text[i + k] & 0xC0) == 0x80;

        if (!valid)
            return text.size();

        i += bytes;
        length++;
    }
    return length;
}

// Повертає рядок, доповнений пробілами до заданої кількості символів
string FitToWidth(const string& text, const size_t width, const bool alignLeft)
{
    size_t len = TextLength(text);
    string spaces(len < width ? width - len : 0, ' ');
    return alignLeft ? text + spaces : spaces + text;
}

// Виводить один рядок таблиці (текстові стовпці 1 і 3 – вліво, решта – вправо)
void PrintRow(const vector<string>& cells, const vector<int>& widths)
{
    cout << "|";
    for (size_t i = 0; i < cells.size(); i++)
    {
        bool left = (i == 1 || i == 3);
        cout << " " << FitToWidth(cells[i], widths[i], left) << " |";
    }
    cout << endl;
}

// Вивід масиву у вигляді таблиці (заголовок і шапка) – 7 клітинок
void Print(const Student* s, const int N)
{
    const vector<int> widths = { 3, 15, 4, 24, 6, 10, 11 };
    int total = 1;
    for (size_t i = 0; i < widths.size(); i++)
        total += widths[i] + 3;
    const string doubleLine(total, '='), singleLine(total, '-');

    cout << endl << FitToWidth("Список студентів групи", (total + 22) / 2, false) << endl;
    cout << doubleLine << endl;
    PrintRow({ "№", "Прізвище", "Курс", "Спеціальність", "Фізика",
               "Математика", "Інформатика" }, widths);
    cout << singleLine << endl;

    for (int i = 0; i < N; i++)
    {
        PrintRow({ to_string(i + 1), s[i].prizv, to_string(s[i].kurs),
                   SpecToString(s[i].spec), to_string(s[i].fizyka),
                   to_string(s[i].matematyka), to_string(s[i].informatyka) }, widths);
    }
    cout << doubleLine << endl << endl;
}

// Перевіряє, чи студент вчиться без трійок (усі оцінки "5" або "4")
bool HasNoThrees(const Student& s)
{
    return s.fizyka >= 4 && s.matematyka >= 4 && s.informatyka >= 4;
}

// Обчислює процент студентів, які вчаться без трійок (послідовний пошук)
double CalcPercentWithoutThrees(const Student* s, const int N)
{
    if (N <= 0)
        return 0;

    int k = 0;
    for (int i = 0; i < N; i++)
        if (HasNoThrees(s[i]))
            k++;

    return 100.0 * k / N;
}

// Шукає прізвища студентів, які отримали з фізики оцінки "5" або "4"
vector<string> FindSurnamesPhysics5or4(const Student* s, const int N)
{
    vector<string> result;
    for (int i = 0; i < N; i++)
        if (s[i].fizyka == 5 || s[i].fizyka == 4)
            result.push_back(s[i].prizv);

    return result;
}

// Виводить прізвища зі списку
void PrintSurnames(const vector<string>& surnames)
{
    if (surnames.empty())
        cout << "  таких студентів немає" << endl;

    for (size_t i = 0; i < surnames.size(); i++)
        cout << "  " << i + 1 << ". " << surnames[i] << endl;
}