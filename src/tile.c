#include "tile.h"
#include "defs.h"

struct tile tile_init(unsigned int type, int x, int y)
{
    struct tile t;
    t.type = type;

    t.pos.x = x;
    t.pos.y = y;
    t.pos.w = TILE_SIZE;
    t.pos.h = TILE_SIZE;

    t.has_collision = true;

    return t;
}

void tile_draw(struct tile* t, SDL_Rect camera, SDL_Renderer* renderer)
{
    SDL_Rect r = {t->pos.x - camera.x, t->pos.y - camera.y, t->pos.w, t->pos.h};
    CHK(SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255), SDL_GetError());
    CHK(SDL_RenderFillRect(renderer, &r), SDL_GetError());
}

void tile_handle_events(struct tile* t, SDL_Event e)
{

}

void tile_update(struct tile* t)
{

}
