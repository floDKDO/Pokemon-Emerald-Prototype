#ifndef __PLAYER__H__
#define __PLAYER__H__

#include <SDL2/SDL.h>
#include <stdio.h>

#define MAX_LENGTH_PLAYER_NAME 10

struct player
{
    char name[MAX_LENGTH_PLAYER_NAME];
    int x, y;
};


struct player player_init(char* name);

void player_draw(struct player* p, SDL_Renderer* renderer);


#endif // __PLAYER__H__
