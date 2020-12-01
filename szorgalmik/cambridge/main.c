#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void shuffle(char szo[]){
    int l = strlen(szo);
    while (!((szo[l] < 'Z' && szo[l] > 'A') || (szo[l] >= 'a' && szo[l] <= 'z')))
        l--;
    l -= 1;
    while( l-1 > 0){
        int n = rand() % (l-1)+1;
        char temp = szo[n];
        szo[n] = szo[l];
        szo[l] = temp;
        l--;
    }
    printf("%s ", szo);
}

int main(){
    srand(time(0));
    char szo[51];
    while (scanf("%s", szo)==1){
        shuffle(szo);
    }
    return 0;
}
