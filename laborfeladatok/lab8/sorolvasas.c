#include <stdio.h>
#include <stdlib.h>

int main(){
    char kar;
    int n = 0;
    char *tomb = (char*) malloc(n * sizeof(char));
    scanf("%c", &kar);
    /*while(kar != -1){
        tomb[n] = kar;
        n++;
        realloc(tomb, n);
        scanf("%d", &kar);

    }
    */
    while(kar != '\n'){
        char *uj = (char*) malloc((n+1) * sizeof(char));
        for (int i = 0; i < n; i++){
            uj[i] = tomb[i];
        }
        uj[n] = kar;
        n++;
        free(tomb);
        tomb = uj;
        scanf("%c", &kar);
    }
    char *uj = (char*) malloc((n+1) * sizeof(char));
    for (int i = 0; i < n; i++){
        uj[i] = tomb[i];
    }
    uj[n] = '\0';
    free(tomb);
    tomb = uj;

    printf("%s ", tomb);
    free(tomb);
    return 0;
}
