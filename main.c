#include <stdio.h>
#include "init.h"
#include "DrawCircle.h"
#include "port.h"

int main(int argc, char* argv[]) {

    if (!init()) {
        printf("SYSTEM INIT FAILED!\n");
    }
    else {
        int flag = 1;
        int chessmanCount = 0;
        SDL_Point chessmanPosition;
        SDL_Event event;
        int mouse_x;
        int mouse_y;
        bool quit = false;

        initPositionTable();
        SDL_RenderClear(render);
        while (!quit) {
            initPort(1);  // init and theme
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
                    chessmanPosition = portCheckIn(mouse_x, mouse_y, flag);
                    if (chessmanPosition.x == -1 || chessmanPosition.y == -1) continue;  // outside range
                    if (positionStatusTable[chessmanPosition.x][chessmanPosition.y] == 0) continue;  // have been recorded
                    ++chessmanCount;
                    chessmanStatusChange(chessmanPosition.x, chessmanPosition.y, chessmanCount, flag);
                    if (flag == 1) flag = 0;
                    else flag = 1;
                }
            }
            portCheckIn(mouse_x, mouse_y, flag);
            if (chessmanCount > 0 ) chessmanLocationView(chessmanCount);
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

