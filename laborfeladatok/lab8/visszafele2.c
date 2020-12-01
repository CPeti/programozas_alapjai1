#include <stdio.h>
#include <stdlib.h>

int main(){
    int szam;
    int n = 0;
    int *tomb = (int*) malloc(n * sizeof(int));
    printf("%d. szam: ", n);
    scanf("%d", &szam);
    /*while(szam != -1){
        tomb[n] = szam;
        n++;
        realloc(tomb, n);
        scanf("%d", &szam);

    }
    */
    while(szam != -1){
        int *uj = (int*) malloc((n+1) * sizeof(int));
        for (int i = 0; i < n; i++){
            uj[i] = tomb[i];
        }
        uj[n] = szam;
        n++;
        free(tomb);
        tomb = uj;
        printf("%d. szam: ", n);
        scanf("%d", &szam);
    }
    for (int i = n-1; i >= 0; i--){
        printf("%d ", tomb[i]);
    }
    free(tomb);
    return 0;
}
