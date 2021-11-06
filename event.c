/*
Super Mario Bros

Menu

event.c

Antoine Drabble

Création: 07.01.13
*/


#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <fmod.h>

#include "event.h"
#include "enemy.h"

void UpdateEvents(Input* in)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			in->key[event.key.keysym.sym]=1;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.sym]=0;
			break;
		case SDL_QUIT:
			in->quit = 1;
			break;
		default:
			break;
		}
	}
}

void CollisionDecor(Map* m, SDL_Rect* person, Sprites* S, Chars* mario, int vx, Object* shroom)
{
	int xmin,xmax,ymin,ymax,i,j,indicetile;
	xmin = person->x / Size_Sprite;
	ymin = person->y / Size_Sprite;
	xmax = (person->x + person->w -1) / Size_Sprite;
	ymax = (person->y + person->h -1) / Size_Sprite;
    mario->G=1;

    if (mario->lvllost>0){
        mario->lvllost--;
        if(mario->invisible==1)
            mario->invisible=0;
        else
            mario->invisible=1;
    }
    else{
        mario->invisible=0;
    }

if (person->h+person->y<m->Nb_Block_H*Size_Sprite-10){
    j = (person->y + person->h +1) / Size_Sprite;
    for(i=xmin;i<=xmax;i++) //If there is a block below
    {
        indicetile = m->LoadedMap[i][j];
        if (S[indicetile].getThrough){
            mario->G=0;
            mario->jump = 1;
        }
        if (indicetile==10){
            if (mario->lvllost<1)
            {
                if(mario->lvl==1)
                    mario->lose=1;
                if(mario->lvl==2)
                    audio_play(6);
                    mario->lvl=1;
                    mario->position.y+=10;
                    mario->lvllost=400;
            }
        }
        else{ //If we don't touch the ground and the jump time is over 1000, we fall back.
            if(mario->jumptime>1000)
                mario->jump = 0;
        }
    }
}

    j = (person->y - 1) / Size_Sprite;
	for(i=xmin;i<=xmax;i++) //If there is a block above
	{
		    indicetile = m->LoadedMap[i][j];
		    if (S[indicetile].getThrough)
                mario->jumptime = 1001;
            if (indicetile==3){
                if(S[m->LoadedMap[i][j-1]].getThrough==0){
                    if (m->Used[i][j]==0){
                        shroom->nb_objet++; //Creation of a mushroom!
                        shroom->used[shroom->nb_objet]= 0;
                        shroom->position[shroom->nb_objet].x = i*Size_Sprite;
                        shroom->position[shroom->nb_objet].y = (j-1)*Size_Sprite;
                        m->Used[i][j]=1;
                    }
                }
            }
	}

	i= (person->x + person->w) / Size_Sprite; //If we hit a block to our right,
    for(j=ymin;j<=ymax;j++)
    {
        indicetile = m->LoadedMap[i][j];
        if (S[indicetile].getThrough){
            person->x-=vx;
            j=ymax+1;
            }
    }
    i = (person->x -1) / Size_Sprite; //If we touch a left notepad
    for(j=ymin;j<=ymax;j++)
    {
        indicetile = m->LoadedMap[i][j];
        if (S[indicetile].getThrough){
            person->x-=vx;
            j=ymax+1;
            }
    }
    for(i=xmin;i<=xmin;i++){
        for(j=ymin;j<=ymax;j++)
        {
            indicetile = m->LoadedMap[i][j];
            if (indicetile==8 || indicetile==9){ // If we touch the flag at the end
                    mario->win = 1;
                }
        }
    }


	return;
}

int CollisionDecor2(Map* m, SDL_Rect* person, Sprites* S, int vx)
{
	int xmin,xmax,ymin,ymax,i,j,indicetile;
	xmin = person->x / Size_Sprite;
	ymin = person->y / Size_Sprite;
	xmax = (person->x + person->w -1) / Size_Sprite;
	ymax = (person->y + person->h -1) / Size_Sprite;

	i= (person->x + person->w) / Size_Sprite; //If we hit a block to our right,
    for(j=ymin;j<=ymax;j++)
    {
        indicetile = m->LoadedMap[i][j];
        if (S[indicetile].getThrough){
            person->x-=vx;
            return 1;  //  Horizontal collision
        }
    }
    i = (person->x -1) / Size_Sprite; //If we touch a left notepad
    for(j=ymin;j<=ymax;j++)
    {
        indicetile = m->LoadedMap[i][j];
        if (S[indicetile].getThrough){
            person->x-=vx;
            return 1; // Horizontal collision
        }
    }


	return 0; // no collision
}

