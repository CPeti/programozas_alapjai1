#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///a fuggveny kivagja a stringbol megadott indexek kozotti darabot, megmaradt darab dinamikusan lefoglalt memoriateruletenek cimet adja vissza
/// parameterek: kivagando string, elso kivagando karakter sorszama, utolso kivagando karakter utani sorszam
/// a lefoglalt memoriat a hivonak kell felszabaditani
char* resz(char string[], int elso, int utolso){
    int i = 0;
    int pos = 0;
    char *p = (char*) malloc((strlen(string) - (utolso - elso)+1) * sizeof(char));
    while (string[i] != '\0'){
        if (i == elso) i = utolso;
        p[pos++] = string[i++];
    }
    return p;
}

int main()
{
    char string[] = {"hello, vilag"};
    char *a = resz(string, 4, 8);
    printf("%s", a);
    free(a);
    return 0;
}
