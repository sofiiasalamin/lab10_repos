#include "pch.h"
#include "CppUnitTest.h"
#include <string>

#define main StudentProgramMain
#include "../10.2А/10.2А.cpp"
#undef main

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestStudent
{
    TEST_CLASS(StudentTests)
    {
    public:

        
        TEST_METHOD(Sort_Test)
        {
            Student s[3] = {
                {"Петренко", 2, SPEC_KN, 80, 80, 90},
                {"Іваненко", 1, SPEC_IN, 70, 70, 80},
                {"Сидоренко", 2, SPEC_ME, 60, 60, 70}
            };

            Sort(s, 3);

            Assert::IsTrue(s[0].kurs == 1);
            Assert::IsTrue(s[1].kurs == 2);
            Assert::IsTrue(s[1].matem == 60);
            Assert::IsTrue(s[2].matem == 80);
        }

       
        TEST_METHOD(BinSearch_Found)
        {
            Student s[3] = {
                {"Петренко", 2, SPEC_KN, 80, 80, 90},
                {"Іваненко", 1, SPEC_IN, 70, 70, 80},
                {"Сидоренко", 2, SPEC_ME, 60, 60, 70}
            };

            Sort(s, 3);

            int result = BinSearch(s, 3, "Петренко", 2, 80);

            Assert::IsTrue(result != -1);
            Assert::IsTrue(s[result].prizv == "Петренко");
        }

        TEST_METHOD(BinSearch_NotFound)
        {
            Student s[3] = {
                {"Петренко", 2, SPEC_KN, 80, 80, 90},
                {"Іваненко", 1, SPEC_IN, 70, 70, 80},
                {"Сидоренко", 2, SPEC_ME, 60, 60, 70}
            };

            Sort(s, 3);

            int result = BinSearch(s, 3, "Мельник", 3, 90);

            Assert::AreEqual(-1, result);
        }

        TEST_METHOD(IndexSort_Test)
        {
            Student s[3] = {
                {"Петренко", 2, SPEC_KN, 80, 80, 90},
                {"Іваненко", 1, SPEC_IN, 70, 70, 80},
                {"Сидоренко", 2, SPEC_ME, 60, 60, 70}
            };

            int* I = IndexSort(s, 3);

            Assert::IsTrue(s[I[0]].kurs == 1);
            Assert::IsTrue(s[I[1]].kurs == 2);
            Assert::IsTrue(s[I[1]].matem == 60);
            Assert::IsTrue(s[I[2]].matem == 80);

            delete[] I;
        }

       
    };
}

