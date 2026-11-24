
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;

// Перелік спеціальностей
enum Spec
{
    SPEC_KN,    // Комп'ютерні науки
    SPEC_IN,    // Інформатика
    SPEC_ME,    // Математика та економіка
    SPEC_FI,    // Фізика та інформатика
    SPEC_TN     // Трудове навчання
};

// Структура студента з об'єднанням
struct Student
{
    string prizv;
    int kurs;
    Spec spec;
    int fizyka;
    int matem;

    union
    {
        int programuvannya;
        int chyselniMetody;
        int pedagogika;
    };
};

// Прототипи основних функцій
int ReadInt(const string& message);
int ReadRange(const string& message, int min, int max);

void Create(Student* s, const int N);
void Print(Student* s, const int N);
void Sort(Student* s, const int N);

string SpecToString(const Spec spec);

// Прототипи допоміжних функцій таблиці
size_t Len(const string& s);
string PadL(const string& s, size_t w);
string PadR(const string& s, size_t w);

void PrintBorder(const size_t W[]);
void PrintHeader(const size_t W[]);
void PrintRow(int num, const Student& st, const size_t W[]);

// Перевірка введення цілого числа
int ReadInt(const string& message)
{
    int x;
    string line;

    while (true)
    {
        cout << message;
        getline(cin, line);

        stringstream ss(line);

        if (ss >> x)
        {
            ss >> ws;

            if (ss.eof())
                return x;
        }

        cout << "Помилка! Введіть ціле число." << endl;
    }
}

// Перевірка введення числа в заданому діапазоні
int ReadRange(const string& message, int min, int max)
{
    int x;

    do
    {
        x = ReadInt(message);

        if (x < min || x > max)
            cout << "Помилка! Введіть число від "
            << min << " до " << max << "." << endl;

    } while (x < min || x > max);

    return x;
}

// Формування масиву студентів
void Create(Student* s, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "\nСтудент № " << i + 1 << ":" << endl;

        do
        {
            cout << "     Прізвище: ";
            getline(cin, s[i].prizv);

            if (s[i].prizv.empty())
                cout << "Помилка! Введіть прізвище." << endl;

        } while (s[i].prizv.empty());

        s[i].kurs = ReadRange("     Курс (1 - 6): ", 1, 6);

        int spec;

        cout << "\nСпеціальність:" << endl;
        cout << "     0 - Комп'ютерні науки" << endl;
        cout << "     1 - Інформатика" << endl;
        cout << "     2 - Математика та економіка" << endl;
        cout << "     3 - Фізика та інформатика" << endl;
        cout << "     4 - Трудове навчання" << endl;

        spec = ReadRange("     Введіть номер спеціальності: ", 0, 4);

        s[i].spec = (Spec)spec;

        s[i].fizyka = ReadRange(
            "     Оцінка з фізики (0 - 100): ", 0, 100);

        s[i].matem = ReadRange(
            "     Оцінка з математики (0 - 100): ", 0, 100);

        switch (s[i].spec)
        {
        case SPEC_KN:
            s[i].programuvannya = ReadRange(
                "     Оцінка з програмування (0 - 100): ", 0, 100);
            break;

        case SPEC_IN:
            s[i].chyselniMetody = ReadRange(
                "     Оцінка з чисельних методів (0 - 100): ", 0, 100);
            break;

        case SPEC_ME:
        case SPEC_FI:
        case SPEC_TN:
            s[i].pedagogika = ReadRange(
                "     Оцінка з педагогіки (0 - 100): ", 0, 100);
            break;
        }

        cout << endl;
    }
}

// Кількість символів UTF-8
size_t Len(const string& s)
{
    size_t n = 0;

    for (unsigned char c : s)
        if ((c & 0xC0) != 0x80)
            n++;

    return n;
}

// Вирівнювання вправо
string PadL(const string& s, size_t w)
{
    size_t l = Len(s);

    return (l >= w) ? s : string(w - l, ' ') + s;
}

// Вирівнювання вліво
string PadR(const string& s, size_t w)
{
    size_t l = Len(s);

    return (l >= w) ? s : s + string(w - l, ' ');
}

// Назва спеціальності
string SpecToString(const Spec spec)
{
    switch (spec)
    {
    case SPEC_KN:
        return "Комп'ютерні науки";

    case SPEC_IN:
        return "Інформатика";

    case SPEC_ME:
        return "Математика та економіка";

    case SPEC_FI:
        return "Фізика та інформатика";

    case SPEC_TN:
        return "Трудове навчання";
    }

    return "";
}

