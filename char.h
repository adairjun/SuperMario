/*
Super Mario Bros

char.h

Antoine Drabble

Création: 17.01.13
*/

#ifndef CHAR_DEF//this makes it possible to avoid doing the same include several times.
#define CHAR_DEF

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "game.h"
#include "map.h"
#include "object.h"

typedef struct
{
SDL_Surface* image;
SDL_Rect position;
int jump, jumptime, G, selectedmario;
int directionmario, temp, lastdirection, win, lose, lvl, lvllost, invisible;
}Chars;

void LoadChars(Chars* mario, Map* m, Chars* marioimages);
void ShowPerson(Chars* mario, SDL_Surface* screen, int xscroll, int yscroll, Chars* marioimages);
void FreeChars (Chars* mario, Chars* marioimages);

#endif
