/*
Super Mario Bros

enemyevent.h

Antoine Drabble

Création: 24.01.13
*/

#ifndef ENEMYMOVE_DEF//this makes it possible to avoid doing the same include several times.
#define ENEMYMOVE_DEF

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "char.h"
#include "audio.h"
#include "map.h"
#include "enemy.h"

void enemymove(Enemy* flower, Chars* mario, int xscroll, int yscroll, Map* m, Sprites* S);

#endif
