#ifndef SNAKEOPERATE_H_INCLUDED
#define SNAKEOPERATE_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "constants.h"


///Az alma strukt�r�ja
typedef struct Apple
{
    int x,y,r;
} Apple;

///A k�gy� egy testr�sz�nek strukt�r�ja
typedef struct Bodypart
{
    int x,y;
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
Bodypart* incrSnake(Bodypart* sn);

///L�trehozza az alm�t
Apple spawnApple(Bodypart* sn);

///Megeszi az alm�t
Apple eatApple(Bodypart* sn);

///�tk�zik-e mag�val?
bool collSelf(Bodypart* sn);

///�tk�zik-e a fallal?
bool collSnakeWall(Bodypart* sn);

///Felszabad�tja a k�gy� �ltal foglalt mem�ri�t
void freeSnake(Bodypart* sn);

///Elind�tja a j�t�kot
Bodypart* startGame(Bodypart* sn);


#endif // SNAKEOPERATE_H_INCLUDED
