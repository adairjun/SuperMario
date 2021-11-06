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

#include "event.h"
#include "enemyevent.h"


void enemymove(Enemy* flower, Chars* mario, int xscroll, int yscroll, Map* m, Sprites* S)
{
    int i;
    SDL_Rect position[50];

    for (i=1; i<=flower->nb_objet; i++){
        SDL_Rect test;
        test = flower->position[i];
	    test.x+=flower->xSpeed[i];
	    test.y+=flower->ySpeed[i];
        
        int temp, temp2;
	    temp = CollisionDecor2(m, &test, S, flower->xSpeed[i]);
        temp2 = CollisionDecor3(&test, flower->xSpeed[i],flower,i);
        flower->position[i] = test;
        if (temp == 1 || temp2 == 1) {
            flower->xSpeed[i] = -flower->xSpeed[i];
        } else if (temp == 2 || temp2 == 2)  {
            flower->ySpeed[i] = -flower->ySpeed[i];
        }

        // flower->position[i].x = flower->position[i].x + flower->xSpeed[i];
        // flower->position[i].y = flower->position[i].y + flower->ySpeed[i];

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
                if(mario->lvl==1)
                    mario->lose=1;
                if(mario->lvl==2)
                    audio_play(6);
                    mario->lvl=1;
                    mario->position.y+=10;
                    mario->lvllost=400;
            }
       }
   }

}
