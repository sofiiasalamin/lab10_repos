#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>               // забезпечення відображення кирилиці
using namespace std;

// назви елементів мають префікс SPEC_, бо Windows.h визначає макрос IN
enum Spec { SPEC_KN, SPEC_IN, SPEC_ME, SPEC_FI, SPEC_TN };
// Комп'ютерні науки, Інформатика, Математика та економіка, Фізика та інформатика, Трудове навчання

struct Student
{
    string   prizv;
    int      kurs;
    Spec     spec;
    int      fizyka;
    int      matem;
    int      inform;
};

void Create(Student* s, const int N);
void Print(Student* s, const int N);
void Sort(Student* s, const int N);
int BinSearch(Student* s, const int N, const string prizv, const int kurs, const int matem);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);
string SpecToString(const Spec spec);

// допоміжні функції для акуратного виводу таблиці
size_t Len(const string& s);
string PadL(const string& s, size_t w);
string PadR(const string& s, size_t w);
void PrintBorder();
void PrintHeader();
void PrintRow(int num, const Student& st);

int main()
{                             // забезпечення відображення кирилиці:
    SetConsoleCP(65001);       // встановлення кодової сторінки UTF-8 в потік вводу
    SetConsoleOutputCP(65001); // встановлення кодової сторінки UTF-8 в потік виводу

    int N;
    do {
        cout << "Введіть кількість студентів N: "; cin >> N;
        if (N <= 0)
            cout << "Ви ввели помилкове значення! Слід ввести додатне число" << endl;
    } while (N <= 0);

    Student* s = new Student[N];

    int* I;
    string prizv;
    int kurs;
    int matem;
    int found;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl;
        cout << " [5] - бінарний пошук студента за прізвищем, курсом та оцінкою з математики" << endl;
        cout << "       (виконувати після фізичного впорядкування – пункт [3])" << endl << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem)
        {
        case 1:
            Create(s, N);
            break;
        case 2:
            Print(s, N);
            break;
        case 3:
            Sort(s, N);
            break;
        case 4:
            I = IndexSort(s, N);
            PrintIndexSorted(s, I, N);
            delete[] I;
            break;
        case 5:
            cout << "Введіть ключі пошуку:" << endl;
            cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
            cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
            cout << "     прізвище: "; getline(cin, prizv);
            do {
                cout << "     курс (1 - 6): "; cin >> kurs;
                if (kurs < 1 || kurs > 6)
                    cout << "Ви ввели помилкове значення! Слід ввести число від 1 до 6" << endl;
            } while (kurs < 1 || kurs > 6);
            do {
                cout << "     оцінка з математики (0 - 100): "; cin >> matem;
                if (matem < 0 || matem > 100)
                    cout << "Ви ввели помилкове значення! Слід ввести число від 0 до 100" << endl;
            } while (matem < 0 || matem > 100);
            cout << endl;
            if ((found = BinSearch(s, N, prizv, kurs, matem)) != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    delete[] s;
    return 0;
}

// Формування масиву: введення даних з клавіатури з контролем помилок
void Create(Student* s, const int N)
{
    int spec;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
        cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

        cout << "     прізвище: "; getline(cin, s[i].prizv);
        do {
            cout << "     курс (1 - 6): "; cin >> s[i].kurs;
            if (s[i].kurs < 1 || s[i].kurs > 6)
                cout << "Ви ввели помилкове значення! Слід ввести число від 1 до 6" << endl;
        } while (s[i].kurs < 1 || s[i].kurs > 6);
        do {
            cout << "     спеціальність (0 - Комп'ютерні науки, 1 - Інформатика," << endl;
            cout << "        2 - Математика та економіка, 3 - Фізика та інформатика," << endl;
            cout << "        4 - Трудове навчання): "; cin >> spec;
            if (spec < 0 || spec > 4)
                cout << "Ви ввели помилкове значення! Слід ввести число від 0 до 4" << endl;
        } while (spec < 0 || spec > 4);
        s[i].spec = (Spec)spec;
        do {
            cout << "     оцінка з фізики (0 - 100): "; cin >> s[i].fizyka;
            if (s[i].fizyka < 0 || s[i].fizyka > 100)
                cout << "Ви ввели помилкове значення! Слід ввести число від 0 до 100" << endl;
        } while (s[i].fizyka < 0 || s[i].fizyka > 100);
        do {
            cout << "     оцінка з математики (0 - 100): "; cin >> s[i].matem;
            if (s[i].matem < 0 || s[i].matem > 100)
                cout << "Ви ввели помилкове значення! Слід ввести число від 0 до 100" << endl;
        } while (s[i].matem < 0 || s[i].matem > 100);
        do {
            cout << "     оцінка з інформатики (0 - 100): "; cin >> s[i].inform;
            if (s[i].inform < 0 || s[i].inform > 100)
                cout << "Ви ввели помилкове значення! Слід ввести число від 0 до 100" << endl;
        } while (s[i].inform < 0 || s[i].inform > 100);
        cout << endl;
    }
}

