#include <stdio.h>

int main(){
    long long int a = 1;
    for (int i = 0; i <= 40; i++){
        a <<= 1;
        printf("%llu\n", a);
    }


    printf("\n");
    unsigned long long int j, k;
    j = 0;
    k = 1;
    int l = 0;
    while(k > j){
        j = k;
        k <<= 1;
        l++;
    }
    printf("%d\n", l);
    /*
    unsigned char:            8 bit
    unsigned short int:      16 bit
    unsigned int:            32 bit
    unsigned long int:       32 bit
    unsigned long long int:  64 bit
    */





    printf("\n");
    unsigned int b;
    printf("adj meg egy szamot! ");
    scanf("%u", &b);
    unsigned int c = 0;
    int i = 33;
    while(b > c){
        c = b;
        b <<= 1;
        i--;
    }
    printf("%d bites a megadott szam", i);
    return 0;
}
