#include <stdio.h>

int main(){
    unsigned long szamok[9] = {-65535, 0U, 1931988508U, 581177634U, 581374240U, 581177632U, 581177634U, 1919159836U, 0U };
    for (int n = 0; n < 10; n++){
        //szamok[n] = szamok[n] ^ 65535;
        for (int i = 31; i >= 0; i--){
            if ((szamok[n] >> i & 1) != 0)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
}
