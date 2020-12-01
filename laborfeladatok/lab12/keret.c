#include <stdio.h>
#include <stdlib.h>

typedef struct BiFa {
    int ertek;
    struct BiFa *bal, *jobb;
} BiFa;



BiFa *beszur(BiFa *gyoker, int ertek) {
    if (gyoker == NULL) {
        BiFa *uj = (BiFa*) malloc(sizeof(BiFa));
        uj->ertek = ertek;
        uj->bal = uj->jobb = NULL;
        return uj;
    }
    if (ertek < gyoker->ertek) {        /* balra szur */
        gyoker->bal = beszur(gyoker->bal, ertek);
    }
    else if (ertek > gyoker->ertek) {   /* jobbra szur */
        gyoker->jobb = beszur(gyoker->jobb, ertek);
    }
    else {
        /* mar benne van */
    }
    return gyoker;
}

void kiir(BiFa *gyoker){
    if(!gyoker) {
        return;
    }

    kiir(gyoker->bal);
    printf("%d ", gyoker->ertek);
    kiir(gyoker->jobb);
}

void felszabadit(BiFa *gyoker){
    if(!gyoker) {
        return;
    }

    felszabadit(gyoker->bal);
    felszabadit(gyoker->jobb);
    free(gyoker);

}

int szamlal(BiFa *gyoker){
    if(!gyoker) {
        return 0;
    }

    return szamlal(gyoker->bal) + szamlal(gyoker->jobb) + 1;
}

int osszead(BiFa *gyoker){
    if(!gyoker) {
        return 0;
    }

    return osszead(gyoker->bal) + osszead(gyoker->jobb) + gyoker->ertek;
}

BiFa* keres(BiFa *gyoker, int keresett){
    BiFa *mozgo = gyoker;
    while(mozgo && mozgo->ertek != keresett){
        if(abs(mozgo->ertek) > abs(keresett)){
            mozgo = mozgo->bal;
        } else {
            mozgo = mozgo->jobb;
        }
    }

    return mozgo;
}

void negal(BiFa *gyoker){
    if(!gyoker) {
        return;
    }

    negal(gyoker->bal);
    gyoker->ertek *= -1;
    negal(gyoker->jobb);
}

void tukroz(BiFa *gyoker){
    if(!gyoker) {
        return;
    }

    tukroz(gyoker->bal);
    tukroz(gyoker->jobb);
    BiFa *temp = gyoker->bal;
    gyoker->bal = gyoker->jobb;
    gyoker->jobb = temp;
}


int main(void) {
    int minta[] = {15, 96, 34, 12, 14, 56, 21, 11, 10, 9, 78, 43, 0};
    BiFa *gyoker = NULL;
    for (int i = 0; minta[i] > 0; i++)
        gyoker = beszur(gyoker, minta[i]);
    negal(gyoker);
    kiir(gyoker);
    printf("\n");
    printf("%d\n", szamlal(gyoker));
    printf("%d\n", osszead(gyoker));
    printf("%d\n", keres(gyoker, -34));
    tukroz(gyoker);
    negal(gyoker);
    kiir(gyoker);
    felszabadit(gyoker);

    return 0;
}
