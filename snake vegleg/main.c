#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <time.h>
#include "oneplayer.h"
#include "twoplayer.h"
#include "snakeoperate.h"
#include "graphics.h"
#include "constants.h"
#include "mainmenu.h"
#include "highscores.h"
#include "debugmalloc.h"



///SDL inicializálása
void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL)
    {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}


///Ez lesz a program fõ ciklusa, innen lesz vezérelhetõ majd a menü
void loop ()
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(HEWI,HEWI, &window, &renderer);

    boxRGBA(renderer,0,0,HEWI,HEWI,0,0,0,255);
    SDL_RenderPresent(renderer);

    Menu state=MAIN;

    while(state!=QUIT)
    {
        switch(state)
        {
        case MAIN:
        {
            state = mainMenu(renderer);
            break;
        }
        case HIGHSCORES:
        {
            controlHS(renderer);
            state = MAIN;
            break;
        }
        case ONEP:
        {
            oneplayer(renderer);
            state = MAIN;
            break;
        }
        case TWOP:
        {
            twoplayer(renderer);
            state = MAIN;
            break;
        }
        default:
            state=MAIN;
            break;
        }
    }

    SDL_Quit();

    return;
}


int main(int argc, char *argv[])
{
    srand(time(NULL));

    loop();


    return 0;
}

