/*
Super Mario Bros

Menu

Main.c

Antoine Drabble

Création: 07.01.13
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <fmod.h>

#include "credits.h"
#include "game.h"
#include "audio.h"

int main(int argc, char *argv[])
{
    SDL_Surface* screen = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int keepGoing = 1;

    audio_init();
    audio_play(1);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("images/Mario.png"), NULL); // Icon must be loaded before SDL_SetVideoMode
    screen = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Open the page
    SDL_WM_SetCaption("Super Mario BROS", NULL); //Define the title

    menu = IMG_Load("images/menu.jpg"); //Load menu image
    positionMenu.x = screen->w / 2 - menu->w / 2; //Sets the menu to the center of the window
    positionMenu.y = 0;


    while (keepGoing)
    {
        SDL_WaitEvent(&event);
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
                    case SDLK_1:

                        game(screen);
                        screen = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        break;
                    case SDLK_2:
                        credits(screen);
                        break;
                }
                break;
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); //Black background
        SDL_BlitSurface(menu, NULL, screen, &positionMenu); //Print the menu on the page
        SDL_Flip(screen);
    }

    audio_stop();
    SDL_FreeSurface(menu); //Clear menu
    SDL_Quit(); //Quit

    return EXIT_SUCCESS;
}
