#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "snakeoperate.h"
#include "constants.h"



///Kirajzolja az alm�t
void drawApple(SDL_Renderer* renderer,Apple app);

///Kirajzolja a k�gy�t
void drawSnake(SDL_Renderer* renderer, Bodypart* sn, int player);

///Ezzel a f�ggv�nnyel lehet �rni
void write(SDL_Renderer* renderer, TTF_Font* font, char* string, SDL_Color color,SDL_Rect where);

///Ki�rja az aktu�lis eredm�nyt
void drawScores(SDL_Renderer* renderer,int num1, int num2);

///Sz�vegbek�r�s (infoC alapj�n)
bool input_text(char *dest, SDL_Renderer *renderer);

#endif // GRAPHICS_H_INCLUDED
