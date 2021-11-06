/*
Super Mario Bros

enemy.c

Antoine Drabble

Création: 24.01.13
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "enemy.h"

void ShowEnemy(SDL_Surface* screen, Enemy* flower, int xscroll, int yscroll)
{
    int i;
    SDL_Rect position[50];

    for (i=1; i<=flower->nb_objet; i++){

        position[i].x = flower->position[i].x - xscroll;
        position[i].y = flower->position[i].y - yscroll;
        position[i].w = Size_Sprite;
        position[i].h = Size_Sprite;
    }

    for (i=1; i<=flower->nb_objet; i++){
        if (flower->used[i]==0){
            SDL_BlitSurface(flower->image,NULL,screen,&position[i]);
        }
    }
}

Enemy* LoadEnemy(Map* m)
{
    Enemy* flower;
    flower = malloc(sizeof(Enemy));

    flower->image = IMG_Load("images/enemy.png");
    flower->nb_objet = 1;
    flower->used[flower->nb_objet]= 0;

    flower->position[flower->nb_objet].w = 32;
    flower->position[flower->nb_objet].h = 32;

    flower->position[flower->nb_objet].x = 800;
    flower->position[flower->nb_objet].y = m->Nb_Block_H*Size_Sprite-2*Size_Sprite-flower->position[flower->nb_objet].h;

    flower->xSpeed[flower->nb_objet] = -2;
    flower->ySpeed[flower->nb_objet] = 0;


    flower->nb_objet = 2;
    flower->used[flower->nb_objet]= 0;

    flower->position[flower->nb_objet].w = 32;
    flower->position[flower->nb_objet].h = 32;

    flower->position[flower->nb_objet].x = 700;
    flower->position[flower->nb_objet].y = m->Nb_Block_H*Size_Sprite-2*Size_Sprite-flower->position[flower->nb_objet].h;

    flower->xSpeed[flower->nb_objet] = -2;
    flower->ySpeed[flower->nb_objet] = 0;

    return flower;
}

void FreeEnemy (Enemy* flower)
{
    SDL_FreeSurface(flower->image);
    free(flower);
}
