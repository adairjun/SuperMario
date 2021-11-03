/*
Super Mario Bros

event.h

Antoine Drabble

Création: 17.01.13
*/
#ifndef EVENT_DEF//this makes it possible to avoid doing the same include several times.
#define EVENT_DEF

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "game.h"
#include "map.h"
#include "char.h"
#include "object.h"
#include "audio.h"

typedef struct
{
	char key[SDLK_LAST];
    char quit;
}Input;

void UpdateEvents(Input* in);
void Evolve(Input* in, Map *m, Chars *mario, Sprites *S, Object* shroom);
void Move(Map* m,Chars* mario,int vx,int vy, Sprites* S, Object* shroom);
int MovementTest(Map* m,Chars* mario,int vx,int vy, Sprites* S, Object* shroom);
void MapScroll(Map* m, Chars* mario);
int CollisionDecor(Map* m, SDL_Rect* perso, Sprites* S, Chars* mario, int vx, Object* shroom);
int FinishLevel (SDL_Surface* screen, Chars* mario, Map* m);

#endif
