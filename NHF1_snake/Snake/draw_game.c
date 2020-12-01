#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "draw_game.h"
#include <stdio.h>


;


void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
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
static void draw_grid(){
    for (int gridx = 0; gridx < n + 1; gridx++){
        for (int gridy = 0; gridy < n + 1; gridy++){
            thickLineRGBA(renderer, 0, gridy * (wy/n), wy, gridy * (wy/n), 1, 50, 50, 50, 255);
            thickLineRGBA(renderer, gridx * (wy/n), 0, gridx * (wy/n), wy, 1, 50, 50, 50, 255);
        }
    }
}
static void draw_apple(coord apple, SDL_Texture *img){
    SDL_Rect src = {0, 0, 32, 32};
    SDL_Rect dest = {apple.x*(wy/n), apple.y*(wy/n), wy/n, wy/n};
    SDL_RenderCopy(renderer, img, &src, &dest);
}
static void draw_snake(snake sn){
    body *moving = sn.head->next;
    int i = 0;
    int d = wy/n;
    if (sn.head) boxRGBA(renderer, sn.head->pos.x*(d), sn.head->pos.y*(d), (sn.head->pos.x+1)*(d)-1, (sn.head->pos.y+1)*(d)-1, sn.c.r, sn.c.g, sn.c.b, 255);
    while(moving){
        boxRGBA(renderer, moving->pos.x*(d), moving->pos.y*(d), (moving->pos.x+1)*(d)-1, (moving->pos.y+1)*(d)-1, sn.c.r, sn.c.g, sn.c.b, 255);
        moving = moving->next;
        i++;
    }
}
static void show_score(snake sn, int x, int y, TTF_Font *font){
    SDL_Surface *felirat;
    SDL_Texture *felirat_t;

    SDL_Color color = {255, 255, 255};
    char sscore[5];
    sprintf(sscore, "%d", sn.score);

    SDL_Rect hova = { x-strlen(sscore)*20, y, strlen(sscore)*40, 50 };
    felirat = TTF_RenderUTF8_Blended(font, sscore, color);
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
}
void draw_game(snake sn1, snake sn2, coord apple, TTF_Font *font, gamemode gm,  SDL_Texture *apple_img){
    boxRGBA(renderer, 0, 0, wy-1, wy-1, 0, 0, 0, 255);
    draw_snake(sn1);
    if (gm == duo) draw_snake(sn2);
    draw_apple(apple, apple_img);
    draw_grid();
    if (gm == solo)show_score(sn1, 400, 15, font);
    else {show_score(sn1, 100, 15, font); show_score(sn2, 700, 15, font);}
}
void draw_screen(SDL_Texture *screen){
    SDL_Rect src = {0, 0, 400, 400};
    SDL_Rect dest = {0, 0, 800, 800};
    SDL_RenderCopy(renderer, screen, &src, &dest);
}


