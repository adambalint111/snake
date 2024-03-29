#include "oneplayer.h"
#include "graphics.h"
#include "snakeoperate.h"
#include "constants.h"
#include "highscores.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "debugmalloc.h"


///A k�gy� mozg�s�nak id�z�t�je
Uint32 idozit(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}


void oneplayer(SDL_Renderer* renderer)
{
    bool coll = false;
    Bodypart* snake=NULL;
    snake=startGame(snake,1);
    Dir tempDir=NONE;
    Dir direction=NONE;

    boxRGBA(renderer,0,0,HEWI,HEWI,255,0,0,255);

    SDL_TimerID tim = SDL_AddTimer(50, idozit, NULL);

    Apple apple = spawnApple(snake,NULL);

    int score=0;

    while(!coll)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_USEREVENT:
        {
            direction=tempDir;
            if(collAppleSnake(apple, snake))
            {
                apple=eatApple(snake,NULL,1);
                score++;
            }
            boxRGBA(renderer, 0, 0, HEWI, HEWI, 0,0,0,255);
            drawSnake(renderer,snake,1);
            snake=moveSnake(snake,direction);
            drawScores(renderer,score,-1);
            drawApple(renderer,apple);
            if(collSnakeWall(snake) || collSelforSnake(snake,snake))
            {
                coll=true;
            }
            SDL_RenderPresent(renderer);
        }
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_LEFT:
                if(direction!=RIGHT)
                    tempDir=LEFT;
                break;
            case SDLK_UP:
                if(direction!=DOWN)
                    tempDir=UP;
                break;
            case SDLK_RIGHT:
                if(direction!=LEFT)
                    tempDir=RIGHT;
                break;
            case SDLK_DOWN:
                if(direction!=UP)
                    tempDir=DOWN;
                break;
            case SDLK_ESCAPE:
                coll=true;
                break;
            default:
                break;
            }
        default:
            continue;
        }
    }
    addScore(score,renderer);
    SDL_RemoveTimer(tim);
    freeSnake(snake);
    return;

}

