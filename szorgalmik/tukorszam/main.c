#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("hany egyseg szeles legyen a sakktabla egy mezoje? ");
    int hossz;
    scanf("%d", &hossz);
    for (int mezo = 0; mezo < 64 * hossz * hossz ; mezo += 1){
        if ((mezo % (2 * hossz) < hossz && mezo % (hossz * hossz * 16) < (hossz * hossz * 8)) || (mezo % (2 * hossz) >= hossz && mezo % (hossz * hossz * 16) > (hossz * hossz * 8)))
            printf("X ");
        else
            printf(". ");
        if (mezo % (8 * hossz) == 8 * hossz - 1)
            printf("\n");
    }
    return 0;
}
