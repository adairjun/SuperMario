/*
Super Mario Bros

audio.h

Antoine Drabble

Création: 22.01.13
*/

#ifndef ADUIO_DEF//this makes it possible to avoid doing the same include several times.
#define AUDIO_DEF

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

void audio_init();
void audio_play(int song);
void audio_stop();

#endif
