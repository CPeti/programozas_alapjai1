#ifndef SHOW_H_INCLUDED
#define SHOW_H_INCLUDED
#include "core.h"



extern int wx;
extern int wy;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);
Uint32 idozit(Uint32 ms, void *param);

void draw_game(snake sn1, snake sn2, coord apple, TTF_Font *font, gamemode gm,  SDL_Texture *apple_img);
void draw_screen(SDL_Texture *screen);


#endif // SHOW_H_INCLUDED
