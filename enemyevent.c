/*
Super Mario Bros

enemyevent.c

Antoine Drabble

Création: 24.01.13
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "enemyevent.h"


void enemymove(Enemy* flower, Chars* mario, int xscroll, int yscroll, Map* m, Sprites* S)
{
    int i;
    SDL_Rect position[50];

    for (i=1; i<=flower->nb_objet; i++){
        flower->position[i].x = flower->position[i].x - flower->xSpeed;
        flower->position[i].y = flower->position[i].y - flower->ySpeed;

        position[i].x = flower->position[i].x - xscroll;
        position[i].y = flower->position[i].y - yscroll;
        position[i].w = Size_Sprite;
        position[i].h = Size_Sprite;
    }

   for (i=1; i<=flower->nb_objet; i++){ //We pass once per enemy
       if (flower->used[i]==0){
            if((position[i].x >= mario->position.x -xscroll + mario->position.w) //Check if mario touches the muflower
            || (position[i].x + position[i].w <= mario->position.x -xscroll)
            || (position[i].y >= mario->position.y -yscroll + mario->position.h)
            || (position[i].y + position[i].h <= mario->position.y - yscroll)
            ){}
            else{
                // mario died
                mario->lose =1;
            }
       }
   }

}
