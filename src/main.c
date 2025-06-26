#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "defs.h"
#include "log_functions.h"
#include "player.h"


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
    NCHK(window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE), SDL_GetError());

    SDL_Renderer* renderer;
    NCHK(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED), SDL_GetError());

    CHK(SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND), SDL_GetError()); //allow transparency
    CHK(SDL_RenderSetLogicalSize(renderer, 1280, 720), SDL_GetError());

    struct player p = player_init("My player");

    bool in_game = true;
    SDL_Event e;

    int nb_frames = 0;
    Uint32 second = 0;

    while(in_game)
    {
        Uint32 begin_time = SDL_GetTicks();

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

                default:
                    break;
            }
            player_handle_events(&p, e);
        }
        player_draw(&p, renderer);
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
