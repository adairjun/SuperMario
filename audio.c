/*
Super Mario Bros

Audio.c

Antoine Drabble

Création: 22.01.13
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <fmod.h>

#include "audio.h"

FMOD_SOUND *music, *jump, *lose, *win, *shroom, *damage;
FMOD_SYSTEM *sys; // FMOD, library that manages music

void audio_init(){
    FMOD_System_Create(&sys);
    FMOD_System_Init(sys, 4, FMOD_INIT_NORMAL, NULL);
    FMOD_System_CreateSound(sys, "sound/music.mp3", FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &music); //Load the music
    FMOD_Sound_SetLoopCount(music, -1); // Activate endless repetition
    FMOD_System_CreateSound(sys, "sound/smb_jumpsmall.wav", FMOD_CREATESAMPLE, 0, &jump);
    FMOD_System_CreateSound(sys, "sound/smb_mariodie.wav", FMOD_CREATESAMPLE, 0, &lose);
    FMOD_System_CreateSound(sys, "sound/smb_stage_clear.wav", FMOD_CREATESAMPLE, 0, &win);
    FMOD_System_CreateSound(sys, "sound/smb2_grow.wav", FMOD_CREATESAMPLE, 0, &shroom);
    FMOD_System_CreateSound(sys, "sound/smb3_lost_suit.wav", FMOD_CREATESAMPLE, 0, &damage);
}

void audio_play(int song){
    if (song==1)
        FMOD_System_PlaySound(sys, 0, music, 0, NULL); //Joue la musique
    if (song==2)
        FMOD_System_PlaySound(sys, NULL, jump, 0, NULL);
    if (song==3)
        FMOD_System_PlaySound(sys, NULL, lose, 0, NULL);
    if (song==4)
        FMOD_System_PlaySound(sys, NULL, win, 0, NULL);
    if (song==5)
        FMOD_System_PlaySound(sys, NULL, shroom, 0, NULL);
    if (song==6)
        FMOD_System_PlaySound(sys, NULL, damage, 0, NULL);
}

void audio_stop(){
    FMOD_Sound_Release(music);
    FMOD_Sound_Release(damage);
    FMOD_Sound_Release(jump);
    FMOD_Sound_Release(win);
    FMOD_Sound_Release(lose);
    FMOD_Sound_Release(shroom);
    FMOD_System_Close(sys);
    FMOD_System_Release(sys);
}
