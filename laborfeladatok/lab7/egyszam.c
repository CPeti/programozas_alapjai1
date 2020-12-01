#include <stdio.h>

int main(){
    unsigned long int a = 29;
    for (int i = 31; i >= 0; i--){
        if ((a >> i & 1) != 0)
            printf("1");
        else
            printf("0");
    }
}
