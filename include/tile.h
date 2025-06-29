#ifndef __TILE__H__
#define __TILE__H__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>


struct tile
{
    unsigned int type;
    SDL_Rect pos;
    bool has_collision;
};


struct tile tile_init(unsigned int type, int x, int y);

void tile_draw(struct tile* t, SDL_Rect camera, SDL_Renderer* renderer);

void tile_handle_events(struct tile* t, SDL_Event e);

void tile_update(struct tile* t);


#endif // __TILE__H__
