#include <stdio.h>

int main(void) {
    printf("1. %g\n", 1e40 / 1e-40); //normal alakban irja ki
    printf("2. %g\n", 1e40f / 1e-40f); //meghaladja a float maximalis meretet(64bit), nem lehet kirni
    printf("3. %g\n", 1e40); //normal alakban irja ki
    printf("4. %f\n", 1e40); //floatkent irja ki
    printf("5. %s\n", 1e3+1 == 1e3 ? "igaz" : "hamis"); //hamis, 1000hez meg pontosan hozzá tud adni 1-et
    printf("6. %s\n", 1e30+1 == 1e30 ? "igaz" : "hamis"); //igaz 10^30 tul nagy ahhoz hogy 1-et hozza lehessen adni normal alakban, keretkive lesz 10^30-ra

    return 0;
}
