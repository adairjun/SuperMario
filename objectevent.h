/*
Super Mario Bros

objectevent.h

Antoine Drabble

Création: 24.01.13
*/

#ifndef OBJECTMOVE_DEF//this makes it possible to avoid doing the same include several times.
#define OBJECTMOVE_DEF

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "char.h"
#include "audio.h"
#include "map.h"
#include "object.h"

void objectmove(Object* shroom, Chars* mario, int xscroll, int yscroll, Map* m, Sprites* S);

#endif
