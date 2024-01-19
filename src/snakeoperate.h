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

///Az alma strukt�r�ja
typedef struct Apple
{
    Point p;
    int r;
} Apple;

///A k�gy� egy testr�sz�nek strukt�r�ja
typedef struct Bodypart
{
    Point p;
    struct Bodypart* next;
} Bodypart;

///Enumer�ci� az ir�nyokra
typedef enum Dir
{
    LEFT=-2,
    UP=-1,
    RIGHT=2,
    DOWN=1,
    NONE=0,
} Dir;


///Mozgatja a k�gy�t
Bodypart* moveSnake(Bodypart* sn, Dir dir);

///�tk�zik-e az alm�val?
bool collAppleSnake(Apple app, Bodypart* sn);

///Megn�veli a k�gy�t
Bodypart* incrSnake(Bodypart* sn, int player);

///L�trehozza az alm�t
Apple spawnApple(Bodypart* snA, Bodypart* snB);

///Megeszi az alm�t
Apple eatApple(Bodypart* snA, Bodypart* snB, int player);

///�tk�zik-e mag�val/k�gy�val?
bool collSelforSnake(Bodypart* snA, Bodypart* snB);

///�tk�zik-e a fallal?
bool collSnakeWall(Bodypart* sn);

///Felszabad�tja a k�gy� �ltal foglalt mem�ri�t
void freeSnake(Bodypart* sn);

///Elind�tja a j�t�kot
Bodypart* startGame(Bodypart* sn, int player);


#endif // SNAKEOPERATE_H_INCLUDED
