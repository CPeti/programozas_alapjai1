#include <stdio.h>
#include <stdlib.h>

///a fuggveny kivagja egy string kivant darabjat, a kivagott darab dinamikusan lefoglalt memoriateruletenek cimet adja vissza
/// parameterek: kivagando string, elso megtartando karakter sorszama, utolso megtartando karakter utani sorszam
/// a lefoglalt memoriat a hivonak kell felszabaditani
char* resz(char string[], int elso, int utolso){
    int i;
    char *p = (char*) malloc((utolso - elso) *sizeof(char));
    for(i = 0; i < utolso-elso; i++){
        p[i] = string[i+elso];
    }
    p[i+1] = '\0';
    return p;
}

int main()
{
    char string[] = {"hello, vilag"};
    char *a = resz(string, 3, 9);
    printf("%s", a);
    free(a);
    return 0;
}
