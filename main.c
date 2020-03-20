#include <stdio.h>
#include "funcs/init.h"
#include "funcs/DrawCircle.h"
#include "funcs/port.h"

int main(int argc, const char** argv) {

    if (!init()) {
        printf("SYSTEM INIT FAILED!\n");
    }
    else {
        initPositionTable();
        SDL_RenderClear(render);
        

        

        SDL_Event event;
        bool quit = false;
        int mouse_x;
        int mouse_y;
        while (!quit) {
            initPort(1);
            // for (int i = 0; i < 15; i++) {
            //     //SDL_RenderDrawRects(render, portPositionCheckRect[i], 15*15);
            //     for (int j = 0; j < 15; j++)
            //     {
            //         drawCircle(render, portPosition[i][j].x, portPosition[i][j].y, CHESSMAN_RADIUS, 1);
            //     }
            // }
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    printf("goodbye!\n");
                    quit = true;
                }
                if (event.type == SDL_MOUSEMOTION) {
                    mouse_x = event.motion.x;
                    mouse_y = event.motion.y;
                }
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    printf("{%d, %d}", getSubcript(mouse_x, mouse_y).x, getSubcript(mouse_x, mouse_y).y);
                }
            }
            portCheckIn(mouse_x, mouse_y);
            
            SDL_RenderPresent(render);
            SDL_RenderClear(render);
            SDL_Delay(100);
        }
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    return 0;
}

