#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* beszur(char string1[], int hely, char string2[]){
    char *p = (char*) malloc((strlen(string1) + strlen(string2) + 1) * sizeof(char));
    int i = 0;
    int pos = 0;
    while (string1[i] != '\0'){
        if (i == hely){
            int j = 0;
            while (string2[j] != '\0'){
                p[pos++] = string2[j++];
            }
        }
        p[pos++] = string1[i++];
    }
    return p;
}

int main()
{
    char *a = beszur("hello!", 5, ", vilag");
    printf("%s", a);
    free(a);
    return 0;
}
