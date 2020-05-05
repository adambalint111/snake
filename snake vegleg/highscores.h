#ifndef HIGHSCORES_H_INCLUDED
#define HIGHSCORES_H_INCLUDED


#include "graphics.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct Result
{
    char name[101];
    int score;
} Result;

//Result highs[TOP];

void addScore(int scr, SDL_Renderer* renderer);

void controlHS(SDL_Renderer* renderer);

#endif // HIGHSCORES_H_INCLUDED
