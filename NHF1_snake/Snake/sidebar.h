#ifndef SIDEBAR_H_INCLUDED
#define SIDEBAR_H_INCLUDED
#include <stdbool.h>
#include "core.h"

extern int wx;
extern int wy;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
typedef struct button{int x1; int y1; int width; int height; char text[20]; bool clicked;} button;
typedef struct highscore{char name[20]; int score;} highscore;

bool button_check(button *bt, int mousex, int mousey, bool click);
button** build_menu();
void draw_menu(button **menu, TTF_Font *font, int mousex, int mousey, bool click);
bool update_leaderboard(char filename[], highscore **ldr, snake sn, char name[]);
highscore**  read_leaderboard(char filename[]);
void draw_leaderboard(highscore **ldr, TTF_Font *font);
void destroy_menu(button **menu);
void destroy_leaderboard(highscore **ldr);
bool input_text(char *dest, size_t hossz, TTF_Font *font);

#endif // SIDEBAR_H_INCLUDED
