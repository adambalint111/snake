#include "mainmenu.h"
#include "graphics.h"
#include "constants.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <string.h>
#include "debugmalloc.h"


Menu mainMenu(SDL_Renderer *renderer)
{
    TTF_Init();
    TTF_Font *title = TTF_OpenFont("courier-new.ttf", 40);
    TTF_Font *sub = TTF_OpenFont("courier-new.ttf", 32);

    SDL_Color yellow= {241, 247, 146};
    SDL_Color white= {255,255,255};


    char text[101];
    boxRGBA(renderer,0,0,HEWI,HEWI,0,0,0,255);
    strcpy(text,"Snake");
    SDL_Rect place= {100,100,0,0};
    write(renderer,title,text,yellow,place);
    strcpy(text,"1 -> OnePlayer mode!");
    place.y=300;
    write(renderer,sub,text,white,place);
    strcpy(text,"2 -> TwoPlayer mode!");
    place.y=350;
    write(renderer,sub,text,white,place);
    strcpy(text,"H -> Highscores!");
    place.y=400;
    write(renderer,sub,text,white,place);
    strcpy(text,"ESC -> Quit!");
    place.y=450;
    write(renderer,sub,text,white,place);

    SDL_RenderPresent(renderer);

    SDL_Event mainEv;
    SDL_WaitEvent(&mainEv);

    switch(mainEv.type)
    {
    case SDL_KEYDOWN:
    {
        switch(mainEv.key.keysym.sym)
        {
        case SDLK_1:
            return ONEP;
        case SDLK_2:
            return TWOP;
        case SDLK_h:
            return HIGHSCORES;
        case SDLK_ESCAPE:
            return QUIT;
        default:
            return MAIN;
        }
    }
    /*case SDL_QUIT:
        return QUIT;*/
    default:
        return MAIN;
    }
}

