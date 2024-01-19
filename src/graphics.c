#include "graphics.h"
#include "snakeoperate.h"
#include "constants.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"


///Kirajzolja az almát
void drawApple(SDL_Renderer* renderer,Apple app)
{
    filledCircleRGBA(renderer, app.p.x, app.p.y, app.r, rand()%255,rand()%255,rand()%255,255);
}

///Kirajzolja a kígyót
void drawSnake(SDL_Renderer* renderer, Bodypart* sn, int player)
{
    SDL_Color color;
    color.r=0;
    if(player==1)
    {
        color.g=255;
        color.b=0;
    }
    else
    {
        color.g=255;
        color.b=255;
    }
    for(Bodypart* curr=sn; curr!=NULL; curr=curr->next)
    {
        boxRGBA(renderer,curr->p.x,curr->p.y,curr->p.x+GRID,curr->p.y+GRID,color.r,color.g,color.b,255);
    }
}

///Kiírja az aktuális eredményt
void drawScores(SDL_Renderer* renderer,int num1, int num2)
{
    char p1[9]="P1: ";
    char str1[5];
    sprintf(str1,"%d",num1);
    strcat(p1,str1);
    stringRGBA(renderer,750,10,p1,124,252,0,200);
    if(num2!=-1)
    {
        char p2[9]="P2: ";
        char str2[5];
        sprintf(str2,"%d",num2);
        strcat(p2,str2);
        stringRGBA(renderer,750,30,p2,0,255,255,255);
    }
}


///Ezzel a függvénnyel lehet írni
void write(SDL_Renderer* renderer, TTF_Font* font, char* string, SDL_Color colorr,SDL_Rect where)
{
    SDL_Surface *text;
    SDL_Texture *text_t;


    text=TTF_RenderUTF8_Blended(font,string, colorr);
    text_t= SDL_CreateTextureFromSurface(renderer, text);
    where.w=text->w;
    where.h=text->h;


    SDL_RenderCopy(renderer, text_t, NULL, &where);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(text_t);
}


///Szövegbekérés (infoC alapján)
bool input_text(char *dest, SDL_Renderer *renderer)
{
    SDL_Rect teglalap= {40, 80, 400, 40};
    SDL_Rect szovtegl= {40,50,400,40};
    SDL_Color szoveg= {0, 0, 0};
    SDL_Color hatter = {255, 255, 255};

    size_t hossz=101;

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("courier-new.ttf", 30);
    TTF_Font *seg = TTF_OpenFont("courier-new.ttf", 22);

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
    while (!kilep && !enter)
    {
        /* doboz kirajzolasa */
        boxRGBA(renderer, teglalap.x, teglalap.y-30, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, hatter.r, hatter.g, hatter.b, 255);

        write(renderer,seg,"Put your name here:",szoveg,szovtegl);
        rectangleRGBA(renderer, teglalap.x, teglalap.y-5, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, szoveg.r, szoveg.g, szoveg.b, 255);
        /* szoveg kirajzolasa */
        int w;
        strcpy(textandcomposition, dest);
        strcat(textandcomposition, composition);
        if (textandcomposition[0] != '\0')
        {
            SDL_Surface *felirat = TTF_RenderUTF8_Blended(font, textandcomposition, szoveg);
            SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
            SDL_Rect cel = { teglalap.x, teglalap.y, felirat->w < maxw ? felirat->w : maxw, felirat->h < maxh ? felirat->h : maxh };
            SDL_RenderCopy(renderer, felirat_t, NULL, &cel);
            SDL_FreeSurface(felirat);
            SDL_DestroyTexture(felirat_t);
            w = cel.w;
        }
        else
        {
            w = 0;
        }
        /* kurzor kirajzolasa */
        if (w < maxw)
        {
            vlineRGBA(renderer, teglalap.x + w + 2, teglalap.y + 2, teglalap.y + teglalap.h - 3, szoveg.r, szoveg.g, szoveg.b, 192);
        }
        /* megjeleniti a képernyon az eddig rajzoltakat */
        SDL_RenderPresent(renderer);

        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        /* Kulonleges karakter */
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_BACKSPACE)
            {
                int textlen = strlen(dest);
                do
                {
                    if (textlen == 0)
                    {
                        break;
                    }
                    if ((dest[textlen-1] & 0x80) == 0x00)
                    {
                        /* Egy bajt */
                        dest[textlen-1] = 0x00;
                        break;
                    }
                    if ((dest[textlen-1] & 0xC0) == 0x80)
                    {
                        /* Bajt, egy tobb-bajtos szekvenciabol */
                        dest[textlen-1] = 0x00;
                        textlen--;
                    }
                    if ((dest[textlen-1] & 0xC0) == 0xC0)
                    {
                        /* Egy tobb-bajtos szekvencia elso bajtja */
                        dest[textlen-1] = 0x00;
                        break;
                    }
                }
                while(true);
            }
            if (event.key.keysym.sym == SDLK_RETURN)
            {
                enter = true;
            }
            break;

        /* A feldolgozott szoveg bemenete */
        case SDL_TEXTINPUT:
            if (strlen(dest) + strlen(event.text.text) < hossz)
            {
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

