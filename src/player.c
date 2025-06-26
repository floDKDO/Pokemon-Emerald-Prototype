#include "player.h"
#include "defs.h"
#include "log_functions.h"

struct player player_init(char* name)
{
    struct player p;
    CHK(snprintf(p.name, MAX_LENGTH_PLAYER_NAME, "%s", name), "Error: snprintf");
    p.x = 0;
    p.y = 0;
    memset(p.direction, false, 4);
    p.speed = 5;

    return p;
};


void player_draw(struct player* p, SDL_Renderer* renderer)
{
    SDL_Rect r = {p->x, p->y, TILE_SIZE, TILE_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    CHK(SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255), SDL_GetError());
    CHK(SDL_RenderFillRect(renderer, &r), SDL_GetError());
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}


void player_handle_events(struct player* p, SDL_Event e)
{
    switch(e.type)
    {
        case SDL_KEYDOWN:
            #ifdef DEBUG
            LOG("Key down (%s) event!\n", SDL_GetKeyName(e.key.keysym.sym));
            #endif // DEBUG

            if(e.key.keysym.sym == SDLK_UP)
            {
                p->direction[0] = true;
            }
            else if(e.key.keysym.sym == SDLK_DOWN)
            {
                p->direction[1] = true;
            }
            else if(e.key.keysym.sym == SDLK_LEFT)
            {
                p->direction[2] = true;
            }
            else if(e.key.keysym.sym == SDLK_RIGHT)
            {
                p->direction[3] = true;
            }
            break;

        case SDL_KEYUP:
            #ifdef DEBUG
            LOG("Key up (%s) event!\n", SDL_GetKeyName(e.key.keysym.sym));
            #endif // DEBUG

            if(e.key.keysym.sym == SDLK_UP)
            {
                p->direction[0] = false;
            }
            else if(e.key.keysym.sym == SDLK_DOWN)
            {
                p->direction[1] = false;
            }
            else if(e.key.keysym.sym == SDLK_LEFT)
            {
                p->direction[2] = false;
            }
            else if(e.key.keysym.sym == SDLK_RIGHT)
            {
                p->direction[3] = false;
            }
            break;

        default:
            break;
    }
}


void player_update(struct player* p)
{
    if(p->direction[0] == true)
    {
        p->y -= p->speed;
    }
    else if(p->direction[1] == true)
    {
        p->y += p->speed;
    }
    else if(p->direction[2] == true)
    {
        p->x -= p->speed;
    }
    else if(p->direction[3] == true)
    {
        p->x += p->speed;
    }
}
