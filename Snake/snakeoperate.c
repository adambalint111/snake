#include "snakeoperate.h"
#include "constants.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


///Mozgatja a k�gy�t
Bodypart* moveSnake(Bodypart* sn, Dir dir)
{
    Bodypart* curr=sn;
    Bodypart* newHead;
    while(curr->next->next!=NULL)
        curr=curr->next;

    curr->next->x=sn->x+(dir/2)*GRID;
    curr->next->y=sn->y+(dir%2)*GRID;

    curr->next->next=sn;
    newHead=curr->next;
    curr->next=NULL;
    return newHead;
}

///�tk�zik-e az alm�val?
bool collAppleSnake(Apple app, Bodypart* sn)
{
    if((sn->x)-(app.x-GRID/2)==0 && (sn->y)-(app.y-GRID/2)==0)
    {
        return true;
    }
    return false;
}

///Megn�veli a k�gy�t
Bodypart* incrSnake(Bodypart* sn)
{
    Bodypart* newBp;
    newBp = (Bodypart*) malloc(sizeof(Bodypart));
    newBp->next=NULL;
    if(sn==NULL)
    {
        newBp->x=HEWI-5*GRID;
        newBp->y=HEWI-5*GRID;
        return newBp;
    }
    else if(sn->next==NULL)
    {
        newBp->x=sn->x+GRID;
        newBp->y=sn->y;
        sn->next=newBp;
        return sn;
    }
    else
    {
        Bodypart* curr=sn;
        while(curr->next->next!=NULL)
            curr=curr->next;
        curr->next->next=newBp;
        if(curr->x==curr->next->x)
        {
            newBp->x=curr->next->x;
            if(curr->y<=(curr->next->y))
                newBp->y=(curr->next->y)+GRID;
            else
                newBp->y=(curr->next->y)-GRID;
        }
        else
        {
            newBp->y=curr->next->y;
            if(curr->x<=(curr->next->x))
                newBp->x=(curr->next->x)+GRID;
            else
                newBp->x=(curr->next->x)-GRID;
        }
        return sn;
    }
}

///L�trehozza az alm�t
Apple spawnApple(Bodypart* sn)
{
    Apple app;
    app.r=GRID/2;
    bool onSnake= true;
    while(onSnake)
    {
        app.x=GRID*(rand()%(HEWI/GRID))+GRID/2;
        app.y=GRID*(rand()%(HEWI/GRID))+GRID/2;
        Bodypart* curr=sn;
        while(curr!=NULL && onSnake)
        {
            onSnake=collAppleSnake(app, curr);
            curr=curr->next;
        }
    }
    return app;
}

///Megeszi az alm�t
Apple eatApple(Bodypart* sn)
{
    incrSnake(sn);
    Apple app=spawnApple(sn);
    return app;
}

///�tk�zik-e mag�val?
bool collSelf(Bodypart* sn)
{
    Bodypart* curr=sn->next;
    while(curr!=NULL)
    {
        if((curr->x)==(sn->x) && (curr->y)==(sn->y))
        {
            return true;
        }
        curr=curr->next;
    }
    return false;
}

///�tk�zik-e a fallal?
bool collSnakeWall(Bodypart* sn)
{
    if((sn->x)<0 || (sn->x)>=HEWI || (sn->y)<0 || (sn->y)>=HEWI)
        return true;
    return false;
}

///Felszabad�tja a k�gy� �ltal foglalt mem�ri�t
void freeSnake(Bodypart* sn)
{
    Bodypart* curr=sn;
    while(curr!=NULL)
    {
        Bodypart* tmp=curr->next;
        free(curr);
        curr=tmp;
    }
}

///Elind�tja a j�t�kot
Bodypart* startGame(Bodypart* sn)
{
    if(sn!=NULL)
        freeSnake(sn);
    sn=incrSnake(sn);
    sn=incrSnake(sn);
    return sn;
}
