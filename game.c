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
    char *theLevel;

    marioimages = malloc(12 * sizeof(Chars));
    memset(&in,0,sizeof(in)); //Set all keys to 0

    SDL_Rect positionLevel;
    SDL_Surface* level;
    screen = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    level = IMG_Load("images/lvl.jpg"); //Load menu image
    positionLevel.x = screen->w / 2 - level->w / 2; //Sets the menu to the center of the window
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
                        theLevel="theLevel1.lvl";
                        keepGoing=1;
                        break;
                    case SDLK_2:
                        theLevel="theLevel2.lvl";
                        keepGoing=1;
                        break;
                    case SDLK_3:
                        theLevel="theLevel3.lvl";
                        keepGoing=1;
                        break;
                }
                break;
        }
    }

    screen = SDL_SetVideoMode( WindowW, WindowH, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    keepGoing=0;
    S = LoadImages();
    shroom = LoadObject();
    m = LoadMap(theLevel);
    LoadChars(&mario, m, marioimages);
    ShowMap(m, screen, S);
    SDL_Flip(screen);

while(!in.key[SDLK_ESCAPE] && !in.quit && !keepGoing)// simplification of key management
	{
        currentTime = SDL_GetTicks();
        if (currentTime - previousTime > 4) /* If 4 ms have elapsed since the last loop round */
        {
            UpdateEvents(&in);
            MapScroll(m, &mario);
            Evolve(&in,m,&mario,S, shroom);
            ShowMap(m,screen,S);
            objectmove(shroom, &mario, m->xscroll,m->yscroll, m, S);
            ShowObject(screen, shroom, m->xscroll,m->yscroll);
            ShowPerson(&mario,screen,m->xscroll,m->yscroll, marioimages);
            SDL_Flip(screen);
            keepGoing = FinishLevel(screen, &mario, m);
            previousTime = currentTime; /* The "current" time becomes the "previous" time for our future calculations */
        }
        else
        {
        SDL_Delay(4 - (currentTime - previousTime));
        }
    }

    FreeMap(m,S);
    FreeChars(&mario, marioimages);
    FreeObject(shroom);
}
