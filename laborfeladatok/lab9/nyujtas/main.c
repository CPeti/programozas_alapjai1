#include <stdio.h>
#include <stdlib.h>
#include<string.h>
///#include "debugmalloc.h"

/// a fuggvenyt stringet tartalmazo tombre lehet meghivni, vissza a string dinamikusan foglalt masolatat adja.
/// Ha ezt a masolatot mar nem hasznaljuk, a hivonak kell felszabaditani a lefoglalt memoriateruletet.
char* masolat(char string[]){
    char *p = (char*) malloc((strlen(string)+1) * sizeof(char));
    strcpy(p, string);
    return p;
}

///a fuggveny ket parameterkent kapott stringet fuz ossze az elso helyen, aminek dinamikusan kell lefoglalva lennie, es ennek kell lennie az elso parameternek
///az osszefuzott string felszabaditasa a hivo feladata
char* hozzafuz(char string1[], char string2[]){
    char *p = (char*) malloc ((strlen(string1) + strlen(string2) + 1) * sizeof(char));
    strcpy(p, string1);
    strcat(p, string2);
    free(string1);
    return p;
}

int main(){
    char *x = masolat("alma");  /* az elozo feladatbol */

    x = hozzafuz(x, "fa");
    printf("%s\n", x);    /* almafa */

    free(x);

    return 0;
}
