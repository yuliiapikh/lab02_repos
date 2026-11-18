#include "pch.h"
#include "CppUnitTest.h"
#include <stdio.h>
#include "D:/VS projects/9.2.1/macros.h"      

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// перша гілка формули: 1 <= z < 10
static float w_branch1(float x, float y, float z)
{
    return SQR(MAX(x + y, x + z));
}

// друга гілка формули: z < 1 або z >= 10
static float w_branch2(float x, float y, float z)
{
    return MIN(SQR(x), 5 * ABS(y - z));
}

namespace UnitTest92
{
    TEST_CLASS(MacroTests)
    {
    public:
        TEST_METHOD(SQR_Simple) { Assert::AreEqual(25, SQR(5)); }
        TEST_METHOD(SQR_Expression) { Assert::AreEqual(25, SQR(2 + 3)); } // дужки
        TEST_METHOD(ABS_Negative) { Assert::AreEqual(3.5, ABS(-3.5), 1e-9); }
        TEST_METHOD(ABS_Positive) { Assert::AreEqual(4, ABS(4)); }
        TEST_METHOD(MAX_Two) { Assert::AreEqual(7, MAX(3, 7)); }
        TEST_METHOD(MIN_Two) { Assert::AreEqual(3, MIN(3, 7)); }
        TEST_METHOD(MAX_InsideExpr) { Assert::AreEqual(6, 2 * MAX(1, 3)); } // дужки
        TEST_METHOD(MAX_Nested) { Assert::AreEqual(9, MAX(MAX(1, 9), 4)); }
    };

    TEST_CLASS(FormulaTests)
    {
    public:
        // гілка 1: max^2(x+y, x+z)
        TEST_METHOD(Branch1_Case1) { Assert::AreEqual(36.0f, w_branch1(1, 2, 5), 1e-4f); }
        TEST_METHOD(Branch1_Case2) { Assert::AreEqual(121.0f, w_branch1(1, 10, 2), 1e-4f); }
        TEST_METHOD(Branch1_Case3) { Assert::AreEqual(4.0f, w_branch1(-5, 1, 3), 1e-4f); }

        // гілка 2: min(x^2, 5|y-z|)
        TEST_METHOD(Branch2_Case1) { Assert::AreEqual(9.0f, w_branch2(3, 2, 12), 1e-4f); }
        TEST_METHOD(Branch2_Case2) { Assert::AreEqual(5.0f, w_branch2(10, 5, 6), 1e-4f); }
        TEST_METHOD(Branch2_Case3) { Assert::AreEqual(4.0f, w_branch2(2, 0, -4), 1e-4f); }
    };
}