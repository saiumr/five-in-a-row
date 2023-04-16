#include "event.h"

int flag = 1;
int chessmanCount = 0;
SDL_Point chessmanPosition;
SDL_Event event;
int mouse_x;
int mouse_y;
bool quit = false;

void eventHandle(SDL_Event event) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
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
            chessmanStatusTableChange(chessmanPosition.x, chessmanPosition.y, chessmanCount, flag);
            if (flag == 1) flag = 0;
            else flag = 1;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }
    }
    portCheckIn(mouse_x, mouse_y, flag);
    if (chessmanCount > 0 ) chessmanLocationView(chessmanCount);
}