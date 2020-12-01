#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>

double dist(double x1, double y1, double x2, double y2);

/* A porgram kerete az "Elso program" peldabol lett atveve */
int main(int argc, char *argv[]) {
    /* SDL inicializálása és ablak megnyitása */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    int wx = 640;
    int wy = 480;
    SDL_Window *window = SDL_CreateWindow("Azon pontok halmaza...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    /* rajzok */
    double eps = 5;

    for (double x = 0; x < wx; x++){
        for (double y = 0; y < wy; y++){
            if (fabs(dist(x, y, 320, 240) - 200) < eps){
                pixelRGBA(renderer, x, y, 255, 0, 0, 255);
            }
            if (fabs(dist(x, y, 240, 200) + dist(x, y, 400, 280)  - 200) < eps){
                pixelRGBA(renderer, x, y, 0, 255, 0, 255);
            }
            if (fabs(fabs(dist(x, y, 240, 240) - dist(x, y, 400, 240))  - 100) < eps){
                pixelRGBA(renderer, x, y, 0, 0, 255, 255);
            }
            if (fabs(dist(x, y, 320, 240) - fabs(x - 400)) < eps){
                pixelRGBA(renderer, x, y, 255, 255, 255, 255);
            }
        }
    }

    /* szoveg */
    stringRGBA(renderer, 30, 200, "Kor", 255, 0, 0, 255);
    stringRGBA(renderer, 30, 210, "Ellipszis", 0, 255, 0, 255);
    stringRGBA(renderer, 30, 220, "Hiperbola", 0, 0, 255, 255);
    stringRGBA(renderer, 30, 230, "Parabola", 255, 255, 255, 255);


    /* az elvegzett rajzolasok a kepernyore */
    SDL_RenderPresent(renderer);

    /* varunk a kilepesre */
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        /* SDL_RenderPresent(renderer); - MacOS Mojave esetén */
    }

    /* ablak bezarasa */
    SDL_Quit();

    return 0;
}

double dist(double x1, double y1, double x2, double y2){
    return (sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
}

