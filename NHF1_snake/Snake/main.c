#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "core.h"
#include "draw_game.h"
#include "sidebar.h"
#include "debugmalloc.h"

int n = 25;     //palya merete
int wx = 1200;  //ablak meretei
int wy = 800;

SDL_Renderer *renderer;

int main(int argc, char *argv[]) {
    srand(time(NULL));
    SDL_Window *window;
    sdl_init(wx, wy, &window, &renderer);

    /* kpek es betutipus betoltese */
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("assets/BASKVILL.ttf", 52);
    SDL_Texture *titlescreen = IMG_LoadTexture(renderer, "assets/mainscreen.png");
    SDL_Texture *deathscreen = IMG_LoadTexture(renderer, "assets/deathscreen.png");
    SDL_Texture *greenWin = IMG_LoadTexture(renderer, "assets/greenwin.png");
    SDL_Texture *blueWin = IMG_LoadTexture(renderer, "assets/bluewin.png");
    SDL_Texture *apple_img = IMG_LoadTexture(renderer, "assets/apple.png");

    /* dicsoseglista beolvasasa filebol strukturak tombjebe */
    char filename[] = "assets/leaderboard.txt";
    highscore** ldr = read_leaderboard(filename);

    char name[40] = "anonymus";

    /* az oldalsav gombjainak osszegyujtese egy tombbe */
    button** menu = build_menu();

    /* idozito hozzaadasa: 20 ms; 1000 ms / 20 ms -> 50 fps, <3 infoc */
    SDL_TimerID id = SDL_AddTimer(20, idozit, NULL);
    SDL_Color grn = {0, 255, 0};
    SDL_Color bl = {0, 0, 255};
    /* a ket kigyo deklaralasa es inicializalasa */
    snake green;
    snake blue;
    init(&green, grn);
    init(&blue, bl);

    /* alma deklaralasa, majd poziciojanak beallitasa random ertekekre */
    coord apple;
    spawn(&apple, n);

    /* allapotvaltozok inicializalasa */
    bool quit = false;              //ha az erteke igaz, a jatek befejezodik
    bool click = false;             //a bal egergomb "lenyomottsaganak" logikai erteke
    int tick = 0;                   //a loopokat szamlalo valtozo
    int speed = 6;                  //ennyi looponkent fog frissulni a jatekallas, ez teszi szakaszossa a kigyok mozgasat.
    bool cdgreen = false;           //cooldown a kigyok iranyitasan, ha igaz, a kigyo nem valthat iranyt. A kígyók mozgása után áll vissza hamisra
    bool cdblue = false;
    gamestate state = startup;
    winner w = none;
    gamemode gm = solo;

    /* kurzor helyenek x es y koordinatai */
    int mousex = 0;
    int mousey = 0;


    while(!quit){
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type){
            case SDL_MOUSEBUTTONDOWN:
                /* kurzor koordinatainak beallitasa*/
                mousex = event.button.x;
                mousey = event.button.y;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    click = true;
                    /* gombok lenyomasanak ellenorzese */
                    if (button_check(menu[0], mousex, mousey, click)){          //start gomb, elionditja a jatekot
                        state = running;
                    }else if (button_check(menu[1], mousex, mousey, click)){    //stop gomb, megallitja a jatekot
                        state = paused;
                    }else if (button_check(menu[2], mousex, mousey, click)){    //reset gomb, visszaallitja a jatekot a kezdoallapotba
                        reset(&green);
                        reset(&blue);
                        state = running;
                    }else if (button_check(menu[3], mousex, mousey, click)){    //leaderboard gomb, a dicsoseglistat jeleniti meg. Ha mar nyitva van, bezarja
                        if(state != leaderboard) state = leaderboard;
                        else state = running;
                    }else if (button_check(menu[4], mousex, mousey, click)){    //fast gomb, a legyorsabbra allitja a sebesseget
                        speed = 12;
                    }else if (button_check(menu[5], mousex, mousey, click)){    //normal gomb, a kozepesre allitja a sebesseget
                        speed = 6;
                    }else if (button_check(menu[6], mousex, mousey, click)){    //slow gomb, lassura allitja a sebesseget
                        speed = 3;
                    }else if (button_check(menu[7], mousex, mousey, click)){    //solo gomb, a jatekmodot egyjatekosra allitja
                        if(gm == duo) gm = solo;
                        state = running;
                    }else if (button_check(menu[8], mousex, mousey, click)){    //duo gomb, a jatekmodot ketjatekosra allitja
                        if(gm == solo) gm = duo;
                        state = running;
                    }else if (button_check(menu[9], mousex, mousey, click)){    //change name gomb, megjelenit egy szovegdobozt a nev megvaltoztatasara
                        input_text(name, 40, font);
                    }
                } break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    click = false;
                } break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    /* a zöld kígyó irányítása a WASD billentyűkkel */
                    case SDLK_w:    if (!cdgreen && state == running && green.speed.y == 0) {green.speed.x = 0; green.speed.y = -1; cdgreen = true;} break;
                    case SDLK_d:    if (!cdgreen && state == running && green.speed.x == 0) {green.speed.x = 1; green.speed.y = 0; cdgreen = true;} break;
                    case SDLK_s:    if (!cdgreen && state == running && green.speed.y == 0) {green.speed.x = 0; green.speed.y = 1; cdgreen = true;} break;
                    case SDLK_a:    if (!cdgreen && state == running && green.speed.x == 0) {green.speed.x = -1; green.speed.y = 0; cdgreen = true;} break;

                    /* a kek kígyó irányítása a nyil billentyűkkel, ha a jatekmod ketjatekos*/
                    case SDLK_UP:    if (!cdblue && gm == duo && state == running && blue.speed.y == 0) {blue.speed.x = 0; blue.speed.y = -1; cdblue = true;} break;
                    case SDLK_RIGHT:    if (!cdblue && gm == duo && state == running && blue.speed.x == 0) {blue.speed.x = 1; blue.speed.y = 0; cdblue = true;} break;
                    case SDLK_DOWN:    if (!cdblue && gm == duo && state == running && blue.speed.y == 0) {blue.speed.x = 0; blue.speed.y = 1; cdblue = true;} break;
                    case SDLK_LEFT:    if (!cdblue && gm == duo && state == running && blue.speed.x == 0) {blue.speed.x = -1; blue.speed.y = 0; cdblue = true;} break;

                    /* reset az R billentyuvel */
                    case SDLK_r:    reset(&green); reset(&blue); state = running; break;
                    /* jatek inditasa es megallitasa a SPACE billentyuvel */
                    case SDLK_SPACE:    if(state == running) state = paused; else state = running; break;
                }
                break;


            case SDL_USEREVENT:
                if (state == running){
                    /* ha valamelyik kigyo feje egy mezon van az almaval, a merete eggyel no*/
                    check_food(&green, &blue, &apple, gm);

                    if (tick % speed == speed-1){
                        move(&green);
                        /* cooldown visszaallitasa */
                        cdgreen = false;
                        if (gm == duo) {move(&blue); cdblue = false;}
                        /* utkozesek ellenorzese, ha igen, jatek vege */
                        if (collision(green, blue, &w, gm)){
                            state = finished;
                            if (gm == solo) update_leaderboard(filename, ldr, green, name);
                            if (gm == duo) reset(&blue);
                            reset(&green);
                        }
                    }
                    /* jatekelemek kirajzolasa */
                    draw_game(green, blue, apple, font, gm, apple_img);
                } else if (state == startup){
                    /* kezdokepernyo */
                    draw_screen(titlescreen);
                } else if (state == finished){
                    /* jatek vege kepernyok */
                    if (w == none) draw_screen(deathscreen); //you died!
                    if (w == greenw) draw_screen(greenWin);  //green won
                    if (w == bluew) draw_screen(blueWin);    //blue won
                } else if (state == leaderboard) {
                    /* dicsoseglista kirajzolasa */
                    draw_leaderboard(ldr, font);
                }
                /* menu kirajzolasa */
                draw_menu(menu, font, mousex, mousey, click);

                /* megjelenites */
                SDL_RenderPresent(renderer);
                tick += 1;
                tick %= 60;
                break;

            case SDL_QUIT:
                quit = true;
                break;
        }
    }

    SDL_DestroyTexture(titlescreen);
    SDL_DestroyTexture(deathscreen);
    SDL_DestroyTexture(greenWin);
    SDL_DestroyTexture(blueWin);
    SDL_DestroyTexture(apple_img);
    SDL_RemoveTimer(id);
    TTF_CloseFont(font);
    destroy_menu(menu);
    destroy_leaderboard(ldr);
    kill(&green);
    kill(&blue);
    SDL_Quit();
    return 0;
}