int MovementTest(Map* m, Chars* mario, int vx, int vy, Sprites* S, Object* shroom)
{
	SDL_Rect test;
	test = mario->position;
	test.x+=vx;
	test.y+=vy;

	CollisionDecor(m, &test, S, mario, vx, shroom);

    if(test.y+test.h>(Size_Sprite*m->Nb_Block_H)+100)
        mario->lose=1;
	if (mario->G==1) //Gravity activated if the soil is not touched
		test.y += 2;
	else
        mario->jumptime = 1;
    if (test.x-1<0) // If we touch the left edge of the map
        test.x-=vx;
    if (test.x + test.w>=m->Nb_Block_W*Size_Sprite-2) // If we touch the right edge of the map
        test.x-=vx;
    if (test.y<0){ // If we touch the top of the map
        mario->jumptime = 1001;
        test.y+=vy;
    }

	mario->position = test;
	return 1;
	
}

void Move(Map* m, Chars* mario,int vx,int vy, Sprites* S, Object* shroom)
{
	if (vx>=Size_Sprite || vy>=Size_Sprite) //if ever the verctor is bigger than a sprite, so that we don't get throught it
	{
		Move(m,mario,vx/2,vy/2,S,shroom);
		Move(m,mario,vx/3,vy/3,S,shroom);
		Move(m,mario,vx/4,vy/4,S,shroom);
		return;
	}
	MovementTest(m,mario,vx,vy,S,shroom); //If no collision
    return;
}

void Evolve(Input* in, Map *m, Chars *mario, Sprites *S, Object* shroom)
{
	int vx,vy;
    int vitesse = 2;
	vx = vy = 0;
	if (!in->key[SDLK_UP]){
        mario->jumptime=1001;
	}
	if (in->key[SDLK_UP]){
        if (mario->jump==1){
            if (mario->jumptime<=1)
                audio_play(2);

            mario->jumptime +=10;
            vy -= 5;

            if(mario->jumptime>1000)
                in->key[SDLK_UP]=0; //Do not jump all the time if you leave the up key activated
        }
	}
	if (in->key[SDLK_LEFT]){
        vx = -vitesse;
		mario->directionmario = 1;
	}
	if (in->key[SDLK_RIGHT]){
		vx = vitesse;
		mario->directionmario = 2;
	}

	Move(m,mario,vx,vy, S, shroom);
}

void MapScroll(Map* m, Chars* mario)
{
            m->xscroll = mario->position.x + mario->position.w/2 - WindowW/2;
            m->yscroll = mario->position.y + mario->position.h/2 - WindowH/2;
        if (m->xscroll<0)
            m->xscroll=0;
        if (m->yscroll<0)
            m->yscroll=0;
        if (m->xscroll>m->Nb_Block_W*Size_Sprite-WindowW-1)
            m->xscroll=m->Nb_Block_W*Size_Sprite-WindowW-1;
        if (m->yscroll>m->Nb_Block_H*Size_Sprite-WindowH-1)
            m->yscroll=m->Nb_Block_H*Size_Sprite-WindowH-1;
}

int FinishLevel (SDL_Surface* screen, Chars* mario, Map* m)
{
    SDL_Event event;
    int keepGoing;

    if (mario->win==1)
    {
        audio_play(4);
        SDL_Surface* succeeded = IMG_Load("images/win.png");
        SDL_Rect positionsucceeded ;
        positionsucceeded.x = WindowW/2-succeeded->w/2;
        positionsucceeded.y = WindowH/2-succeeded->h/2;

        SDL_BlitSurface(succeeded,NULL,screen,&positionsucceeded);
        SDL_Flip(screen);
        SDL_Delay(1000);

        while (keepGoing)
        {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    keepGoing = 0;
                    break;
                case SDL_KEYDOWN:
                    keepGoing = 0;
                    break;
            }
        }
    mario->win=0;
    SDL_FreeSurface(succeeded);
    return 1;
    }

    if (mario->lose==1)
    {
        audio_play(3);
        SDL_Surface* failed = IMG_Load("images/lose.png");
        SDL_Rect positionfailed;
        positionfailed.x = WindowW/2-failed->w/2;
        positionfailed.y = WindowH/2-failed->h/2;

        SDL_BlitSurface(failed,NULL,screen,&positionfailed);
        SDL_Flip(screen);

        while (keepGoing)
        {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    keepGoing = 0;
                    break;
                case SDL_KEYDOWN:
                    keepGoing = 0;
                    break;
            }
        }

    mario->lose=0;
    SDL_FreeSurface(failed);
    return 1;
    }

    return 0;

}
