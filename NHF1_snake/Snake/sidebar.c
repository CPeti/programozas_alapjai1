#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "sidebar.h"
#include "debugmalloc.h"

static void draw_button(button *bt, TTF_Font *font){
    boxRGBA(renderer, bt->x1-5, bt->y1-5, bt->x1+bt->width+5, bt->y1+bt->height+5, 0, 0, 0, 255);
    if(bt->clicked) {boxRGBA(renderer, bt->x1, bt->y1, bt->x1+bt->width, bt->y1+bt->height, 50, 50, 50, 255);}
    else boxRGBA(renderer, bt->x1, bt->y1, bt->x1+bt->width, bt->y1+bt->height, 100, 100, 100, 255);
    SDL_Surface *felirat;
    SDL_Texture *felirat_t;
    int l = strlen(bt->text);
    SDL_Rect hova = { bt->x1+bt->width/2-l*9, bt->y1, l*18, 50 };
    SDL_Color feher = {255, 255, 255};
    felirat = TTF_RenderUTF8_Blended(font, bt->text, feher);
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
}
bool button_check(button *bt, int mousex, int mousey, bool click){
    if (click && mousex > bt->x1 && mousex < bt->x1 + bt->width && mousey > bt->y1 && mousey < bt->y1+bt->height){
        bt->clicked = true;
        return true;
    }
    bt->clicked = false;
    return false;
}
static button* create_button(int x1, int y1, int width, int height, char text[], bool clicked){
    button *bt = (button*) malloc(sizeof(button));
    bt->x1 = x1;
    bt->y1 = y1;
    bt->width = width;
    bt->height = height;
    for(int i = 0; i < 20; i++)
        bt->text[i] = text[i];
    bt->clicked = false;
    return bt;
}
button** build_menu(){
    button **menu = (button**)malloc(10 * sizeof(button*));
    menu[0] = create_button(825, 25, 100, 50, "start", false);
    menu[1] = create_button(950, 25, 100, 50, "stop", false);
    menu[2] = create_button(1075, 25, 100, 50, "reset", false);
    menu[3] = create_button(825, 100, 350, 50, "leaderboard", false);
    menu[4] = create_button(825, 175, 100, 50, "slow", false);
    menu[5] = create_button(945, 175, 110, 50, "normal", false);
    menu[6] = create_button(1075, 175, 100, 50, "fast", false);
    menu[7] = create_button(825, 250, 165, 50, "solo", false);
    menu[8] = create_button(1010, 250, 165, 50, "duo", false);
    menu[9] = create_button(825, 325, 350, 50, "change name", false);

    return menu;
}
void draw_menu(button **menu, TTF_Font *font, int mousex, int mousey, bool click){
    boxRGBA(renderer, wy, 0, wx, wy, 170, 170, 170, 255);
    for(int i = 0; i < 10; i++) {button_check((menu[i]), mousex, mousey, click); draw_button(menu[i], font);}
}
highscore** read_leaderboard(char filename[]){
    FILE *fp;
    fp = fopen(filename, "r");
    highscore **leaderboard = (highscore**)malloc(10 * sizeof(highscore*));
    for(int i = 0; i < 10; i++){
        highscore *element = (highscore*)malloc(sizeof(highscore));
        if(fscanf(fp, "%s %d", element->name, &element->score) < 0){
            strcpy(element->name, "placeholder");
            element->score = 0;
        }
        leaderboard[i] = element;
    }
    fclose(fp);
    return leaderboard;
}
void write_leaderboard(char filename[], highscore **ldr){
    FILE *fp;
    fp = fopen(filename, "w");
    for(int i = 0; i < 10 && ldr[i]->score != 0; i++){
        fprintf(fp, "%s %d\n", ldr[i]->name, ldr[i]->score);
    }
    fclose(fp);
}
void draw_leaderboard(highscore **ldr, TTF_Font *font){
    boxRGBA(renderer, 0, 0, wy-1, wy-1, 0, 0, 0, 255);
    for(int i = 0; i < 10 && ldr[i]->score != 0; i++){
        SDL_Surface *felirat;
        SDL_Texture *felirat_t;
        SDL_Color color = {255, 255, 255};
        char sscore[30];
        char temp[30];
        sprintf(sscore, "%d. ", i+1);
        strcat(sscore, ldr[i]->name);
        sprintf(temp, " %d", ldr[i]->score);
        strcat(sscore, temp);
        SDL_Rect hova = { 150, 50+i*50, strlen(sscore)*40, 50};
        felirat = TTF_RenderUTF8_Blended(font, sscore, color);
        felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
        SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
        SDL_FreeSurface(felirat);
        SDL_DestroyTexture(felirat_t);
    }
}
bool update_leaderboard(char filename[], highscore **ldr, snake sn, char name[20]){
    if(sn.score <= ldr[9]->score) return false;
    highscore *element = (highscore*)malloc(sizeof(highscore));
    strcpy(element->name, name);
    element->score = sn.score;
    highscore *temp;
    for (int i = 9; i >= 0 && sn.score > ldr[i]->score; i--){
        temp = ldr[i];
        ldr[i] = element;
        if (i == 9) free(temp);
        else ldr[i+1] = temp;
    }
    write_leaderboard(filename, ldr);
    return true;
}
bool input_text(char *dest, size_t hossz, TTF_Font *font) {
    SDL_Rect teglalap = {825, 400, 350, 50};
    SDL_Color szoveg = {0, 0, 0};
    SDL_Color hatter = {255, 255, 255};
    /* Ez tartalmazza az aktualis szerkesztest */
    char composition[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
    composition[0] = '\0';
    /* Ezt a kirajzolas kozben hasznaljuk */
    char textandcomposition[hossz + SDL_TEXTEDITINGEVENT_TEXT_SIZE + 1];
    /* Max hasznalhato szelesseg */
    int maxw = teglalap.w - 2;
    int maxh = teglalap.h - 2;

    dest[0] = '\0';

    bool enter = false;
    bool kilep = false;

    SDL_StartTextInput();
    while (!kilep && !enter) {
        /* doboz kirajzolasa */
        boxRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, hatter.r, hatter.g, hatter.b, 255);
        rectangleRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, szoveg.r, szoveg.g, szoveg.b, 255);
        /* szoveg kirajzolasa */
        int w;
        strcpy(textandcomposition, dest);
        strcat(textandcomposition, composition);
        if (textandcomposition[0] != '\0') {
            SDL_Surface *felirat = TTF_RenderUTF8_Blended(font, textandcomposition, szoveg);
            SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
            SDL_Rect cel = { teglalap.x, teglalap.y, felirat->w < maxw ? felirat->w : maxw, felirat->h < maxh ? felirat->h : maxh };
            SDL_RenderCopy(renderer, felirat_t, NULL, &cel);
            SDL_FreeSurface(felirat);
            SDL_DestroyTexture(felirat_t);
            w = cel.w;
        } else {
            w = 0;
        }
        /* kurzor kirajzolasa */
        if (w < maxw) {
            vlineRGBA(renderer, teglalap.x + w + 2, teglalap.y + 2, teglalap.y + teglalap.h - 3, szoveg.r, szoveg.g, szoveg.b, 192);
        }
        /* megjeleniti a képernyon az eddig rajzoltakat */
        SDL_RenderPresent(renderer);

        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
            /* Kulonleges karakter */
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    int textlen = strlen(dest);
                    do {
                        if (textlen == 0) {
                            break;
                        }
                        if ((dest[textlen-1] & 0x80) == 0x00)   {
                            /* Egy bajt */
                            dest[textlen-1] = 0x00;
                            break;
                        }
                        if ((dest[textlen-1] & 0xC0) == 0x80) {
                            /* Bajt, egy tobb-bajtos szekvenciabol */
                            dest[textlen-1] = 0x00;
                            textlen--;
                        }
                        if ((dest[textlen-1] & 0xC0) == 0xC0) {
                            /* Egy tobb-bajtos szekvencia elso bajtja */
                            dest[textlen-1] = 0x00;
                            break;
                        }
                    } while(true);
                }
                if (event.key.keysym.sym == SDLK_RETURN) {
                    enter = true;
                }
                break;

            /* A feldolgozott szoveg bemenete */
            case SDL_TEXTINPUT:
                if (strlen(dest) + strlen(event.text.text) < hossz) {
                    strcat(dest, event.text.text);
                }

                /* Az eddigi szerkesztes torolheto */
                composition[0] = '\0';
                break;

            /* Szoveg szerkesztese */
            case SDL_TEXTEDITING:
                strcpy(composition, event.edit.text);
                break;

            case SDL_QUIT:
                /* visszatesszuk a sorba ezt az eventet, mert
                 * sok mindent nem tudunk vele kezdeni */
                SDL_PushEvent(&event);
                kilep = true;
                break;
        }
    }

    /* igaz jelzi a helyes beolvasast; = ha enter miatt allt meg a ciklus */
    SDL_StopTextInput();
    return enter;
}
void destroy_menu(button **menu){
    for(int i = 0; i < 10; i++){
        free(menu[i]);
    }
    free(menu);
}
void destroy_leaderboard(highscore **ldr){
    for(int i = 0; i < 10; i++){
        free(ldr[i]);
    }
    free(ldr);
}
