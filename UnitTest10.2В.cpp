
#include "pch.h"
#include "CppUnitTest.h"

#define main StudentProgramMain
#include "../10.2В/10.2В.cpp"
#undef main

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestStudent
{
    TEST_CLASS(StudentTests)
    {
    public:

        // Тест 1. Перевірка сортування за курсом
        TEST_METHOD(Sort_Test_Course)
        {
            Student s[3] = {};

            s[0].prizv = "Ivanov";
            s[0].kurs = 3;
            s[0].matem = 80;

            s[1].prizv = "Petrenko";
            s[1].kurs = 1;
            s[1].matem = 90;

            s[2].prizv = "Kovalenko";
            s[2].kurs = 2;
            s[2].matem = 70;

            Sort(s, 3);

            Assert::IsTrue(s[0].kurs == 1);
            Assert::IsTrue(s[1].kurs == 2);
            Assert::IsTrue(s[2].kurs == 3);
        }

        // Тест 2. Перевірка сортування за оцінкою з математики
        TEST_METHOD(Sort_Test_Mathematics)
        {
            Student s[3] = {};

            s[0].prizv = "Ivanov";
            s[0].kurs = 2;
            s[0].matem = 90;

            s[1].prizv = "Petrenko";
            s[1].kurs = 2;
            s[1].matem = 60;

            s[2].prizv = "Kovalenko";
            s[2].kurs = 2;
            s[2].matem = 80;

            Sort(s, 3);

            Assert::IsTrue(s[0].matem == 60);
            Assert::IsTrue(s[1].matem == 80);
            Assert::IsTrue(s[2].matem == 90);
        }

        // Тест 3. Перевірка сортування прізвищ за спаданням
        TEST_METHOD(Sort_Test_Surname)
        {
            Student s[3] = {};

            s[0].prizv = "Andriienko";
            s[0].kurs = 1;
            s[0].matem = 80;

            s[1].prizv = "Petrenko";
            s[1].kurs = 1;
            s[1].matem = 80;

            s[2].prizv = "Ivanov";
            s[2].kurs = 1;
            s[2].matem = 80;

            Sort(s, 3);

            Assert::IsTrue(s[0].prizv == "Petrenko");
            Assert::IsTrue(s[1].prizv == "Ivanov");
            Assert::IsTrue(s[2].prizv == "Andriienko");
        }

        // Тест 4. Перевірка всіх критеріїв сортування
        TEST_METHOD(Sort_Test_All)
        {
            Student s[5] = {};

            s[0].prizv = "Ivanov";
            s[0].kurs = 2;
            s[0].matem = 80;

            s[1].prizv = "Petrenko";
            s[1].kurs = 1;
            s[1].matem = 90;

            s[2].prizv = "Shevchenko";
            s[2].kurs = 2;
            s[2].matem = 70;

            s[3].prizv = "Andriienko";
            s[3].kurs = 2;
            s[3].matem = 80;

            s[4].prizv = "Kovalenko";
            s[4].kurs = 1;
            s[4].matem = 70;

            Sort(s, 5);

            Assert::IsTrue(s[0].prizv == "Kovalenko");
            Assert::IsTrue(s[1].prizv == "Petrenko");
            Assert::IsTrue(s[2].prizv == "Shevchenko");
            Assert::IsTrue(s[3].prizv == "Ivanov");
            Assert::IsTrue(s[4].prizv == "Andriienko");
        }

       

        // Тест 6. Перевірка сортування одного студента
        TEST_METHOD(Sort_Test_OneStudent)
        {
            Student s[1] = {};

            s[0].prizv = "Ivanov";
            s[0].kurs = 2;
            s[0].matem = 85;

            Sort(s, 1);

            Assert::IsTrue(s[0].prizv == "Ivanov");
            Assert::IsTrue(s[0].kurs == 2);
            Assert::IsTrue(s[0].matem == 85);
        }
    };
}
