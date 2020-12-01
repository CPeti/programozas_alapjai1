#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/* ablak letrehozasa */
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
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

    *pwindow = window;
    *prenderer = renderer;
}

Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}
typedef struct coord{
    double x;
    double y;
} coord;

typedef enum s{
    start,
    moving_point1,
    moving_point2,
    moving_line,
    idle,
} s;

double dist(coord cd1, coord cd2){
    return (sqrt((cd1.x - cd2.x)*(cd1.x - cd2.x) + (cd1.y - cd2.y)*(cd1.y - cd2.y)));
}

void set(coord *cd1, coord cd2){
    cd1->x = cd2.x;
    cd1->y = cd2.y;
}

void rotate(coord *cd, double alpha){
    double temp = cos(alpha) * cd->x - sin(alpha) * cd->y;
    cd->y = sin(alpha) * cd->x + cos(alpha) * cd->y;
    cd->x = temp;
}

bool draw_ellipse(SDL_Renderer *renderer, coord p1, coord p2, double dsum){
    coord o;
    o.x = (p1.x + p2.x) / 2;
    o.y = (p1.y + p2.y) / 2;
    filledCircleRGBA(renderer, o.x, o.y, 4, 255, 255, 255, 255);
    lineRGBA(renderer, p1.x, p1.y, p2.x, p2.y, 255, 255, 255, 255);
    double c = dist(p1, p2)/2;
    double a = dsum/2;
    if (a*a < c*c) return false;
    double b = sqrt(a*a-c*c);
    coord temp1;
    coord temp2;

    double pi = 2*acos(0);
    double alpha = atan((p2.y-p1.y)/(p2.x - p1.x));


    temp2.x = a*cos(0);
    temp2.y = b*sin(0);
    rotate(&temp2, alpha);
    for(double i = 0; i <= 360; i+= 10){
        double fi = i * pi/180;
        temp1.x = a*cos(fi);
        temp1.y = b*sin(fi);
        rotate(&temp1, alpha);
        lineRGBA(renderer, o.x+temp1.x, o.y+temp1.y, o.x + temp2.x, o.y+temp2.y, 255, 255, 255, 255);
        filledCircleRGBA(renderer, o.x+temp1.x, o.y+temp1.y, 2, 255, 255, 255, 255);
        set(&temp2, temp1);
    }
    return true;
}


int main(int argc, char *argv[]) {
    /* ablak letrehozasa */
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("Ellipszis", 1000, 800, &window, &renderer);
    SDL_TimerID id = SDL_AddTimer(20, idozit, NULL);

    coord mouse;
    mouse.x = 0;
    mouse.y = 0;

    coord p1;
    p1.x = 200;
    p1.y = 300;

    coord p2;
    p2.x = 400;
    p2.y = 300;

    double dsum = 600;
    bool quit = false;

    s state = start;

    while(!quit){
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type){
            case SDL_MOUSEMOTION:
                mouse.x = event.button.x;
                mouse.y = event.button.y;

                if (state == moving_point1){
                    set(&p1, mouse);
                } else if(state == moving_point2){
                    set(&p2, mouse);
                } else if(state == moving_line){
                    dsum = dist(p2, mouse) +  dist(p1, mouse);
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    double d1 = dist(p1, mouse);
                    double d2 = dist(p2, mouse);
                    if(d1 < 10){
                        state = moving_point1;
                    }else if(d2 < 10){
                        state = moving_point2;
                    }else if(fabs(d1 + d2 - dsum) < 10){
                        state = moving_line;
                    }
                } break;

            case SDL_USEREVENT:
                /* megjelenites */
                if (state != idle){
                    boxRGBA(renderer, 0, 0, 1000, 800, 0, 0, 0, 255);
                    filledCircleRGBA(renderer, p1.x, p1.y, 10, 255, 255, 255, 255);
                    filledCircleRGBA(renderer, p2.x, p2.y, 10, 255, 255, 255, 255);
                    draw_ellipse(renderer, p1, p2, dsum);
                    SDL_RenderPresent(renderer);
                    if(state == start)
                        state = idle;
                } break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    state = idle;
                } break;

            case SDL_QUIT:
                quit = true;
                break;
        }
    }
    /* ablak bezarasa */
    SDL_RemoveTimer(id);
    SDL_Quit();

    return 0;
}
