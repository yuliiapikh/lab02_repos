#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <math.h>
#include "macros.h"               

#define Z 5                         

int main()
{
    puts("Lab 9.2. Using macros and preprocessing directives");

    float x, y, w;                  
    char ch;                        // відповідь: чи продовжувати програму

    do
    {
        puts("Input x and y");
        printf("x = "); scanf("%f", &x);
        printf("y = "); scanf("%f", &y);

#if (Z >= 1) && (Z < 10)            // якщо 1 <= z < 10 – компілюється ця гілка
        w = SQR(MAX(x + y, x + Z));
#else                               // якщо z < 1 або z >= 10 – ця гілка
        w = MIN(SQR(x), 5 * ABS(y - Z));
#endif                              // завершення блоку умовної компіляції

        PRINTR(w);                  // макрос виведення результату

        puts("Repeat? y/n");
        scanf(" %c", &ch);
    } while (ch == 'y');

    return 0;
}