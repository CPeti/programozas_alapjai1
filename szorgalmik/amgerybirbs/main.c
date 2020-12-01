#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
double rad(double angle);
double dist(double x1, double y1, double x2, double y2);

int main(){
    FILE* fp;
    fp = fopen("angry.svg", "w");
    ///1px = 1cm, a program a feladat adatain hasznalja, csak a madar es a malac kirajzolt merete nagyobb a szebb abra erdekeben
    ///vaszon szelessege, hosszusaga
    int cw = 3500;
    int ch = 2000;
    fprintf(fp, "<svg width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">", cw, ch);

    ///hatter
    fprintf(fp, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"%s\" fill=\"%s\"/>", 0, 0, cw, ch, "black", "azure");
    fprintf(fp, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"%s\" fill=\"%s\"/>", 0, ch - 30, cw, ch, "black", "green");

    ///talpak
    fprintf(fp, "<polygon points=\"%d, %d %d, %d %d, %d %d, %d\" stroke=\"%s\" fill=\"%s\"/>", cw - 450, ch - 30, cw - 400, ch - 130, cw - 100, ch - 130, cw - 50, ch - 30, "black", "saddlebrown");
    fprintf(fp, "<polygon points=\"%d, %d %d, %d %d, %d %d, %d\" stroke=\"%s\" fill=\"%s\"/>", 850, ch - 30, 800, ch - 130, 500, ch - 130, 450, ch - 30, "black", "saddlebrown");

    ///oszlopok
    fprintf(fp, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"%s\" fill=\"%s\"/>", cw - 300, ch - 550, 100, 550 - 130, "black", "gray");
    fprintf(fp, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"%s\" fill=\"%s\"/>", cw - 450, ch - 650, 400, 100, "black", "gray");

    ///madar(x1, y1) es malac(x1. y1)
    int r = 50;
    double x1 = 250;
    double x2 = 3250;
    double y1 = 1700;
    double y2 = 1300;
    fprintf(fp, "<circle cx=\"%f\" cy=\"%f\" r=\"%d\" stroke=\"%s\" fill=\"%s\" />", x1, y1, r, "black", "red");
    fprintf(fp, "<circle cx=\"%f\" cy=\"%f\" r=\"%d\" stroke=\"%s\" fill=\"%s\" />", x2, y2, r, "black", "green");

    ///csuzli
    int cs_x = 650;
    fprintf(fp, "<polygon points=\"%d, %d %d, %d %d, %d %d, %d %d, %d %d, %d %d, %d %d, %d %d, %d\" stroke=\"%s\" fill=\"%s\"/>", cs_x - 50, ch - 130, cs_x - 50, ch - 430, cs_x - 250, ch - 630, cs_x - 200, ch - 680, cs_x, ch - 483, cs_x + 200, ch - 680, cs_x + 250, ch - 630, cs_x + 50, ch - 430, cs_x + 50, ch - 130, "black", "sienna");
    fprintf(fp, "<line x1=\"%d\" x2=\"%f\" y1=\"%d\" y2=\"%f\" stroke=\"%s\" stroke-width=\"%d\"/>", cs_x - 125, x1, ch - 605, y1, "maroon", 15);
    fprintf(fp, "<line x1=\"%d\" x2=\"%f\" y1=\"%d\" y2=\"%f\" stroke=\"%s\" stroke-width=\"%d\"/>", cs_x + 140, x1, ch - 605, y1, "maroon", 15);
    fprintf(fp, "<line x1=\"%d\" x2=\"%d\" y1=\"%d\" y2=\"%d\" stroke=\"%s\" stroke-width=\"%d\"/>", cs_x + 130, cs_x + 180, ch - 605, ch - 560, "maroon", 15);

    ///palya szamitasai
    double g = 981;
    for (double angle = 10; angle <= 60; angle += 5){
        for ( double speed = 1000; speed <= 3000; speed += 100){
            double x = x1;
            double y = y1;
            double targetx = x2;
            double targety = y2;
            double speedx = speed * cos(rad(angle));
            double speedy = speed * sin(rad(angle));
            double t = 0.01;
            bool hit = false;
            while (x < cw && y < ch && x > 0 && y > 0 && !hit){
                ///evem mozgas
                x = x + speedx * t;
                ///evev mozgas
                y = y - speedy * t + g/2 * t * t;
                speedy -= g * t;
                if (dist(x, y, targetx, targety)< 2 * r){
                    hit = true;
                }
            }
            ///kirajzolas, cikluson kivul
            if (hit){
                ///madar helye a talalat idopontjaban
                fprintf(fp, "<circle cx=\"%f\" cy=\"%f\" r=\"%d\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.1\"/>", x, y, r, "black", "red");
                fprintf(fp, "<circle cx=\"%f\" cy=\"%f\" r=\"%d\" stroke=\"%s\" fill=\"%s\" />", x, y, 5, "black", "black");
                ///valtozok visszaallitasa
                x = x1;
                y = y1;
                targetx = x2;
                targety = y2;
                speedx = speed * cos(rad(angle));
                speedy = speed * sin(rad(angle));
                t = 0.1;
                ///palya kirajzolasa
                double xtemp = x;
                double ytemp = y;
                while (x < cw && y < ch && x > 0){
                    x = x + speedx * t;
                    y = y - speedy * t + g/2 * t * t;
                    speedy -= g * t;
                    fprintf(fp, "<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"%d\"/>", x, xtemp, y, ytemp, "black", 3);
                    xtemp = x;
                    ytemp = y;
                }
            }

        }
    }

    fprintf(fp, "</svg>");
    fclose(fp);
    return 0;
}

double rad(double angle){
    double pi = acos(-1);
    return (angle /180 * pi);
}

double dist(double x1, double y1, double x2, double y2){
    return (sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
}

