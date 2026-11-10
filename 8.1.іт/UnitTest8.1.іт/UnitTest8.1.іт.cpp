#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include "CppUnitTest.h"
#include "D:/VS projects/8.1.іт/8.1.іт.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestIterative
{
    TEST_CLASS(UnitTestIterative)
    {
    public:

        TEST_METHOD(TestCount)
        {
            char str1[] = "a+b-c=";
            Assert::AreEqual(3, Count(str1));

            char str2[] = "abcXYZ123";
            Assert::AreEqual(0, Count(str2));
        }

        TEST_METHOD(TestChange)
        {
            char str1[50] = "a+b-c=";
            char* dest1 = Change(str1);

            Assert::AreEqual("a**b**c**", str1);
            Assert::AreEqual("a**b**c**", dest1);

            delete[] dest1;
        }
    };
}