#include "highscores.h"
#include "graphics.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

Result highs[10];

void clearHS()
{
    for(int i=0; i<10; i++)
    {
        strcpy(highs[i].name, "---");
        highs[i].score=0;
    }
}

void sortHS()
{
    for(int i=0; i<10; i++)
        for(int j=i; j<10; j++)
        {
            if(highs[i].score<highs[j].score)
            {
                Result temp=highs[i];
                highs[i]=highs[j];
                highs[j]=temp;
            }
        }
}

void readHS(char* fn)
{
    FILE* fp;
    fp=fopen(fn,"r");

    int i=0;
    while(fscanf(fp,"%[^\t]\t%d", highs[i].name, &highs[i].score)==2)
    {
        fgetc(fp);
        i++;
    }
    for(int j=i; j<10; j++)
    {
        strcpy(highs[j].name, "---");
        highs[j].score=0;
    }
    fclose(fp);
}

void addScore(int scr)
{
    for(int i=0; i<10; i++)
    {
        if(scr>=highs[i].score)
        {
            readHS("highscores.txt");
            FILE* fp;
            fp=fopen("highscores.txt","w");
            int min=highs[i].score;
            int minInd=i;
            for(int j=i;j<10;j++)
                if(highs[j].score<=min)
                {
                    minInd=j;
                    min=highs[j].score;
                }
            scanf("%s", highs[minInd].name);
            highs[minInd].score=scr;
            sortHS();
            for(int j=0; j<10; j++)
            {
                fprintf(fp,"%s\t%d\n",highs[j].name,highs[j].score);
            }
            fclose(fp);
            return;
        }
    }
    return;
}


void presentHS(SDL_Renderer* renderer)
{
    readHS("highscores.txt");
    sortHS();
    TTF_Init();
    TTF_Font *title = TTF_OpenFont("arial.ttf", 64);
    TTF_Font *sub = TTF_OpenFont("arial.ttf", 18);

    SDL_Color yellow= {241, 247, 146};
    SDL_Color white= {255,255,255};


    char text[108];
    boxRGBA(renderer,0,0,HEWI,HEWI,0,0,0,255);
    strcpy(text,"HIGHSCORES");
    SDL_Rect place= {100,100,0,0};
    write(renderer,title,text,yellow,place);
    place.y+= 100;

    for(int i=0; i<10; i++)
    {
        sprintf(text,"%d",i+1);
        strcat(text,". ");
        strcat(text,highs[i].name);
        strcat(text," -> ");
        char printScore[4];
        sprintf(printScore,"%d",highs[i].score);
        strcat(text,printScore);
        place.y+=20;

        write(renderer,sub,text,white,place);

    }

    SDL_RenderPresent(renderer);


    SDL_Event hsEv;


    while(true)
    {
        SDL_WaitEvent(&hsEv);
        switch(hsEv.type)
        {
        case SDL_KEYDOWN:
            switch(hsEv.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return;
            }
        }
    }
}
