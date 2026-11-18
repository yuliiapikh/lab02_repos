// Lab_9_1_UnitTest.cpp

#include "pch.h"
#include "CppUnitTest.h"
#include <math.h>

#include "D:/VS projects/9.1/var.cpp"
#include "D:/VS projects/9.1/dod.cpp"
#include "D:/VS projects/9.1/sum.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest91
{
    TEST_CLASS(DodTests)
    {
    public:
        // a = 2, x = 2, n = 3  =>  a = 2 * (-2 / 3) = -4/3
        TEST_METHOD(RecurrenceCoefficient_Minus_X_Div_N)
        {
            nsVar::x = 2; nsVar::n = 3; nsVar::a = 2;
            nsDod::dod();
            Assert::AreEqual(-4.0 / 3.0, nsVar::a, 1e-12);
        }

        // перший доданок: a = 1, x = 1, n = 1  =>  a = -1
        TEST_METHOD(FirstTerm_Is_Minus_X)
        {
            nsVar::x = 1; nsVar::n = 1; nsVar::a = 1;
            nsDod::dod();
            Assert::AreEqual(-1.0, nsVar::a, 1e-12);
        }
    };

    TEST_CLASS(SumTests)
    {
    public:
        // x = 0  =>  exp(0) = 1, один доданок
        TEST_METHOD(Sum_X_Zero)
        {
            nsVar::x = 0; nsVar::e = 0.0001;
            nsSum::sum();
            Assert::AreEqual(1.0, nsVar::s, 1e-12);
            Assert::AreEqual(1, nsVar::n);
        }

        // x = 1, e = 0.0001  =>  s ~ exp(-1), 8 доданків
        TEST_METHOD(Sum_X_One)
        {
            nsVar::x = 1; nsVar::e = 0.0001;
            nsSum::sum();
            Assert::AreEqual(exp(-1.0), nsVar::s, nsVar::e);
            Assert::AreEqual(8, nsVar::n);
        }

        // x = -1  =>  s ~ exp(1)
        TEST_METHOD(Sum_X_MinusOne)
        {
            nsVar::x = -1; nsVar::e = 0.0001;
            nsSum::sum();
            Assert::AreEqual(exp(1.0), nsVar::s, nsVar::e);
        }

        // x = 2, e = 0.001  =>  s ~ exp(-2), 10 доданків
        TEST_METHOD(Sum_X_Two)
        {
            nsVar::x = 2; nsVar::e = 0.001;
            nsSum::sum();
            Assert::AreEqual(exp(-2.0), nsVar::s, nsVar::e);
            Assert::AreEqual(10, nsVar::n);
        }

        // серія значень x від -3 до 3 з точністю 1e-6
        TEST_METHOD(Sum_Series_Of_X)
        {
            for (double xx = -3; xx <= 3.0001; xx += 0.5) {
                nsVar::x = xx; nsVar::e = 1e-6;
                nsSum::sum();
                Assert::AreEqual(exp(-xx), nsVar::s, 1e-5);
            }
        }
    };
}