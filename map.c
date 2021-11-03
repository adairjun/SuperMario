/*
Super Mario Bros

Menu

map.c

Antoine Drabble

Création: 07.01.13
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "game.h"
#include "char.h"
#include "event.h"
#include "map.h"

Sprites* LoadImages()
{
    Sprites* S;
    int i;

    S = malloc(NbSprites*sizeof(Sprites));

    S[0].sprite = IMG_Load("images/sky.png");
    S[1].sprite = IMG_Load("images/soil.png");
    S[2].sprite = IMG_Load("images/block.png");
    S[3].sprite = IMG_Load("images/box.png");
    S[4].sprite = IMG_Load("images/pipe1.png");
    S[5].sprite = IMG_Load("images/pipe2.png");
    S[6].sprite = IMG_Load("images/pipe3.png");
    S[7].sprite = IMG_Load("images/pipe4.png");
    S[8].sprite = IMG_Load("images/fin1.png");
    S[9].sprite = IMG_Load("images/fin2.png");
    S[10].sprite = IMG_Load("images/spades.png");

    for(i=0;i<NbSprites;i++){
    S[i].sprite = SDL_DisplayFormat(S[i].sprite);
    }

    S[0].getThrough = 0;
    S[1].getThrough = 1;
    S[2].getThrough = 1;
    S[3].getThrough = 1;
    S[4].getThrough = 1;
    S[5].getThrough = 1;
    S[6].getThrough = 1;
    S[7].getThrough = 1;
    S[8].getThrough = 0;
    S[9].getThrough = 0;
    S[10].getThrough = 1;

    return S;
}

Map* LoadMap(char* level)
{
    Map* m;
	FILE* F;
	F = fopen(level,"r");
	m = malloc(sizeof(Map));

	m->xscroll = 0;
	m->yscroll = 0;

    int i,j;
	char buf[5000];  // Buffer for the name of the level

	fscanf(F,"%s",buf); // Level name
	fscanf(F,"%d %d",&m->Nb_Block_W,&m->Nb_Block_H); //Number of block width and height

    m->LoadedMap = malloc(m->Nb_Block_W*sizeof(Uint16*)); //memory allocation for the array
    m->Used = malloc(m->Nb_Block_W*sizeof(Uint16*));

    for(i=0;i<m->Nb_Block_W;i++)
    {
        m->LoadedMap[i] = malloc(m->Nb_Block_H*sizeof(Uint16));
        m->Used[i] = malloc(m->Nb_Block_H*sizeof(Uint16));
    }
        for(i=0;i<m->Nb_Block_H;i++)
        {
            for(j=0;j<m->Nb_Block_W;j++)
            {
                int tmp;
                fscanf(F,"%d",&tmp);
                m->LoadedMap[j][i] = tmp;
                m->Used[j][i] = 0;
            }
        }

	fclose(F);

	return m;
}

void ShowMap(Map* m, SDL_Surface* screen, Sprites* S)
{
	int i,j;
	SDL_Rect Rect_dest;
	int numero_tile;
    int minx, maxx, miny, maxy;
    minx = m->xscroll / Size_Sprite-1;
    miny = m->yscroll / Size_Sprite-1;
    maxx = (m->xscroll + WindowW)/Size_Sprite;
    maxy = (m->yscroll + WindowH)/Size_Sprite;
    for(i=minx;i<=maxx;i++)
    {
        for(j=miny;j<=maxy;j++)
        {
            Rect_dest.y = j*Size_Sprite - m->yscroll;
            Rect_dest.x = i*Size_Sprite - m->xscroll;
            if (i<0 || i>=m->Nb_Block_W || j<0 || j>=m->Nb_Block_H)
            {

            }
            else
            {
                numero_tile = m->LoadedMap[i][j];
                SDL_BlitSurface(S[numero_tile].sprite,NULL,screen,&Rect_dest);
            }
        }
    }
}



void FreeMap(Map* m, Sprites* S)
{

    int i;
    SDL_FreeSurface(S[0].sprite);
    SDL_FreeSurface(S[1].sprite);
    SDL_FreeSurface(S[2].sprite);
    SDL_FreeSurface(S[3].sprite);
    SDL_FreeSurface(S[4].sprite);
    SDL_FreeSurface(S[5].sprite);
    SDL_FreeSurface(S[6].sprite);
    SDL_FreeSurface(S[7].sprite);
    SDL_FreeSurface(S[8].sprite);
    SDL_FreeSurface(S[9].sprite);
    SDL_FreeSurface(S[10].sprite);

    free(m->LoadedMap);
    free(m);
    free(S);
}
