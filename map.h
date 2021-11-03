/*
Super Mario Bros

map.h

Antoine Drabble

Création: 07.01.13
*/

#ifndef MAP_DEF//this makes it possible to avoid doing the same include several times.
#define MAP_DEF

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>


#define NbSprites 11 // To be modified if you add sprites
#define Size_Sprite 40 // To modify if we change the sprite size

typedef struct
{
    int Nb_Block_W, Nb_Block_H;
    Uint16** LoadedMap;
    Uint16** Used;
    long int xscroll,yscroll;
}Map;

typedef struct
{
    SDL_Surface* sprite;
    int getThrough;
}Sprites;

Sprites* LoadImages();
Map* LoadMap(char* level);
void ShowMap(Map* m, SDL_Surface* screen, Sprites* S);
void FreeMap(Map* m, Sprites* S);

#endif
