#include <stdio.h>

int keres(int *tomb, int meret, int keresett){
    for (int i = 0; i < meret; i+= 1){
        if (*(tomb+i) == keresett)
            return i;
    }
    return NULL;
}

int main(){
    int tomb[] = {0, 13, 523, 46, 73, 49, 6234, 78, 48, 986};
    for (int i = 0; i < 10; i+= 1)
        printf("[%d]=%d ", i, tomb[i]);
    printf("\n");
    int keresett = 46;
    printf("%d indexe: %d\n", keresett, keres(tomb, 10, keresett));
    printf("%d memoriacime: %p", keresett, &*(tomb+keres(tomb, 10, keresett)));
    return 0;
}
