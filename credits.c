/*
Super Mario Bros

Credit.c

Antoine Drabble

Création: 07.01.13
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "credits.h"


void credits(SDL_Surface* screen)
{
    SDL_Surface *ImgCredits = NULL;
    SDL_Rect positionCredits;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;
    int previousTime = 0, currentTime = 0;

    ImgCredits = IMG_Load("images/credits.png");
    positionCredits.x = screen->w / 2 - ImgCredits->w / 2;
    positionCredits.y = -200;

    int keepGoing = 1;

    while (keepGoing)
        {
            SDL_PollEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    keepGoing = 0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            keepGoing = 0;
                            break;
                    }
            }

    if (positionCredits.y > 400+ImgCredits->h/2)
    {
        keepGoing = 0;
    }

        currentTime = SDL_GetTicks();
        if (currentTime - previousTime > 10) /* If 10 ms have elapsed since the last loop round */
        {
            positionCredits.y++; // We move the credits
            previousTime = currentTime; // The "current" time becomes the "previous" time for our future calculations
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 82, 131, 252));
        SDL_BlitSurface(ImgCredits, NULL, screen, &positionCredits);
        SDL_Flip(screen);
    }

    SDL_FreeSurface(ImgCredits);
}
