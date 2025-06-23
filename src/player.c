#include "player.h"
#include "defs.h"

struct player player_init(char* name)
{
    struct player p;
    CHK(snprintf(p.name, MAX_LENGTH_PLAYER_NAME, "%s", name), "Error: snprintf");
    p.x = 0;
    p.y = 0;

    return p;
};


void player_draw(struct player* p, SDL_Renderer* renderer)
{
    SDL_Rect r = {p->x, p->y, TILE_SIZE, TILE_SIZE};
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //SDL_RenderClear(renderer);
    CHK(SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255), SDL_GetError());
    CHK(SDL_RenderFillRect(renderer, &r), SDL_GetError());
    SDL_RenderPresent(renderer);
}
