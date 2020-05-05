#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "snakeoperate.h"
#include "constants.h"



///Kirajzolja az almát
void drawApple(SDL_Renderer* renderer,Apple app);

///Kirajzolja a kígyót
void drawSnake(SDL_Renderer* renderer, Bodypart* sn, int player);

///Ezzel a függvénnyel lehet írni
void write(SDL_Renderer* renderer, TTF_Font* font, char* string, SDL_Color color,SDL_Rect where);

///Kiírja az aktuális eredményt
void drawScores(SDL_Renderer* renderer,int num1, int num2);

///Szövegbekérés (infoC alapján)
bool input_text(char *dest, SDL_Renderer *renderer);

#endif // GRAPHICS_H_INCLUDED
