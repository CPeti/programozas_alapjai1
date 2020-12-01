#include <stdio.h>

int main(void) {
    signed char i = 1;
    while (i > 0) {
        ++i;
    }
    printf("%d\n", i);

    return 0;
}
/*
int: -2147483648 = -2^31, signed int tartomanya -2^31 - 2^31-1, ide csordul tovabb ha tullepi a maximalis erteket;
signed short int: -32768, short int tartomanya -(2^15) - 2^15-1;
signed char: -(2^8) - 2^8-1 a tartomanya, -128ra csordul tul
*/
