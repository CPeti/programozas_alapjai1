#include <stdio.h>
void show(unsigned long tomb[], int meret){
    for (int n = 0; n < meret; n++){
        for (int i = 0; i < 32; i++){
            if ((tomb[n] >> i & 1) != 0)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void clean(unsigned long tomb[], int meret){
    for (int i = 0; i < meret; i++)
        tomb[i] = 0;
    show(tomb, meret);
}

void draw(int x, int y, unsigned long tomb[], int meret){
    unsigned long a = 1 << x;
    tomb[y] = (tomb[y] + a);
}

int main(){
    unsigned long tomb[24] = {0};
    clean(tomb, 24);
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if (i > 5 && i < 25 && j > 5 && j < 15)
                draw(i, j, tomb, 24);
        }
    }
    show(tomb, 24);
    return 0;
}
