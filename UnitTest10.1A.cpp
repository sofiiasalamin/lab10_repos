#include "pch.h"
#include "CppUnitTest.h"
#include <sstream>
#include <string>
#include <vector>
#include "../10.1A/10.1A.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests101
{
	
	Student MakeStudent(const string& prizv, Spec spec, int fizyka, int matematyka, int informatyka)
	{
		Student s;
		s.prizv = prizv;
		s.kurs = 2;
		s.spec = spec;
		s.fizyka = fizyka;
		s.matematyka = matematyka;
		s.informatyka = informatyka;
		return s;
	}
	class CoutCapture
	{
		streambuf* old;
		ostringstream buffer;
	public:
		CoutCapture() { old = cout.rdbuf(buffer.rdbuf()); }
		~CoutCapture() { cout.rdbuf(old); }
		string Str() const { return buffer.str(); }
	};

	TEST_CLASS(SpecToStringTests)
	{
	public:

		TEST_METHOD(SpecToString_KompNauky)
		{
			Assert::AreEqual(string("Комп'ютерні науки"), SpecToString(KOMP_NAUKY));
		}

		
	};

	TEST_CLASS(HasNoThreesTests)
	{
	public:

		TEST_METHOD(HasNoThrees_AllFives)
		{
			Student s = MakeStudent("A", KOMP_NAUKY, 5, 5, 5);
			Assert::IsTrue(HasNoThrees(s));
		}

		TEST_METHOD(HasNoThrees_AllFours_Boundary)
		{
			Student s = MakeStudent("A", KOMP_NAUKY, 4, 4, 4);
			Assert::IsTrue(HasNoThrees(s));
		}

		
	};

	TEST_CLASS(CalcPercentWithoutThreesTests)
	{
	public:

		TEST_METHOD(CalcPercent_ZeroStudents_ReturnsZero)
		{
			Assert::AreEqual(0.0, CalcPercentWithoutThrees(nullptr, 0), 1e-9);
		}

		

		TEST_METHOD(CalcPercent_NoneWithoutThrees_IsZero)
		{
			Student s[2] = {
				MakeStudent("A", KOMP_NAUKY, 3, 5, 5),
				MakeStudent("B", INFORMATYKA, 4, 3, 4)
			};
			Assert::AreEqual(0.0, CalcPercentWithoutThrees(s, 2), 1e-9);
		}

		
	};


	TEST_CLASS(OutputTests)
	{
	public:

		
		TEST_METHOD(Print_ContainsHeaderAndStudentData)
		{
			Student s[1] = { MakeStudent("Ivanov", KOMP_NAUKY, 5, 4, 3) };

			CoutCapture cap;
			Print(s, 1);
			string out = cap.Str();

			Assert::IsTrue(out.find("Список студентів групи") != string::npos);
			Assert::IsTrue(out.find("Прізвище") != string::npos);
			Assert::IsTrue(out.find("Ivanov") != string::npos);
			Assert::IsTrue(out.find("Комп'ютерні науки") != string::npos);
		}
	};

	
}