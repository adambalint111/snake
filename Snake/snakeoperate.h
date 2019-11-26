#ifndef SNAKEOPERATE_H_INCLUDED
#define SNAKEOPERATE_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "constants.h"


///Az alma struktúrája
typedef struct Apple
{
    int x,y,r;
} Apple;

///A kígyó egy testrészének struktúrája
typedef struct Bodypart
{
    int x,y;
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
Bodypart* incrSnake(Bodypart* sn);

///Létrehozza az almát
Apple spawnApple(Bodypart* sn);

///Megeszi az almát
Apple eatApple(Bodypart* sn);

///Ütközik-e magával?
bool collSelf(Bodypart* sn);

///Ütközik-e a fallal?
bool collSnakeWall(Bodypart* sn);

///Felszabadítja a kígyó által foglalt memóriát
void freeSnake(Bodypart* sn);

///Elindítja a játékot
Bodypart* startGame(Bodypart* sn);


#endif // SNAKEOPERATE_H_INCLUDED
