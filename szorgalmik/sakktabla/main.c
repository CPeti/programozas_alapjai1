#include <stdio.h>
#include <stdlib.h>

int main()
{
    for (int i = 1; i < 10; i += 1){
        for (int n = 0; n < 10; n += 1)
            printf("%d ", 100 * i + 10 * n + i);
    }
    return 0;
}
