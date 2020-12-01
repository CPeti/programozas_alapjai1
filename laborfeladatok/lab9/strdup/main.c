#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/// a fuggvenyt stringet tartalmazo tombre lehet meghivni, vissza a string dinamikusan foglalt masolatat adja.
/// Ha ezt a masolatot mar nem hasznaljuk, a hivonak kell felszabaditani a lefoglalt memoriateruletet.
char* masolat(char string[]){
    char *p = (char*) malloc((strlen(string)+1) * sizeof(char));
    strcpy(p, string);
    return p;
}

int main(){
    char *p = masolat("alma");
    printf("%s\n", p);
    free(p);
    return 0;
}
