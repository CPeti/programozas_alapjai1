#include <stdio.h>

void trim(char *forras, int forrasmeret, char *cel){
    int firstchar, lastchar;
    for(int i = 0; i < forrasmeret; i++){
        if (forras[i] != ' '){
            firstchar = i;
            break;
        }
    }
    for(int i = forrasmeret-1; i>=0; i-=1){
        if (forras[i] != '\0'&& forras[i] != ' '){
            lastchar = i;
            break;
        }
    }

    for(int i = firstchar; i <= lastchar; i++){
        cel[i-firstchar] = forras[i];

    }
}
int main(){
    char forras[] = "              hello, mizu?     ";
    char cel[sizeof(forras)];
    trim("              hello, mizu?          ", sizeof(forras), cel);
    printf("%s", cel);
    return 0;
}
