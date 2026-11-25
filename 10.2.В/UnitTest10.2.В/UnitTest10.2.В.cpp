#include "pch.h"
#include "CppUnitTest.h"
#include "D:/VS projects/10.2.В/students.h"
#include "D:/VS projects/10.2.В/students.cpp"

#undef IN

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

static Student Make(const string& prizv, int kurs, Spec spec)
{
    Student st{};
    st.prizv = prizv; st.kurs = kurs; st.spec = spec;
    st.fizyka = 4; st.matematyka = 4;
    st.ped = 4; // третя оцінка (поле об’єднання)
    return st;
}

// тестовий набір з 6 студентів (початковий порядок – невпорядкований)
static void Fill(Student* g)
{
    g[0] = Make("Петренко", 2, ME);
    g[1] = Make("Іваненко", 1, KN);
    g[2] = Make("Коваль", 1, IN);
    g[3] = Make("Бойко", 1, IN);
    g[4] = Make("Мельник", 2, FI);
    g[5] = Make("Шевченко", 2, ME);
}

namespace UnitTest102B
{
    TEST_CLASS(CompareUkrTests)
    {
    public:
        TEST_METHOD(Order_Basic)
        {
            Assert::IsTrue(CompareUkr("Бойко", "Коваль") < 0);
            Assert::IsTrue(CompareUkr("Коваль", "Бойко") > 0);
            Assert::AreEqual(0, CompareUkr("Мельник", "Мельник"));
            Assert::AreEqual(0, CompareUkr("мельник", "МЕЛЬНИК"));
        }

        TEST_METHOD(Order_UkrainianAlphabet)
        {
            Assert::IsTrue(CompareUkr("Ігор", "Идель") > 0);
            Assert::IsTrue(CompareUkr("Ігор", "Йосип") < 0);
            Assert::IsTrue(CompareUkr("Гнатюк", "Ґудзь") < 0);
            Assert::IsTrue(CompareUkr("Ґудзь", "Давиденко") < 0);
            Assert::IsTrue(CompareUkr("Ешбі", "Єфремов") < 0);
            Assert::IsTrue(CompareUkr("Єфремов", "Жук") < 0);
        }

        TEST_METHOD(Prefix_And_Apostrophe)
        {
            Assert::IsTrue(CompareUkr("Ковал", "Коваль") < 0);
            Assert::AreEqual(0, CompareUkr("Дзю'ба", "Дзю’ба"));
        }
    };

    TEST_CLASS(CompareKeysTests)
    {
    public:
        TEST_METHOD(ByCourse)
        {
            Assert::IsTrue(CompareKeys(1, FI, "Я", 2, KN, "А", true) < 0);
        }

        TEST_METHOD(BySpecName)
        {
            Assert::IsTrue(CompareKeys(1, IN, "Я", 1, KN, "А", true) < 0);
            Assert::IsTrue(CompareKeys(2, ME, "А", 2, FI, "Я", false) < 0);
        }

        TEST_METHOD(BySurname_Direction)
        {
            Assert::IsTrue(CompareKeys(1, KN, "Коваль", 1, KN, "Бойко", true) < 0);
            Assert::IsTrue(CompareKeys(1, KN, "Коваль", 1, KN, "Бойко", false) > 0);
            Assert::AreEqual(0, CompareKeys(3, TN, "Лис", 3, TN, "Лис", true));
        }

        TEST_METHOD(Physical_And_Indexed)
        {
            Assert::IsTrue(ComparePhysical(Make("Коваль", 1, IN), Make("Бойко", 1, IN)) < 0);
            Assert::IsTrue(CompareIndexed(Make("Бойко", 1, IN), Make("Коваль", 1, IN)) < 0);
        }
    };

