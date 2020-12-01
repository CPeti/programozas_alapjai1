#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Adj meg egy 100-nal kisebb szamot! ");
    int n;
    scanf("%d", &n);
    printf("\n");
    /* sorminta :( */
    if (n >= 100){
        printf("tul nagy a szam!");
        return 0;
    }
    if (n >= 90){
        printf("XC");
        n -= 90;
    }
    if (n >= 50){
        printf("L");
        n -= 50;
    }
    if (n >= 40){
        printf("XL");
        n -= 40;
    }
    while (n >= 10){
        printf("X");
        n -= 10;
    }
    if (n >= 9){
        printf("IX");
        n -= 9;
    }
    if (n >= 5){
        printf("V");
        n -= 5;
    }
    if (n >= 4){
        printf("IV");
        n -= 4;
        }
    while (n >= 1){
        printf("I");
        n -= 1;
    }
    return 0;
}
