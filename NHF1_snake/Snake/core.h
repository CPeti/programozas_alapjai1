#ifndef SNAKEMOVEMENTS_H_INCLUDED
#define SNAKEMOVEMENTS_H_INCLUDED
#include <stdbool.h>
#include <SDL.h>

extern int n;
extern int wy;

typedef struct coord{int x; int y;} coord;
typedef struct body{coord pos; struct body *next;} body;
typedef struct snake{body* head; coord speed; int score; SDL_Color c;} snake;

typedef enum gamestate{startup, running, paused, finished, leaderboard} gamestate;
typedef enum winner{greenw, bluew, none} winner;
typedef enum gamemode{solo, duo} gamemode;

void reset(snake *sn);
void kill(snake *sn);
void move(snake *sn);
bool collision(snake sn1, snake sn2, winner *w, gamemode gm);
void init(snake *sn, SDL_Color c);
void check_food(snake *sn1, snake *sn2, coord *apple, gamemode gm);
void spawn(coord *apple, int n);


#endif // SNAKEMOVEMENTS_H_INCLUDED
