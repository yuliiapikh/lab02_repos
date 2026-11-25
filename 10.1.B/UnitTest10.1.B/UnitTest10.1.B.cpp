#include "pch.h"
#include "CppUnitTest.h"
#include "D:/VS projects/10.1.B/students.h"
#include "D:/VS projects/10.1.B/students.cpp"

#undef IN

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

// створення студента з потрібною «третьою» оцінкою
static Student Make(const string& prizv, int kurs, Spec spec, int fiz, int mat, int third)
{
    Student st{};
    st.prizv = prizv; st.kurs = kurs; st.spec = spec;
    st.fizyka = fiz;  st.matematyka = mat;
    switch (spec)
    {
    case KN: st.prog = third; break;
    case IN: st.chysl = third; break;
    default: st.ped = third; break;
    }
    return st;
}

namespace UnitTest101B
{
    TEST_CLASS(ThirdAndAverageTests)
    {
    public:
        TEST_METHOD(ThirdGrade_KN_Prog) { Assert::AreEqual(5, ThirdGrade(Make("A", 1, KN, 3, 3, 5))); }
        TEST_METHOD(ThirdGrade_IN_Chysl) { Assert::AreEqual(4, ThirdGrade(Make("A", 1, IN, 3, 3, 4))); }
        TEST_METHOD(ThirdGrade_ME_Ped) { Assert::AreEqual(3, ThirdGrade(Make("A", 1, ME, 3, 3, 3))); }
        TEST_METHOD(ThirdGrade_TN_Ped) { Assert::AreEqual(5, ThirdGrade(Make("A", 1, TN, 3, 3, 5))); }

        TEST_METHOD(AverageGrade_Exact4) { Assert::AreEqual(4.0, AverageGrade(Make("A", 1, KN, 5, 4, 3)), 1e-9); }
        TEST_METHOD(AverageGrade_Fraction) { Assert::AreEqual(14.0 / 3.0, AverageGrade(Make("A", 1, FI, 5, 5, 4)), 1e-9); }
    };

    TEST_CLASS(NoThreesTests)
    {
    public:
        TEST_METHOD(HasNoThrees_544) { Assert::IsTrue(HasNoThrees(Make("A", 1, KN, 5, 4, 4))); }
        TEST_METHOD(HasNoThrees_555) { Assert::IsTrue(HasNoThrees(Make("A", 1, TN, 5, 5, 5))); }
        TEST_METHOD(HasNoThrees_Physics3) { Assert::IsFalse(HasNoThrees(Make("A", 1, KN, 3, 5, 5))); }
        TEST_METHOD(HasNoThrees_Math3) { Assert::IsFalse(HasNoThrees(Make("A", 1, KN, 5, 3, 5))); }
        TEST_METHOD(HasNoThrees_Third3) { Assert::IsFalse(HasNoThrees(Make("A", 1, IN, 5, 5, 3))); }

        TEST_METHOD(CountNoThrees_Group)
        {
            Student g[5] = {
                Make("Іваненко", 2, KN, 4, 5, 5),
                Make("Петренко", 1, IN, 4, 3, 3),
                Make("Коваль",   3, FI, 5, 4, 4),
                Make("Мельник",  2, ME, 5, 5, 3),
                Make("Шевченко", 4, TN, 5, 5, 5)
            };
            Assert::AreEqual(3, CountNoThrees(g, 5));
            Assert::AreEqual(1, CountNoThrees(g, 2));
        }

        TEST_METHOD(CountNoThrees_Empty)
        {
            Student g[1] = { Make("A", 1, KN, 5, 5, 5) };
            Assert::AreEqual(0, CountNoThrees(g, 0));
        }
    };

    TEST_CLASS(AverageBelow4Tests)
    {
    public:
        TEST_METHOD(Below_443) { Assert::IsTrue(HasAverageBelow4(Make("A", 1, KN, 4, 4, 3))); }
        TEST_METHOD(Equal_444) { Assert::IsFalse(HasAverageBelow4(Make("A", 1, KN, 4, 4, 4))); }
        TEST_METHOD(Equal_552) { Assert::IsFalse(HasAverageBelow4(Make("A", 1, TN, 5, 5, 2))); }
        TEST_METHOD(Below_333) { Assert::IsTrue(HasAverageBelow4(Make("A", 1, ME, 3, 3, 3))); }

        TEST_METHOD(Percent_OneOfFive)
        {
            Student g[5] = {
                Make("Іваненко", 2, KN, 4, 5, 5),
                Make("Петренко", 1, IN, 4, 3, 3),
                Make("Коваль",   3, FI, 5, 4, 4),
                Make("Мельник",  2, ME, 5, 5, 3),
                Make("Шевченко", 4, TN, 5, 5, 5)
            };
            Assert::AreEqual(20.0, PercentAverageBelow4(g, 5), 1e-9);
        }

        TEST_METHOD(Percent_AllBelow4)
        {
            Student w[2] = { Make("A", 1, KN, 3, 3, 3), Make("B", 1, IN, 2, 4, 5) };
            Assert::AreEqual(100.0, PercentAverageBelow4(w, 2), 1e-9);
        }

        TEST_METHOD(Percent_EmptyArray)
        {
            Student g[1] = { Make("A", 1, KN, 3, 3, 3) };
            Assert::AreEqual(0.0, PercentAverageBelow4(g, 0), 1e-9);
        }
    };
}