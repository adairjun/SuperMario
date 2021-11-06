/*
Super Mario Bros

enemy.h

Antoine Drabble

Création: 24.01.13
*/

#ifndef ENEMY_DEF//this makes it possible to avoid doing the same include several times.
#define ENEMY_DEF

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "game.h"
#include "map.h"
#include "char.h"

typedef struct
{
    SDL_Surface* image;
    SDL_Rect position[50];
    int nb_objet, used[50];
    int xSpeed[50];
    int ySpeed[50];
}Enemy;

Enemy* LoadEnemy(Map* m);
void ShowEnemy(SDL_Surface* screen,Enemy* flower, int xscroll, int yscroll);
void FreeEnemy (Enemy* flower);

#endif
