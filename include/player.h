#ifndef __PLAYER__H__
#define __PLAYER__H__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_LENGTH_PLAYER_NAME 10

struct player
{
    char name[MAX_LENGTH_PLAYER_NAME];
    SDL_Rect pos;
    bool direction[4]; //UP, DOWN, LEFT, RIGHT
    unsigned int speed;
    bool can_walk;
    bool is_walking;
};


struct player player_init(char* name);

void player_draw(struct player* p, SDL_Rect camera, SDL_Renderer* renderer);

void player_handle_events(struct player* p, SDL_Event e);

void player_update(struct player* p);


#endif // __PLAYER__H__
