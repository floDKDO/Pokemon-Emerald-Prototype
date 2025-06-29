#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "defs.h"
#include "log_functions.h"
#include "player.h"
#include "tile.h"


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    CHK(SDL_Init(SDL_INIT_EVERYTHING), SDL_GetError());

    #ifdef DEBUG
    print_C_version();
    #endif // DEBUG

    char window_title[20] = {"My game"};

    SDL_Window* window;
    NCHK(window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE), SDL_GetError());

    SDL_Renderer* renderer;
    NCHK(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED), SDL_GetError());

    CHK(SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND), SDL_GetError()); //allow transparency
    CHK(SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT), SDL_GetError());

    struct player p = player_init("My player");

    struct tile t[10];
    for(int i = 0; i < 10; ++i)
    {
        t[i] = tile_init(1, 16 * i + 16, 16 * i);
    }

    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    bool in_game = true;
    SDL_Event e;

    int nb_frames = 0;
    Uint32 second = 0;

    while(in_game)
    {
        Uint32 begin_time = SDL_GetTicks();

        camera.x = p.pos.x + (TILE_SIZE/2) - SCREEN_WIDTH/2;
        camera.y = p.pos.y + (TILE_SIZE/2) - SCREEN_HEIGHT/2;

        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_MOUSEMOTION:
                    #ifdef DEBUG
                    LOG("Mouse motion event!\n");
                    #endif // DEBUG
                    break;

                case SDL_WINDOWEVENT:
                    if(e.window.event == SDL_WINDOWEVENT_CLOSE)
                    {
                        #ifdef DEBUG
                        LOG("Window close event!\n");
                        #endif // DEBUG

                        in_game = false;
                    }
                    break;

                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        #ifdef DEBUG
                        LOG("Key down (%s) event!\n", SDL_GetKeyName(e.key.keysym.sym));
                        #endif // DEBUG
                        in_game = false;
                    }
                    break;

                default:
                    break;
            }
            player_handle_events(&p, e);
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        for(int i = 0; i < 10; ++i)
            tile_draw(&t[i], camera, renderer);

        player_draw(&p, camera, renderer);

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        for(int i = 0; i < 10; ++i)
        {
            if(p.is_walking)
            {
                SDL_Rect copy = p.pos;

                if(p.direction[0])
                {
                    copy.y -= TILE_SIZE;
                }
                else if(p.direction[1])
                {
                    copy.y += TILE_SIZE;
                }
                else if(p.direction[2])
                {
                    copy.x -= TILE_SIZE;
                }
                else if(p.direction[3])
                {
                    copy.x += TILE_SIZE;
                }

                if(SDL_HasIntersection(&t[i].pos, &copy))
                {
                    printf("Collision!\n");
                    p.can_walk = false;
                }
            }
            else p.can_walk = true;
        }

        player_update(&p);

        Uint32 end_time = SDL_GetTicks();

        #ifdef DEBUG
        nb_frames += 1;
        if(SDL_GetTicks() - second >= 1000) //1000ms = 1s
        {
            CHK(snprintf(window_title, 20, "%s%d%s", "My game (", nb_frames, " FPS)"), "Error: snprintf");
            SDL_SetWindowTitle(window, window_title);
            nb_frames = 0;
            second = SDL_GetTicks();
        }
        #endif // DEBUG

        Uint32 wait_time;
        if(end_time - begin_time > 16) //16ms = 1/60s (60 FPS)
        {
            wait_time = 0;
        }
        else wait_time = 16 - (end_time - begin_time);

        SDL_Delay(wait_time);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
