#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED


#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

///Egy negyzet oldalhossza a negyzetracson
#define GRID 20
///Az ablak szélessége és magassága
#define HEWI 800
///Hány elemű a dicsosegtabla?
#define TOP 10
///A celfajl neve
#define MYFILE "highscores.txt"

typedef enum Menu {QUIT, MAIN, HIGHSCORES, ONEP, TWOP} Menu;

#endif // CONSTANTS_H_INCLUDED
