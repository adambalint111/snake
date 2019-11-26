#include "graphics.h"
#include "snakeoperate.h"
#include "constants.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


///Kirajzolja az almát
void drawApple(SDL_Renderer* renderer,Apple app)
{
    filledCircleRGBA(renderer, app.x, app.y, app.r, 255,0,0,255);
}

///Kirajzolja a kígyót
void drawSnake(SDL_Renderer* renderer, Bodypart* sn)
{
    for(Bodypart* curr=sn; curr!=NULL; curr=curr->next)
    {
        boxRGBA(renderer,curr->x,curr->y,curr->x+GRID,curr->y+GRID,0,255,0,255);
    }
}

///Kiírja az aktuális eredményt
void drawScores(SDL_Renderer* renderer,int num1, int num2)
{
    char p1[9]="P1: ";
    char str1[5];
    sprintf(str1,"%d",num1);
    strcat(p1,str1);
    stringRGBA(renderer,750,10,p1,0,255,0,200);
    if(num2!=-1)
    {
        char p2[9]="P2: ";
        char str2[5];
        sprintf(str2,"%d",num2);
        strcat(p2,str2);
        stringRGBA(renderer,750,30,p2,120,120,255,200);
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
