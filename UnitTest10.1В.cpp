#include "pch.h"
#include "CppUnitTest.h"
#include <sstream>
#include "../10.1/10.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests101
{
	
	Student MakeStudent(const string& prizv, Spec spec, int fizyka, int matematyka, int third)
	{
		Student s;
		s.prizv = prizv;
		s.kurs = 2;
		s.spec = spec;
		s.fizyka = fizyka;
		s.matematyka = matematyka;
		s.pedahohika = third;   
		return s;
	}

	TEST_CLASS(GetThirdGradeTests)
	{
	public:

		TEST_METHOD(GetThirdGrade_KomputerniNauky_Prohramuvannya)
		{
			Student s = MakeStudent("A", KOMP_NAUKY, 5, 5, 0);
			s.prohramuvannya = 4;
			Assert::AreEqual(4, GetThirdGrade(s));
		}

		
	};

	TEST_CLASS(HasNoThreesTests)
	{
	public:

		TEST_METHOD(HasNoThrees_True_AllFivesAndFours)
		{
			Assert::IsTrue(HasNoThrees(MakeStudent("A", KOMP_NAUKY, 5, 4, 5)));
			Assert::IsTrue(HasNoThrees(MakeStudent("A", MAT_EKON, 4, 4, 4)));
		}

		
	};

	TEST_CLASS(CalcPercentWithoutThreesTests)
	{
	public:

		TEST_METHOD(CalcPercent_EmptyArray_Zero)
		{
			Student s[1];
			Assert::AreEqual(0.0, CalcPercentWithoutThrees(s, 0), 0.001);
		}

		
	};

	TEST_CLASS(FindSurnamesPhysics5or4Tests)
	{
	public:

		TEST_METHOD(FindSurnames_FiveAndFourFound_OthersSkipped)
		{
			Student s[4] = { MakeStudent("Ivanenko", KOMP_NAUKY, 5, 3, 3),
							 MakeStudent("Petrenko", INFORMATYKA, 3, 5, 5),
							 MakeStudent("Sydorenko", TRUD_NAV, 4, 3, 3),
							 MakeStudent("Koval", FIZ_INF, 2, 5, 5) };

			vector<string> res = FindSurnamesPhysics5or4(s, 4);

			Assert::AreEqual((size_t)2, res.size());
			Assert::AreEqual(string("Ivanenko"), res[0]);
			Assert::AreEqual(string("Sydorenko"), res[1]);
		}

		
	};
}
