#include "graphics.h"
#include "snakeoperate.h"
#include "constants.h"
#include "highscores.h"
#include "twoplayer.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "debugmalloc.h"



///A kígyó mozgásának idõzítõje
Uint32 idozit2(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

void twoplayer(SDL_Renderer* renderer)
{
    bool collA = false;
    bool collB = false;

    Bodypart* snakeA=NULL;
    Bodypart* snakeB=NULL;

    snakeA=startGame(snakeA,1);
    snakeB=startGame(snakeB,2);


    Dir tempDirA=NONE;
    Dir tempDirB=NONE;

    Dir directionA=NONE;
    Dir directionB=NONE;

    boxRGBA(renderer,0,0,HEWI,HEWI,255,0,0,255);

    SDL_TimerID timr = SDL_AddTimer(50, idozit2, NULL);

    Apple apple = spawnApple(snakeA,snakeB);

    int scoreA=0;
    int scoreB=0;


    while(!collA && !collB)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_USEREVENT:
        {
            directionA=tempDirA;
            directionB=tempDirB;

            if(collAppleSnake(apple, snakeA))
            {
                apple=eatApple(snakeA, snakeB, 1);
                scoreA++;
            }
            if(collAppleSnake(apple, snakeB))
            {
                apple=eatApple(snakeA, snakeB, 2);
                scoreB++;
            }

            boxRGBA(renderer, 0, 0, HEWI, HEWI, 0,0,0,255);

            drawScores(renderer,scoreA,scoreB);
            drawApple(renderer,apple);
            snakeA=moveSnake(snakeA,directionA);
            snakeB=moveSnake(snakeB,directionB);
            drawSnake(renderer,snakeA,1);
            drawSnake(renderer,snakeB,2);
            if(collSnakeWall(snakeA) || collSelforSnake(snakeA,snakeA) || collSelforSnake(snakeB,snakeA))
            {
                collA=true;
            }
            if(collSnakeWall(snakeB) || collSelforSnake(snakeB,snakeB) || collSelforSnake(snakeA,snakeB))
            {
                collB=true;
            }
            SDL_RenderPresent(renderer);
        }
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_LEFT:
                if(directionA!=RIGHT)
                    tempDirA=LEFT;
                break;
            case SDLK_UP:
                if(directionA!=DOWN)
                    tempDirA=UP;
                break;
            case SDLK_RIGHT:
                if(directionA!=LEFT)
                    tempDirA=RIGHT;
                break;
            case SDLK_DOWN:
                if(directionA!=UP)
                    tempDirA=DOWN;
                break;
            case SDLK_a:
                if(directionB!=RIGHT)
                    tempDirB=LEFT;
                break;
            case SDLK_w:
                if(directionB!=DOWN)
                    tempDirB=UP;
                break;
            case SDLK_d:
                if(directionB!=LEFT)
                    tempDirB=RIGHT;
                break;
            case SDLK_s:
                if(directionB!=UP)
                    tempDirB=DOWN;
                break;
            case SDLK_ESCAPE:
                SDL_RemoveTimer(timr);
                freeSnake(snakeA);
                freeSnake(snakeA);
                return;
            default:
                break;
            }
        default:
            continue;
        }
    }
    boxRGBA(renderer,0,0,HEWI,HEWI,0,0,0,255);
    TTF_Init();
    TTF_Font *resu = TTF_OpenFont("courier-new.ttf", 72);
    TTF_Font *getback = TTF_OpenFont("courier-new.ttf", 32);

    SDL_Color yellow= {241, 247, 146};
    char text[8];
    SDL_Rect place= {200,300,0,0};

    if(collA)
    {
        if(!collB)
        {
            strcpy(text,"P2 won!");
            write(renderer,resu,text,yellow,place);
        }
        else
        {
            if(scoreA>scoreB)
            {
                strcpy(text,"P1 won!");
                write(renderer,resu,text,yellow,place);
            }
            else if (scoreA<scoreB)
            {
                strcpy(text,"P2 won!");
                write(renderer,resu,text,yellow,place);
            }
            else
            {
                strcpy(text,"Draw!");
                write(renderer,resu,text,yellow,place);
            }
        }
    }
    else
    {
        strcpy(text,"P1 won!");
        write(renderer,resu,text,yellow,place);
    }
    strcpy(text,"ESC -> Main Menu");
    place.y+=200;
    write(renderer,getback,text,yellow,place);


    SDL_RenderPresent(renderer);

    SDL_Event hsEv;
    bool wait=true;
    while(wait)
    {
        SDL_WaitEvent(&hsEv);
        switch(hsEv.type)
        {
        case SDL_KEYDOWN:
            switch(hsEv.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                wait=false;
            default:
                break;
            }
        default:
            break;
        }
    }

    SDL_RemoveTimer(timr);

    freeSnake(snakeA);
    freeSnake(snakeB);

    return;

}