// ---------- Допоміжні функції для виводу таблиці ----------

// Кількість символів UTF-8 (а не байтів)
size_t Len(const string& s)
{
    size_t n = 0;
    for (unsigned char c : s)
        if ((c & 0xC0) != 0x80) n++;
    return n;
}

// Вирівнювання вправо (доповнення пробілами зліва)
string PadL(const string& s, size_t w)
{
    size_t l = Len(s);
    return (l >= w) ? s : string(w - l, ' ') + s;
}

// Вирівнювання вліво (доповнення пробілами справа)
string PadR(const string& s, size_t w)
{
    size_t l = Len(s);
    return (l >= w) ? s : s + string(w - l, ' ');
}

// Ширини стовпців: №, Прізвище, Курс, Спеціальність, Фізика, Матем., Інформ.
const size_t W[7] = { 3, 15, 4, 24, 6, 6, 7 };

void PrintBorder()
{
    cout << "+";
    for (int i = 0; i < 7; i++)
        cout << string(W[i] + 2, '-') << "+";
    cout << endl;
}

void PrintHeader()
{
    PrintBorder();
    cout << "| " << PadL("№", W[0])
        << " | " << PadR("Прізвище", W[1])
        << " | " << PadL("Курс", W[2])
        << " | " << PadR("Спеціальність", W[3])
        << " | " << PadL("Фізика", W[4])
        << " | " << PadL("Матем.", W[5])
        << " | " << PadL("Інформ.", W[6])
        << " |" << endl;
    PrintBorder();
}

void PrintRow(int num, const Student& st)
{
    cout << "| " << PadL(to_string(num), W[0])
        << " | " << PadR(st.prizv, W[1])
        << " | " << PadL(to_string(st.kurs), W[2])
        << " | " << PadR(SpecToString(st.spec), W[3])
        << " | " << PadL(to_string(st.fizyka), W[4])
        << " | " << PadL(to_string(st.matem), W[5])
        << " | " << PadL(to_string(st.inform), W[6])
        << " |" << endl;
}

// Вивід масиву у вигляді таблиці
void Print(Student* s, const int N)
{
    cout << "                    СПИСОК СТУДЕНТІВ" << endl;
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(i + 1, s[i]);
    PrintBorder();
    cout << endl;
}

// Фізичне впорядкування: курс (зростання), оцінка з математики (зростання), прізвище (спадання)
void Sort(Student* s, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)        // метод "бульбашки"
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
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

// Бінарний пошук у фізично впорядкованому масиві за ключами (прізвище, курс, оцінка з математики)
int BinSearch(Student* s, const int N, const string prizv, const int kurs, const int matem)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (s[m].prizv == prizv && s[m].kurs == kurs && s[m].matem == matem)
            return m;
        if ((s[m].kurs < kurs)
            ||
            (s[m].kurs == kurs &&
                s[m].matem < matem)
            ||
            (s[m].kurs == kurs &&
                s[m].matem == matem &&
                s[m].prizv > prizv))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}

// Побудова індексного масиву: курс, оцінка з математики, прізвище (за зростанням)
int* IndexSort(Student* s, const int N)
{ // використовуємо метод вставки для формування індексного масиву
    int* I = new int[N];    // створили індексний масив

    for (int i = 0; i < N; i++)
        I[i] = i;             // заповнили його початковими даними

    int i, j, value;         // починаємо сортувати масив індексів
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
            j >= 0 && ((s[I[j]].kurs > s[value].kurs) ||
                (s[I[j]].kurs == s[value].kurs &&
                    s[I[j]].matem > s[value].matem) ||
                (s[I[j]].kurs == s[value].kurs &&
                    s[I[j]].matem == s[value].matem &&
                    s[I[j]].prizv > s[value].prizv));
            j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }

    return I;
}

// Аналогічно функції Print(), але доступ до елементів за допомогою індексного масиву: s[I[i]]...
void PrintIndexSorted(Student* s, int* I, const int N)
{
    cout << "           СПИСОК СТУДЕНТІВ (індексне впорядкування)" << endl;
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(i + 1, s[I[i]]);
    PrintBorder();
    cout << endl;
}

// Повертає назву спеціальності за значенням переліку
string SpecToString(const Spec spec)
{
    switch (spec)
    {
    case SPEC_KN: return "Комп'ютерні науки";
    case SPEC_IN: return "Інформатика";
    case SPEC_ME: return "Математика та економіка";
    case SPEC_FI: return "Фізика та інформатика";
    case SPEC_TN: return "Трудове навчання";
    }
    return "";
}