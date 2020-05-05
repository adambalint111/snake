#include "highscores.h"
#include "constants.h"
#include "graphics.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "debugmalloc.h"

Result highs[TOP];

void writeHS()
{
    FILE* fp;
    fp=fopen(MYFILE,"w");
    for(int i=0; i<TOP; i++)
    {
        fprintf(fp,"%s: %d\n",highs[i].name,highs[i].score);
    }
    fclose(fp);
}

void clearHS()
{
    for(int i=0; i<TOP; i++)
    {
        strcpy(highs[i].name, "---");
        highs[i].score=0;
    }
    writeHS();
}

void sortHS()
{
    for(int i=0; i<TOP; i++)
        for(int j=i; j<TOP; j++)
        {
            if(highs[i].score<highs[j].score)
            {
                Result temp=highs[i];
                highs[i]=highs[j];
                highs[j]=temp;
            }
        }
}

void readHS()
{
    FILE* fp;
    fp=fopen(MYFILE,"r");

    int i=0;
    while(fscanf(fp,"%[^:]: %d", highs[i].name, &highs[i].score)==2)
    {
        fgetc(fp);
        i++;
    }
    for(int j=i; j<TOP; j++)
    {
        strcpy(highs[j].name, "---");
        highs[j].score=0;
    }
    fclose(fp);
    sortHS();
}

void addScore(int scr, SDL_Renderer* renderer)
{
    for(int i=0; i<TOP; i++)
    {
        if(scr>=highs[i].score)
        {
            readHS("highscores.txt");
            bool full=true;
            int minInd;
            for(int j=i; j<TOP; j++)
                if(strcmp(highs[j].name,"---") == 0)
                {
                    minInd=j;
                    full=false;
                    break;
                }
            if(full)
                minInd=TOP-1;

            input_text(highs[minInd].name, renderer);

            // scanf("%s", highs[minInd].name);
            highs[minInd].score=scr;
            sortHS();
            writeHS();
            return;
        }
    }
    return;
}

void presentHS(SDL_Renderer* renderer)
{
    readHS();
    TTF_Init();
    TTF_Font *title = TTF_OpenFont("courier-new.ttf", 64);
    TTF_Font *sub = TTF_OpenFont("courier-new.ttf", 25);
    TTF_Font *cl = TTF_OpenFont("courier-new.ttf", 40);

    SDL_Color yellow= {241, 247, 146};
    SDL_Color white= {255,255,255};


    char text[108];
    boxRGBA(renderer,0,0,HEWI,HEWI,0,0,0,255);
    strcpy(text,"HIGHSCORES");
    SDL_Rect place= {100,100,0,0};
    write(renderer,title,text,yellow,place);
    place.y+= 100;

    for(int i=0; i<TOP; i++)
    {
        sprintf(text,"%2d",i+1);
        strcat(text,". ");
        strcat(text,highs[i].name);
        strcat(text," -> ");
        char printScore[4];
        sprintf(printScore,"%d",highs[i].score);
        strcat(text,printScore);
        place.y+=30;

        write(renderer,sub,text,white,place);

    }
    place.y=700;
    strcpy(text, "Press C to clear the table");
    write(renderer,cl,text,white, place);

    SDL_RenderPresent(renderer);
}

void controlHS(SDL_Renderer* renderer)
{
    presentHS(renderer);

    SDL_Event hsEv;

    while(true)
    {
        SDL_WaitEvent(&hsEv);
        switch(hsEv.type)
        {
        case SDL_KEYDOWN:
            switch(hsEv.key.keysym.sym)
            {
            case SDLK_c:
                clearHS();
                presentHS(renderer);
                break;
            case SDLK_ESCAPE:
                return;
            default:
                break;
            }
        default:
            break;
        }
    }
}