    TEST_CLASS(PhysicalSortTests)
    {
    public:
        TEST_METHOD(Sort_Group)
        {
            Student g[6];
            Fill(g);
            Assert::IsFalse(IsSortedPhysically(g, 6));

            Sort(g, 6);
            Assert::AreEqual(string("Коваль"), g[0].prizv);
            Assert::AreEqual(string("Бойко"), g[1].prizv);
            Assert::AreEqual(string("Іваненко"), g[2].prizv);
            Assert::AreEqual(string("Шевченко"), g[3].prizv);
            Assert::AreEqual(string("Петренко"), g[4].prizv);
            Assert::AreEqual(string("Мельник"), g[5].prizv);
            Assert::IsTrue(IsSortedPhysically(g, 6));
        }

        TEST_METHOD(Sort_Empty)
        {
            Student g[6];
            Fill(g);
            Sort(g, 6);

            Assert::IsTrue(IsSortedPhysically(g, 0));
            Sort(g, 0);
            Assert::AreEqual(string("Коваль"), g[0].prizv);
        }
    };

    TEST_CLASS(IndexSortAndSearchTests)
    {
    public:
        TEST_METHOD(IndexSort_OrderAndImmutability)
        {
            Student h[6];
            Fill(h);
            int* I = IndexSort(h, 6);

            Assert::AreEqual(3, I[0]); // Бойко
            Assert::AreEqual(2, I[1]); // Коваль
            Assert::AreEqual(1, I[2]); // Іваненко
            Assert::AreEqual(0, I[3]); // Петренко
            Assert::AreEqual(5, I[4]); // Шевченко
            Assert::AreEqual(4, I[5]); // Мельник

            Assert::AreEqual(string("Петренко"), h[0].prizv);
            Assert::AreEqual(string("Шевченко"), h[5].prizv);

            delete[] I;
        }

        TEST_METHOD(IndexBinSearch_FoundAndNotFound)
        {
            Student h[6];
            Fill(h);
            int* I = IndexSort(h, 6);

            Assert::AreEqual(0, IndexBinSearch(h, I, 6, "Бойко", 1, IN));
            Assert::AreEqual(5, IndexBinSearch(h, I, 6, "Мельник", 2, FI));
            Assert::AreEqual(3, IndexBinSearch(h, I, 6, "Петренко", 2, ME));
            Assert::AreEqual(3, IndexBinSearch(h, I, 6, "петренко", 2, ME));

            Assert::AreEqual(-1, IndexBinSearch(h, I, 6, "Петренко", 3, ME));
            Assert::AreEqual(-1, IndexBinSearch(h, I, 6, "Петренко", 2, FI));
            Assert::AreEqual(-1, IndexBinSearch(h, I, 6, "Сидоренко", 1, KN));
            Assert::AreEqual(-1, IndexBinSearch(h, I, 0, "Бойко", 1, IN));

            delete[] I;
        }
    };

    TEST_CLASS(BinSearchTests)
    {
    public:
        TEST_METHOD(BinSearch_AllElements)
        {
            Student g[6];
            Fill(g);
            Sort(g, 6);

            Assert::AreEqual(0, BinSearch(g, 6, "Коваль", 1, IN));
            Assert::AreEqual(5, BinSearch(g, 6, "Мельник", 2, FI));
            Assert::AreEqual(2, BinSearch(g, 6, "Іваненко", 1, KN));
            Assert::AreEqual(3, BinSearch(g, 6, "Шевченко", 2, ME));

            for (int i = 0; i < 6; i++)
                Assert::AreEqual(i, BinSearch(g, 6, g[i].prizv, g[i].kurs, g[i].spec));
        }

        TEST_METHOD(BinSearch_NotFoundAndEdgeCases)
        {
            Student g[6];
            Fill(g);
            Sort(g, 6);

            Assert::AreEqual(-1, BinSearch(g, 6, "Коваль", 2, IN));
            Assert::AreEqual(-1, BinSearch(g, 6, "Коваль", 1, KN));
            Assert::AreEqual(-1, BinSearch(g, 6, "Сидоренко", 1, KN));
            Assert::AreEqual(-1, BinSearch(g, 0, "Коваль", 1, IN));
            Assert::AreEqual(0, BinSearch(g, 1, "Коваль", 1, IN));
        }
    };
}