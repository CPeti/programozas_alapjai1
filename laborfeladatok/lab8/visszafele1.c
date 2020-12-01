#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("milyen hosszu? ");
    scanf("%d", &n);
    int* tomb;
    tomb = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        printf("%d. szam: ", i);
        scanf("%d", tomb+i);
    }
    for (int i = n-1; i > 0; i--){
        printf("%d ", tomb[i]);
    }
    free(tomb);
    return 0;
}
