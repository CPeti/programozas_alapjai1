#include <stdio.h>
/*
int *f1(int i) {
    return &i; /// cim szerint probal lokalis valtozot visszaadni, az a valtozo csak a fuggvenyen belul letezik
}

int main(void) {
    int *p;
    p = f1(10);
    printf("%d\n", *p);
    printf("%d\n", *p);
    return 0;
}
*/

int *f1(int i) {
    return &i; /// cim szerint probal lokalis valtozot visszaadni, az a valtozo csak a fuggvenyen belul letezik
}

int main(void) {
    int x = 10;
    int *p = f1(x);
    printf("%d\n", *p);
    printf("%d\n", *p);
    return 0;
}