// Межі таблиці
void PrintBorder(const size_t W[])
{
    cout << "+";

    for (int i = 0; i < 9; i++)
        cout << string(W[i] + 2, '-') << "+";

    cout << endl;
}

// Заголовок таблиці
void PrintHeader(const size_t W[])
{
    PrintBorder(W);

    cout << "| " << PadL("№", W[0])
        << " | " << PadR("Прізвище", W[1])
        << " | " << PadL("Курс", W[2])
        << " | " << PadR("Спеціальність", W[3])
        << " | " << PadL("Фізика", W[4])
        << " | " << PadL("Математика", W[5])
        << " | " << PadL("Програмування", W[6])
        << " | " << PadL("Чисельні методи", W[7])
        << " | " << PadL("Педагогіка", W[8])
        << " |" << endl;

    PrintBorder(W);
}

// Виведення одного рядка таблиці
void PrintRow(int num, const Student& st, const size_t W[])
{
    cout << "| " << PadL(to_string(num), W[0])
        << " | " << PadR(st.prizv, W[1])
        << " | " << PadL(to_string(st.kurs), W[2])
        << " | " << PadR(SpecToString(st.spec), W[3])
        << " | " << PadL(to_string(st.fizyka), W[4])
        << " | " << PadL(to_string(st.matem), W[5])
        << " | ";

    switch (st.spec)
    {
    case SPEC_KN:

        cout << PadL(to_string(st.programuvannya), W[6])
            << " | " << PadL("", W[7])
            << " | " << PadL("", W[8]);

        break;

    case SPEC_IN:

        cout << PadL("", W[6])
            << " | " << PadL(to_string(st.chyselniMetody), W[7])
            << " | " << PadL("", W[8]);

        break;

    case SPEC_ME:
    case SPEC_FI:
    case SPEC_TN:

        cout << PadL("", W[6])
            << " | " << PadL("", W[7])
            << " | " << PadL(to_string(st.pedagogika), W[8]);

        break;
    }

    cout << " |" << endl;
}

// Виведення масиву у вигляді таблиці
void Print(Student* s, const int N)
{
    const size_t W[9] = { 3, 15, 4, 24, 7, 10, 15, 18, 11 };

    cout << "\n";
    cout << "                         СПИСОК СТУДЕНТІВ" << endl;

    PrintHeader(W);

    for (int i = 0; i < N; i++)
        PrintRow(i + 1, s[i], W);

    PrintBorder(W);

    cout << endl;
}

// Фізичне впорядкування масиву
// Курс - зростання
// Математика - зростання
// Прізвище - спадання
void Sort(Student* s, const int N)
{
    Student tmp;

    for (int i0 = 0; i0 < N - 1; i0++)
    {
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            if ((s[i1].kurs > s[i1 + 1].kurs)
                ||
                (s[i1].kurs == s[i1 + 1].kurs &&
                    s[i1].matem > s[i1 + 1].matem)
                ||
                (s[i1].kurs == s[i1 + 1].kurs &&
                    s[i1].matem == s[i1 + 1].matem &&
                    s[i1].prizv < s[i1 + 1].prizv))
            {
                tmp = s[i1];
                s[i1] = s[i1 + 1];
                s[i1 + 1] = tmp;
            }
        }
    }
}

// Головна функція
int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int N;

    do
    {
        N = ReadInt("Введіть кількість студентів N: ");

        if (N <= 0)
            cout << "Помилка! Слід ввести додатне число." << endl;

    } while (N <= 0);

    Student* s = new Student[N];

    bool entered = false;
    int menuItem;

    do
    {
        cout << "\n\n";
        cout << "Виберіть дію:" << endl << endl;

        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - виведення даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;

        menuItem = ReadInt("Введіть значення: ");

        cout << endl;

        switch (menuItem)
        {
        case 1:

            Create(s, N);
            entered = true;

            break;

        case 2:

            if (entered)
                Print(s, N);
            else
                cout << "Спочатку введіть дані студентів!" << endl;

            break;

        case 3:

            if (entered)
            {
                Sort(s, N);

                cout << "Масив успішно впорядковано!" << endl;

                Print(s, N);
            }
            else
                cout << "Спочатку введіть дані студентів!" << endl;

            break;

        case 0:

            cout << "Завершення роботи програми." << endl;

            break;

        default:

            cout << "Помилка! Слід ввести номер пункту меню." << endl;
        }

    } while (menuItem != 0);

    delete[] s;

    return 0;
}
