#include "snakeoperate.h"
#include "constants.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "debugmalloc.h"

///Mozgatja a k�gy�t
Bodypart* moveSnake(Bodypart* sn, Dir dir)
{
    if(dir==NONE)
        return sn;
    Bodypart* curr=sn;
    Bodypart* newHead;
    while(curr->next->next!=NULL)
        curr=curr->next;

    curr->next->p.x=sn->p.x+(dir/2)*GRID;
    curr->next->p.y=sn->p.y+(dir%2)*GRID;

    curr->next->next=sn;
    newHead=curr->next;
    curr->next=NULL;
    return newHead;
}

///�tk�zik-e az alm�val?
bool collAppleSnake(Apple app, Bodypart* sn)
{
    if(sn==NULL)
        return false;
    if((sn->p.x)-(app.p.x-GRID/2)==0 && (sn->p.y)-(app.p.y-GRID/2)==0)
    {
        return true;
    }
    return false;
}

///Megn�veli a k�gy�t
Bodypart* incrSnake(Bodypart* sn, int player)
{
    Bodypart* newBp;
    newBp = (Bodypart*) malloc(sizeof(Bodypart));
    newBp->next=NULL;
    if(sn==NULL)
    {
        if(player==1)
        {
            newBp->p.x=HEWI-5*GRID;
            newBp->p.y=HEWI-5*GRID;
            return newBp;
        }
        else
        {
            newBp->p.x=5*GRID;
            newBp->p.y=5*GRID;
            return newBp;
        }
    }
    else if(sn->next==NULL)
    {
        if(player==1)
        {
            newBp->p.x=sn->p.x+GRID;
            newBp->p.y=sn->p.y;
            sn->next=newBp;
            return sn;
        }
        else
        {
            newBp->p.x=sn->p.x-GRID;
            newBp->p.y=sn->p.y;
            sn->next=newBp;
            return sn;
        }
    }
    else
    {
        Bodypart* curr=sn;
        while(curr->next->next!=NULL)
            curr=curr->next;
        curr->next->next=newBp;
        if(curr->p.x==curr->next->p.x)
        {
            newBp->p.x=curr->next->p.x;
            if(curr->p.y<=(curr->next->p.y))
                newBp->p.y=(curr->next->p.y)+GRID;
            else
                newBp->p.y=(curr->next->p.y)-GRID;
        }
        else
        {
            newBp->p.y=curr->next->p.y;
            if(curr->p.x<=(curr->next->p.x))
                newBp->p.x=(curr->next->p.x)+GRID;
            else
                newBp->p.x=(curr->next->p.x)-GRID;
        }
        return sn;
    }
}

///L�trehozza az alm�t
Apple spawnApple(Bodypart* snA, Bodypart* snB)
{
    Apple app;
    app.r=GRID/2;
    bool onSnakeA= true;
    bool onSnakeB= true;
    while(onSnakeA || onSnakeB)
    {
        app.p.x=GRID*(rand()%(HEWI/GRID))+GRID/2;
        app.p.y=GRID*(rand()%(HEWI/GRID))+GRID/2;
        Bodypart* currA=snA;
        Bodypart* currB=snB;
        while((currA!=NULL || currB!=NULL) && (onSnakeA || onSnakeB))
        {
            if(currA!=NULL)
            {
                onSnakeA=collAppleSnake(app, currA);
                currA=currA->next;
            }
            else
                onSnakeA=false;
            if(currB!=NULL)
            {
                onSnakeB=collAppleSnake(app, currB);
                currB=currB->next;
            }
            else
                onSnakeB=false;
        }
    }
    return app;
}

///Megeszi az alm�t
Apple eatApple(Bodypart* snA, Bodypart* snB, int player)
{
    if(player==1)
        incrSnake(snA,1);
    else
        incrSnake(snB,2);
    Apple app=spawnApple(snA,snB);
    return app;
}

///�tk�zik-e mag�val/k�gy�val?
bool collSelforSnake(Bodypart* snA, Bodypart* snB)
{
    Bodypart* curr=snA;
    if(snA==snB)
        curr=snA->next;
    while(curr!=NULL)
    {
        if((curr->p.x)==(snB->p.x) && (curr->p.y)==(snB->p.y))
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
    if((sn->p.x)<0 || (sn->p.x)>=HEWI || (sn->p.y)<0 || (sn->p.y)>=HEWI)
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
Bodypart* startGame(Bodypart* sn, int player)
{
    if(sn!=NULL)
        freeSnake(sn);
    sn=incrSnake(sn,player);
    sn=incrSnake(sn,player);
    return sn;
}

