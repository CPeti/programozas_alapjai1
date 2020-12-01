#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("hany egyseg szeles legyen a sakktabla egy mezoje? ");
    int hossz;
    scanf("%d", &hossz);
    for (int sor = 0; sor < 8 * hossz ; sor += 1){
        for (int oszlop = 0; oszlop < 8 * hossz; oszlop += 1){
            if (sor % (2 * hossz) >= hossz && oszlop % (2 * hossz) >= hossz){
                printf("X ");
            }
            else if (sor % (2 * hossz) < hossz && oszlop % (2 * hossz) < hossz){
                printf("X ");
            }
            else{
                printf(". ");
            }
        }
        printf("\n");
    }
    return 0;
}
