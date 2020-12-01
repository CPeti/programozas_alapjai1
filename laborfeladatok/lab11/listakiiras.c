#include <stdlib.h>
#include <stdio.h>

typedef struct ListaElem {
    int adat;
    struct ListaElem *kov;
} ListaElem;


/* létrehoz egy listát, benne egy csomó számmal */
ListaElem *lista_letrehoz(void) {                           ///hatulrol epiti fel a lancolt listat, ezert lesz forditva
    int szamok[] = { 8, 14, 13, 17, 1, 19, 16, 5, 3, 11, 2,
                     15, 9, 10, 6, 22, 4, 7, 18, 27, -1 };
    ListaElem *lis = NULL;

    for (int i = 0; szamok[i] != -1; ++i) {
        ListaElem *u;
        u = (ListaElem*) malloc(sizeof(ListaElem));
        u->kov = lis;
        u->adat = szamok[i];
        lis = u;
    }
    return lis;
}

void kiir(ListaElem *eleje){
    ListaElem *mozgo = eleje;
    while(mozgo->kov){
        printf("%d ", mozgo->adat);
        mozgo = mozgo->kov;
    }
    if (eleje) printf("%d\n", mozgo->adat);
}

int hossz(ListaElem *eleje){
    if(!eleje) return 0;
    ListaElem *mozgo = eleje;
    int l = 1;
    while(mozgo->kov){
        l++;
        mozgo = mozgo->kov;
    }
    return l;
}

void felszabadit(ListaElem *eleje){
    ListaElem *temp;
    int n = 0;
    while (eleje){
        temp = eleje;
        eleje = temp->kov;
        free(temp);
        ///printf("%d ", ++n);
    }
}

ListaElem* lista_elejere_beszur(ListaElem *eleje, int n){
    ListaElem *uj;
    uj = (ListaElem*) malloc(sizeof(ListaElem));
    uj->adat = n;
    uj->kov = eleje;
    return uj;
}

void lista_vegehez_hozzafuz(ListaElem *eleje, int n){
    ListaElem *mozgo = eleje;
    while(mozgo->kov){
        mozgo = mozgo->kov;
    }
    ListaElem *uj;
    uj = (ListaElem*) malloc(sizeof(ListaElem));
    uj->adat = n;
    uj->kov = NULL;
    mozgo->kov = uj;
}

ListaElem* keres(ListaElem *eleje, int keresett){
    ListaElem *mozgo = eleje;
    if(mozgo->adat == keresett) return mozgo;
    while(mozgo->kov){
        mozgo = mozgo->kov;
        if(mozgo->adat == keresett)
            return mozgo;

    }
    return NULL;
}

int main(void) {
    ListaElem *eleje;

    eleje = lista_letrehoz();

    kiir(eleje);
    printf("%d\n", hossz(eleje));

    eleje = lista_elejere_beszur(eleje, 0);
    lista_vegehez_hozzafuz(eleje, 100);
    kiir(eleje);
    printf("%d", keres(eleje, 0));
    felszabadit(eleje);
    return 0;
}
