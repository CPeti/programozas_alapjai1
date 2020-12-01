#include <stdio.h>

int main() {
    int szam;
    scanf("%d", &szam);
    int i = 2 ;
    while (i <= szam){
        if (szam % i == 0){
            printf("%3d | %d\n", szam, i);
            szam = szam / i;
        }
        else
            i += 1;
    }
    printf("%3d |", 1);
    return 0;
}
