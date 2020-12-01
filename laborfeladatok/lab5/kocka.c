#include <stdio.h>

void szamit(double oldal, double *felulet, double *terfogat){
    *felulet = 6 * oldal * oldal;
    *terfogat = oldal * oldal * oldal;
}

int main(){
    double felulet, terfogat;
    szamit(2.7, &felulet, &terfogat);
    printf("felulet= %.3f terfogat= %.3f", felulet, terfogat);
    return 0;
}
