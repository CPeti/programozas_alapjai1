#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    FILE* fp;
    fp = fopen("ora.svg", "w");

    int h, m, s;
    printf("Adja meg az idot, szokozzel elvalasztva, h/m/s formatumban: ");
    scanf("%d %d %d", &h, &m, &s);
    h = h % 12;
    m = m % 60;
    s = s % 60;

    /* segegvaltozok */
    float rs = s;
    float rm = m + rs/60;
    float rh = h + rm/60;
    double pi = acos(-1);
    float rad = pi / 180;

    fprintf(fp, "<svg width=\"210\" height=\"210\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">");

    /* oralap */
    fprintf(fp, "<circle cx=\"100\" cy=\"100\" r=\"100\" stroke=\"black\" fill=\"black\" />");
    fprintf(fp, "<circle cx=\"100\" cy=\"100\" r=\"97\" stroke=\"lemonchiffon\" fill=\"lemonchiffon\" />");

    /* beosztas */
    for (float i = 0; i < 60; i += 1){
        if ((int)i % 5 != 0){
            float x = sin(i * 6 * rad) * 95;
            float y = -cos((i * 6) * rad) * 95;
            fprintf(fp, "<line x1=\"100\" y1=\"100\" x2=\"%f\" y2=\"%f\" stroke=\"black\" />", x + 100, y + 100);
        }
    }
    fprintf(fp, "<circle cx=\"100\" cy=\"100\" r=\"90\" stroke=\"lemonchiffon\" fill=\"lemonchiffon\" />");
    for (float i = 0; i < 60; i += 5){
        float x = sin(i * 6 * rad) * 95;
        float y = -cos((i * 6) * rad) * 95;
        fprintf(fp, "<line x1=\"100\" y1=\"100\" x2=\"%f\" y2=\"%f\" stroke=\"black\" />", x + 100, y + 100);
    }
    fprintf(fp, "<circle cx=\"100\" cy=\"100\" r=\"86\" stroke=\"lemonchiffon\" fill=\"lemonchiffon\" />");

    /* masodpercmutato */
    float x = round( sin(rs * 6 * rad) * 70);
    float y = -round( cos((rs * 6) * rad) * 70);
    fprintf(fp, "<line x1=\"100\" y1=\"100\" x2=\"%f\" y2=\"%f\" stroke=\"lightcoral\" />", x + 100, y + 100);

    /* precmutato */
    x = sin(rm * 6 * rad) * 60;
    y = -1* cos((rm * 6) * rad) * 60;
    fprintf(fp, "<line x1=\"100\" y1=\"100\" x2=\"%f\" y2=\"%f\" stroke=\"teal\" />", x + 100, y + 100);

    /* oramutato*/
    x = sin(rh*30*rad)*50;
    y = -1*cos((rh*30)*rad)*50;
    fprintf(fp, "<line x1=\"100\" y1=\"100\" x2=\"%f\" y2=\"%f\" stroke=\"black\" />", x + 100, y + 100);

    /* kozeppont */
    fprintf(fp, "<circle cx=\"100\" cy=\"100\" r=\"5\" stroke=\"black\" fill=\"teal\" />");
    fprintf(fp, "<circle cx=\"100\" cy=\"100\" r=\"4\" stroke=\"teal\" fill=\"lightcoral\" />");
    fprintf(fp, "</svg>");
    fclose(fp);
    return 0;
}
