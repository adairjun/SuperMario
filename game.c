/*
Super Mario Bros

Game.c

Antoine Drabble

Création: 07.01.13
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "game.h"
#include "map.h"
#include "char.h"
#include "object.h"
#include "objectevent.h"
#include "event.h"
#include "audio.h"

void game(SDL_Surface* screen)
{
    SDL_Event event;
    Map* m;
    Sprites* S;
    Chars mario;
    Chars* marioimages;
    Object* shroom;
    Input in;
    int keepGoing = 0;
    int previousTime = 0, currentTime = 0;
    char *niveau;

    marioimages = malloc(12 * sizeof(Chars));
    memset(&in,0,sizeof(in)); //Set toutes les touches à 0

    SDL_Rect positionLevel;
    SDL_Surface* level;
    screen = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    level = IMG_Load("images/lvl.jpg"); //Charge l'image du menu
    positionLevel.x = screen->w / 2 - level->w / 2; //Définit le menu au centre de la fenêtre
    positionLevel.y = 0;
    SDL_BlitSurface(level, NULL, screen, &positionLevel);
    SDL_Flip(screen);
    SDL_FreeSurface(level);

    while (!keepGoing)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        return;
                        break;
                    case SDLK_1:
                        niveau="niveau1.lvl";
                        keepGoing=1;
                        break;
                    case SDLK_2:
                        niveau="niveau2.lvl";
                        keepGoing=1;
                        break;
                    case SDLK_3:
                        niveau="niveau3.lvl";
                        keepGoing=1;
                        break;
                }
                break;
        }
    }

    screen = SDL_SetVideoMode( WindowW, WindowH, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    keepGoing=0;
    S = ChargerImages();
    shroom = ChargerObject();
    m = ChargerMap(niveau);
    LoadChars(&mario, m, marioimages);
    AfficherMap(m, screen, S);
    SDL_Flip(screen);

while(!in.key[SDLK_ESCAPE] && !in.quit && !keepGoing)// simplification de la gestion des touches
	{
        currentTime = SDL_GetTicks();
        if (currentTime - previousTime > 4) /* Si 30 ms se sont écoulées depuis le dernier tour de boucle */
        {
            UpdateEvents(&in);
            MapScroll(m, &mario);
            Evolve(&in,m,&mario,S, shroom);
            AfficherMap(m,screen,S);
            objectmove(shroom, &mario, m->xscroll,m->yscroll, m, S);
            AfficherObject(screen, shroom, m->xscroll,m->yscroll);
            ShowPerson(&mario,screen,m->xscroll,m->yscroll, marioimages);
            SDL_Flip(screen);
            keepGoing = FinishLevel(screen, &mario, m);
            previousTime = currentTime; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
        }
        else
        {
        SDL_Delay(4 - (currentTime - previousTime));
        }
    }

    LibererMap(m,S);
    FreeChars(&mario, marioimages);
    LibererObject(shroom);
}
