#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "debugmalloc.h"
#include "core.h"


void spawn(coord *apple, int n){
    apple->x = rand()%n;
    apple->y = rand()%n;
}
static bool coord_check(coord a, coord b){
    return ((a.x == b.x) && (a.y == b.y));
}
static void set(coord *cd, int x, int y){
    cd->x = x;
    cd->y = y;
}
static void grow(snake sn, int n){
    body *moving = sn.head;
    while(moving->next){
        moving = moving->next;
    }
    for(int i = 0; i < n; i++){
        body *grown;
        grown = (body*)malloc(sizeof(body));
        set(&grown->pos, moving->pos.x, moving->pos.y);
        moving->next = grown;
        grown->next = NULL;
        moving = moving->next;
    }
}
static bool check_wall_and_self(snake sn){
    if (sn.head->pos.x < 0 || sn.head->pos.x > n-1 || sn.head->pos.y < 0 || sn.head->pos.y > n-1){
        return true;
    }
    body* moving = sn.head->next;
    while (moving && moving->next){
        if (coord_check(sn.head->pos, moving->pos)){
            return true;
        }
        moving = moving->next;
    }
    return false;
}
void kill(snake *sn){
    body *temp;
    while(sn->head){
        temp = sn->head;
        sn->head = temp->next;
        free(temp);
    }
    free(sn->head);
}
void init(snake *sn, SDL_Color c){
    sn->head = (body*)malloc(sizeof(body));
    set(&sn->head->pos, rand()%n, rand()%n);
    sn->head->next = NULL;
    set(&sn->speed, 0, 0);
    sn->score = 0;
    sn->c = c;
}
void reset(snake *sn){
    kill(sn);
    init(sn, sn->c);
}
void move(snake *sn){
    body* nw;
    nw = (body*)malloc(sizeof(body));
    set(&nw->pos, sn->head->pos.x + sn->speed.x, sn->head->pos.y + sn->speed.y);
    nw->next = sn->head;
    sn->head = nw;

    body *moving = sn->head;
    while(moving->next->next){
        moving = moving->next;
    }
    free(moving->next);
    moving->next = NULL;
}
bool collision(snake sn1, snake sn2, winner *w, gamemode gm){
    if (check_wall_and_self(sn1)){
        if (gm == solo) *w = none;
        else *w = bluew;
        return true;
    }
    if (gm == duo){
        if (coord_check(sn1.head->pos, sn2.head->pos)){
            *w = none;
            return true;
        }
        if (check_wall_and_self(sn2)){
            *w = greenw;
            return true;
        }
        body *moving = sn1.head;
        while (moving && moving->next){
            if (coord_check(sn2.head->pos, moving->pos)){
                *w = greenw;
                return true;
            }
            moving = moving->next;
        }
        moving = sn2.head;
        while (moving && moving->next){
            if (coord_check(sn1.head->pos, moving->pos)){
                *w = bluew;
                return true;
            }
            moving = moving->next;
        }
    }
    return false;
}
void check_food(snake *sn1, snake *sn2, coord *apple, gamemode gm){
    int growth = 5;
    if (coord_check(*apple, sn1->head->pos)){
        sn1->score += growth;
        grow(*sn1, growth);
        spawn(apple, n);
    }
    if (gm == duo && coord_check(*apple, sn2->head->pos)){
        sn2->score += growth;
        grow(*sn2, growth);
        spawn(apple, n);
    }
}

