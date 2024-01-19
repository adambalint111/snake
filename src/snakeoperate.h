#ifndef SNAKEOPERATE_H_INCLUDED
#define SNAKEOPERATE_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "constants.h"


typedef struct Point
{
    int x,y;
} Point;

///Az alma struktúrája
typedef struct Apple
{
    Point p;
    int r;
} Apple;

///A kígyó egy testrészének struktúrája
typedef struct Bodypart
{
    Point p;
    struct Bodypart* next;
} Bodypart;

///Enumeráció az irányokra
typedef enum Dir
{
    LEFT=-2,
    UP=-1,
    RIGHT=2,
    DOWN=1,
    NONE=0,
} Dir;


///Mozgatja a kígyót
Bodypart* moveSnake(Bodypart* sn, Dir dir);

///Ütközik-e az almával?
bool collAppleSnake(Apple app, Bodypart* sn);

///Megnöveli a kígyót
Bodypart* incrSnake(Bodypart* sn, int player);

///Létrehozza az almát
Apple spawnApple(Bodypart* snA, Bodypart* snB);

///Megeszi az almát
Apple eatApple(Bodypart* snA, Bodypart* snB, int player);

///Ütközik-e magával/kígyóval?
bool collSelforSnake(Bodypart* snA, Bodypart* snB);

///Ütközik-e a fallal?
bool collSnakeWall(Bodypart* sn);

///Felszabadítja a kígyó által foglalt memóriát
void freeSnake(Bodypart* sn);

///Elindítja a játékot
Bodypart* startGame(Bodypart* sn, int player);


#endif // SNAKEOPERATE_H_INCLUDED
